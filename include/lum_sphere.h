#pragma once

#include "lum_hittable.h"

namespace Lumina
{
  class Sphere : public Hittable
  {
    public:
      Sphere() = default;
    Sphere(point3 center, double radius);
    virtual bool hit(const Ray& r, double ray_t_min, double ray_t_max, hit_record& rec) const override;
    private:
      point3 center;
      double radius;
  };
}