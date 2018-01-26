#include "lights/spot-light.h"

using namespace raytracer;
using namespace math;

namespace
{
	class SpotLight : public raytracer::lights::_private_::PointLightImplementation
	{
	public:
		SpotLight(const Point3D& point, const Vector3D& direction, const Angle& angle, const imaging::Color& color)
			: PointLightImplementation(point), _direction(direction), _angle(angle), _color(color) {}

	protected:
		LightRay cast_lightray_to(const Point3D& point) const override
		{
			Ray ray(m_position, point);
			if ((point - m_position).normalized().dot(_direction) >= cos(_angle / 2))
			{
				return LightRay(ray, _color);
			}
			return LightRay(ray, imaging::colors::black());
		}

	private:
		imaging::Color _color;
		Angle _angle;
		Vector3D _direction;
	};
}

LightSource raytracer::lights::spot(const Point3D& point, const Vector3D& direction, const Angle& angle, const imaging::Color& color)
{
	return LightSource(std::make_shared<SpotLight>(point, direction, angle, color));
}