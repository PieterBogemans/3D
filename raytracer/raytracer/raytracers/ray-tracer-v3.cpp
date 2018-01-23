#include "ray-tracer-v3.h"
using namespace imaging;
using namespace math;

const imaging::Color raytracer::raytracers::_private_::RayTracerV3::process_light_ray(const Scene & scene, const MaterialProperties & prop, const Hit & hit, const math::Ray & ray, const LightRay & lightray) const
{
	Color result = RayTracerV2::process_light_ray(scene, prop, hit, ray, lightray);
	result += compute_specular(prop, hit, ray, lightray);
	
	return result;
}

const imaging::Color raytracer::raytracers::_private_::RayTracerV3::compute_specular(const MaterialProperties & prop, const Hit & hit, const math::Ray & ray, const LightRay & lightray) const
{
	//Reference : http://3dcg.ti.ucll.be/reference/lighting/specular/explanations.html
	
	if (prop.specular == colors::black()) {
		return colors::black();
	}
	else 
	{

		Vector3D incoming_light = (hit.position - lightray.ray.origin).normalized();
		Vector3D reflected_direction = incoming_light.reflect_by(hit.normal);
		Vector3D PE = (ray.origin - hit.position).normalized();

		double cosine = PE.dot(reflected_direction);
		
		if (cosine > 0) {
			return lightray.color * prop.specular * pow(cosine, prop.specular_exponent);
		}
		else
		{
			return colors::black();
		}

	}
}

raytracer::RayTracer raytracer::raytracers::v3()
{
	return raytracer::RayTracer(std::make_shared<raytracer::raytracers::_private_::RayTracerV3>());
}
