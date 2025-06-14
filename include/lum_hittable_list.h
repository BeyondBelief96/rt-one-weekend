#pragma once

#include <memory>
#include <vector>
#include "lum_hittable.h"

namespace Lumina
{
  class HittableList : public Hittable 
  {
    public:
      HittableList() = default;
      HittableList(std::shared_ptr<Hittable> object);
      void clear();
      void add(std::shared_ptr<Hittable> object);
      bool hit(const Ray& r, Interval ray_t_interval, HitRecord& rec) const override;
    private:
      std::vector<std::shared_ptr<Hittable>> objects;
  };
}