#include "primitives/triangle-primitive.h"
#include "util/misc.h"
#include "math/coordinate-systems.h"
#include "math/quadratic_equation.h"
#include "performance/performance.h"
#include <assert.h>

using namespace raytracer;
using namespace raytracer::primitives;
using namespace math;

namespace
{
	class TriangleImplementation : public raytracer::primitives::_private_::PrimitiveImplementation
	{
	public:
		TriangleImplementation(Point3D p1, Point3D p2, Point3D p3)
			: _p1(p1), _p2(p2), _p3(p3)
		{
			normal = (_p2 - _p1).normalized().cross((_p3 - _p1).normalized());
		}
		Point3D _p1;
		Point3D _p2;
		Point3D _p3;
		Vector3D normal;
	private:

		std::vector<std::shared_ptr<Hit>> find_all_hits(const Ray& ray) const override
		{
			std::vector<std::shared_ptr<Hit>> hits;

			double t = (_p1 - ray.origin).dot(normal) / (ray.direction.dot(normal));
			Point3D hitPosition = ray.origin + ray.direction * t;
			
			double p1p2Check = ((_p2 - _p1).cross(hitPosition - _p1)).dot(normal);
			double p2p3Check = ((_p3 - _p2).cross(hitPosition - _p2)).dot(normal);
			double p3p1Check = ((_p1 - _p3).cross(hitPosition - _p3)).dot(normal);
			
			if (p1p2Check >= 0 && p2p3Check >= 0 && p3p1Check >= 0)
			{
				auto hit = std::make_shared<Hit>();
				hit->t = t;
				hit->position = ray.at(t);
				hit->local_position.xyz = hit->position;
				hit->local_position.uv = Point2D(0, 0);
				hits.push_back(hit);
			}
			return hits;
		}
		bool find_first_positive_hit(const math::Ray& ray, Hit* hit) const override
		{
			auto hits = find_all_hits(ray);
			if (hits.size() > 0)
			{
				auto found = hits.back();
				if (found->t > 0 && found->t < hit->t)
				{
					*hit = *found;
					return true;
				}
			}
			return false;
		}
		
		math::Box bounding_box() const override
		{
			auto range = interval(-1.0, 1.0);

			return Box(range, range, range);
		}
		
	};
}
Primitive raytracer::primitives::triangle(Point3D p1, Point3D p2, Point3D p3)
{
	return Primitive(std::make_shared<TriangleImplementation>(p1, p2, p3));
}