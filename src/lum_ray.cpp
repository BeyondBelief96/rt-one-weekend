#include "lum_ray.h"


namespace Lumina
{
	Ray::Ray(const point3& origin, const vec3& direction) : origin(origin), direction(direction), time(0.0)
    {
    }
    Ray::Ray(const point3& origin, const vec3& direction, const double ray_time)
        : origin(origin), direction(direction), time(ray_time) {}

    const point3& Ray::getOrigin() const { return origin; }

    const vec3& Ray::getDirection() const { return direction; }

    const double Ray::getTime() const
    {
        return time;
    }

    point3 Ray::at(double t) const { return origin + t * direction; }
}
