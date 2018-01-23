#include "primitives/bounding-box-accelerator.h"
#include "util/misc.h"
#include <math.h>
#include <assert.h>


using namespace raytracer;
using namespace math;

namespace raytracer
{
	namespace primitives
	{
		namespace _private_
		{
			class BoundingBoxAccelerator : public raytracer::primitives::_private_::PrimitiveImplementation
			{
			public:
				Box child;
				Primitive primitive;
				

				BoundingBoxAccelerator(const Primitive &primitive) : primitive(primitive), child(primitive->bounding_box()) {};

				Box bounding_box() const override 
				{
					return this->child;
				}

				std::vector<std::shared_ptr<Hit>> find_all_hits(const Ray& ray) const override
				{

					if (!child.is_hit_positively_by(ray))
					{
						return std::vector<std::shared_ptr<Hit>>();

					}

					return primitive->find_all_hits(ray);
				}



			};
		}
	}
}


Primitive raytracer::primitives::bounding_box_accelerator(const Primitive &primitive)
{
	return Primitive(std::make_shared<raytracer::primitives::_private_::BoundingBoxAccelerator>(primitive));
}
