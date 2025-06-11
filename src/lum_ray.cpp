#include "lum_ray.h"

namespace Lumina
{
    Ray::Ray(const point3& origin, const vec3& direction) : origin(origin), direction(direction) {}

    const point3& Ray::getOrigin() const { return origin; }

    const vec3& Ray::getDirection() const { return direction; }

    point3 Ray::at(double t) const { return origin + t * direction; }
}
