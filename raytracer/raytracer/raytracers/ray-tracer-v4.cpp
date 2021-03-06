#include "ray-tracer-v4.h"
using namespace imaging;
using namespace math;
using namespace raytracer;

const imaging::Color raytracer::raytracers::_private_::RayTracerV4::process_light_ray(const Scene & scene, const MaterialProperties & prop, const Hit & hit, const math::Ray & ray, const LightRay & lightray) const
{
	Hit newHit;
	

	scene.root->find_first_positive_hit(lightray.ray, &newHit);
	
	if (0.99999 > newHit.t && newHit.t >= 0)
	{
		return colors::black();
	}
	else
	{
		return RayTracerV3::process_light_ray(scene, prop, hit, ray, lightray);

	}
	
}

raytracer::RayTracer raytracer::raytracers::v4()
{
	return raytracer::RayTracer(std::make_shared<raytracer::raytracers::_private_::RayTracerV4>());
}
