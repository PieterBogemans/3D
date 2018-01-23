#include "samplers/random-sampler.h"
#include <random>

using namespace math;
using namespace raytracer;

namespace
{
	class RandomSampler : public raytracer::samplers::_private_::SamplerImplementation
	{


	public:
		RandomSampler(int m_sample_count) :m_sample_count(m_sample_count) {}
		int m_sample_count;

		std::vector<Point2D> sample(const math::Rectangle2D& rectangle) const override
		{

			
			std::vector<math::Point2D> list;

			//std::random_device rd;  //Will be used to obtain a seed for the random number engine
			//std::mt19937 gen(rd()); //Standard mersenne_twister_engine seeded with rd()
			//std::uniform_real_distribution<> dis(0, 1);
			for (int i = 0; i < m_sample_count; i++)
			{
				list.push_back(rectangle.from_relative(Point2D(rand() / (RAND_MAX + 1.), rand() / (RAND_MAX + 1.))));
			}

			return list;
		}
	};
}

Sampler raytracer::samplers::random(int x)
{
	return Sampler(std::make_shared<RandomSampler>(x));
}