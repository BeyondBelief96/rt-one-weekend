#pragma once

#include "lum_hittable.h"

namespace Lumina
{
  class Sphere : public Hittable
  {
    public:
        Sphere() = default;

        // Stationary sphere constructor
        Sphere(point3 center, double radius, std::shared_ptr<Material> material);
        
		// Moving sphere constructor
        Sphere(const point3& startPoint, const point3& endPoint, double radius, std::shared_ptr<Material> mat);

        virtual bool hit(const Ray& r, Interval ray_t_interval, HitRecord& rec) const override;
    private:
      Ray center;
      double radius;
      std::shared_ptr<Material> material;
  };
}