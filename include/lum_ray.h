#pragma once

#include "lum_vec3.h"
namespace Lumina
{
  class Ray
  {
    public:
      Ray() {}

      Ray(const point3& origin, const vec3& direction);

      const point3& getOrigin() const;
      const vec3& getDirection() const;
      point3 at(double t) const;
    private:
      point3 origin;
      vec3 direction;
  };
}

