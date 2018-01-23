#include "raytracers/ray-tracer-v2.h"

using namespace imaging;
using namespace math;
using namespace raytracer;


TraceResult raytracer::raytracers::_private_::RayTracerV2::trace(const Scene& scene, const Ray& ray) const
{
	Hit hit;

	// Ask the scene for the first positive hit, i.e. the closest hit in front of the eye
	// If there's a hit, find_first_positive_hit returns true and updates the hit object with information about the hit
	if (scene.root->find_first_positive_hit(ray, &hit))
	{
		// There's been a hit
		// Fill in TraceResult object with information about the trace

		//Initialize a Color result to colors::black(), i.e. with start with zero photons.
		Color result = colors::black();
		// The hit object contains the group id, just copy it (group ids are important for edge detection)
		unsigned group_id = hit.group_id;

		//Ask the hit.material for the MaterialProperties at the hit location.
		Material material = hit.material;
		hit.local_position;
		MaterialProperties prop = material->at(hit.local_position);

		// This ray tracer always returns ambient color in case of hit
		result = result + prop.ambient;

		result += process_lights(scene, prop, hit, ray);

		// The t-value indicates where the ray/scene intersection took place.
		// You can use ray.at(t) to find the xyz-coordinates in space.
		double t = hit.t;

		// Group all this data into a TraceResult object.
		return TraceResult(result, group_id, ray, t);
	}
	else
	{
		// The ray missed all objects in the scene
		// Return a TraceResult object representing "no hit found"
		// which is basically the same as returning black
		return TraceResult::no_hit(ray);
	}
}

const imaging::Color raytracer::raytracers::_private_::RayTracerV2::process_lights(const Scene & scene, const MaterialProperties & prop, const Hit & hit, const math::Ray & ray) const
{
	Color result = colors::black();
	for each (LightSource source in scene.light_sources)
	{
		result += process_light_source(scene, prop, hit, ray, source);
	}
	return result;
}

const imaging::Color raytracer::raytracers::_private_::RayTracerV2::process_light_source(const Scene & scene, const MaterialProperties & prop, const Hit & hit, const math::Ray & ray, LightSource source) const
{
	Color result = colors::black();

	for each (LightRay lightray in source->lightrays_to(hit.position))
	{
		result += process_light_ray(scene, prop, hit, ray, lightray);
	}
	return result;
}

const imaging::Color raytracer::raytracers::_private_::RayTracerV2::process_light_ray(const Scene & scene, const MaterialProperties & prop, const Hit & hit, const math::Ray & ray, const LightRay& lightray) const
{
	Color result = colors::black();

	result += compute_diffuse(prop, hit, ray, lightray);

	return result;

}

const imaging::Color raytracer::raytracers::_private_::RayTracerV2::compute_diffuse(const MaterialProperties & prop, const Hit & hit, const math::Ray & ray, const LightRay & lightray) const
{
	//reference : http://3dcg.ti.ucll.be/reference/lighting/diffuse/explanations.html

	double cosineAlpha = (lightray.ray.origin - hit.position).normalized().dot(hit.normal);

	if (cosineAlpha > 0)
	{	
		return cosineAlpha * (lightray.color)  *  (prop.diffuse);
	}
	else
	{
		return colors::black();
	}
}

raytracer::RayTracer raytracer::raytracers::v2()
{
	return raytracer::RayTracer(std::make_shared<raytracer::raytracers::_private_::RayTracerV2>());
}
