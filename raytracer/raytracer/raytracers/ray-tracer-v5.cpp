#include "raytracers/ray-tracer-v5.h"


using namespace imaging;
using namespace math;
using namespace raytracer;

TraceResult raytracer::raytracers::_private_::RayTracerV5::trace(const Scene &scene, const math::Ray &ray) const
{
	Hit hit;

	if (scene.root->find_first_positive_hit(ray, &hit))
	{
		double t = hit.t;
		unsigned group_id = hit.group_id;
		return TraceResult(trace(scene, ray, 1.0), group_id, ray, t);
	}
	else
	{
		return TraceResult::no_hit(ray);
	}
}

imaging::Color raytracer::raytracers::_private_::RayTracerV5::trace(const Scene &scene, const math::Ray &ray, double weight) const
{
	Color result = colors::black();

	
	if (weight > 0.01)
	{
		Hit hit;

		if (scene.root->find_first_positive_hit(ray, &hit))
		{
			double t = hit.t;
			MaterialProperties prop = hit.material->at(hit.local_position);

			result += prop.ambient;
			result += process_lights(scene, prop, hit, ray);
			result += compute_reflection(scene, prop, ray, hit, weight);
		}
	}

	return result;
}

imaging::Color raytracer::raytracers::_private_::RayTracerV5::compute_reflection(const Scene &scene, const MaterialProperties &props, const math::Ray &ray, const Hit& reflect, double weight) const
{
	Color result = colors::black();

	if (props.reflectivity > 0)
	{
		Vector3D outgoingAlpha = (reflect.position - ray.origin).normalized().reflect_by(reflect.normal);
		Point3D new_Origin = ray.at(reflect.t) + 0.000001 * outgoingAlpha;
		Ray newRay = Ray(new_Origin, outgoingAlpha);

		result += (props.reflectivity * trace(scene, newRay, props.reflectivity * weight));
	}
	return result;
}

RayTracer raytracer::raytracers::v5()
{
	return raytracer::RayTracer(std::make_shared<raytracer::raytracers::_private_::RayTracerV5>());
}

