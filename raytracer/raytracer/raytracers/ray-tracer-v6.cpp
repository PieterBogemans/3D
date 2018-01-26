#include "ray-tracer-v6.h"
#include "ray-tracer-v5.h"

using namespace imaging;
using namespace math;
using namespace raytracer;


imaging::Color raytracer::raytracers::_private_::RayTracerV6::trace(const Scene &scene, const math::Ray &ray, double weight) const
{
	Color result = colors::black();

	if (weight > 0.01)
	{
		Hit hit;

		if (scene.root->find_first_positive_hit(ray, &hit))
		{
			MaterialProperties prop = hit.material->at(hit.local_position);

			result += prop.ambient;
			result += process_lights(scene, prop, hit, ray);
			result += compute_reflection(scene, prop, ray, hit, weight);
			result += compute_refraction(scene, prop, ray, hit, weight);

			return result;
		}
	}
	return result;
}

imaging::Color raytracer::raytracers::_private_::RayTracerV6::compute_refraction(const Scene &scene, const MaterialProperties &prop, const math::Ray &ray, const Hit &hit, double weight) const
{
	if (prop.transparency > 0)
	{
		Ray refracted_ray = compute_refracted_ray(scene, ray, hit, 1.0, prop.refractive_index);
		if (refracted_ray == ray)
		{
			return colors::black();
		}

		Hit exit_hit;
		if (scene.root->find_first_positive_hit(refracted_ray, &exit_hit))
		{
			Ray exit_ray = compute_refracted_ray(scene, refracted_ray, exit_hit, prop.refractive_index, 1.0);

			return trace(scene, exit_ray, weight * prop.transparency) * prop.transparency;
		}
	}
	return colors::black();
}

math::Ray raytracer::raytracers::_private_::RayTracerV6::compute_refracted_ray(const Scene &scene, const math::Ray &ray, const Hit &hit, double n1, double n2) const
{
	Vector3D normal = (hit.position - ray.origin).normalized();
	Vector3D outX = (n1 / n2) * (normal - (normal.dot(hit.normal)) * hit.normal);

	if ((1 - outX.norm_sqr()) < 0)
	{
		return ray;
	}

	Vector3D outY = (0 - sqrt(1 - outX.norm_sqr())) * hit.normal;
	Vector3D outDirection = outX + outY;
	Point3D outOrigin = ray.at(hit.t) + (0.000001 * outDirection);
	Ray refracted_ray = Ray(outOrigin, outDirection);

	return refracted_ray;
}

RayTracer raytracer::raytracers::v6()
{
	return raytracer::RayTracer(std::make_shared<raytracer::raytracers::_private_::RayTracerV6>());
}