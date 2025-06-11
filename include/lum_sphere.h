#pragma once

#include "lum_hittable.h"

namespace Lumina
{
  class Sphere : public Hittable
  {
    public:
      Sphere() = default;
    Sphere(point3 center, double radius);
    virtual bool hit(const Ray& r, Interval ray_t_interval, hit_record& rec) const override;
    private:
      point3 center;
      double radius;
  };
}