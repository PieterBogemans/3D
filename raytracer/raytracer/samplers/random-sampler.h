#pragma once

#include "samplers/sampler.h"


namespace raytracer
{
	namespace samplers
	{
		/// <summary>
		/// Gives back x(int) random points 
		/// </summary>
		Sampler random(int);
	}
}