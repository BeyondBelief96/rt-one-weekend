#pragma once

#include "lum_hittable.h"

namespace Lumina
{
  class Sphere : public Hittable
  {
    public:
        Sphere() = default;
        Sphere(point3 center, double radius, std::shared_ptr<Material> material);
            virtual bool hit(const Ray& r, Interval ray_t_interval, HitRecord& rec) const override;
    private:
      point3 center;
      double radius;
      std::shared_ptr<Material> material;
  };
}