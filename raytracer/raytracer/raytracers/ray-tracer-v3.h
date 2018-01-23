#pragma once

#include "raytracers/ray-tracer.h"
#include "ray-tracer-v2.h"
#include <memory>



namespace raytracer
{
	namespace raytracers
	{
		namespace _private_
		{
			class RayTracerV3 : public RayTracerV2
			{
			protected:
				virtual const imaging::Color process_light_ray(const Scene&, const MaterialProperties&, const Hit&, const math::Ray&, const LightRay&) const override;
				const imaging::Color compute_specular(const MaterialProperties&, const Hit&, const math::Ray&, const LightRay&) const;
			};
		}


		RayTracer v3();
	}
}