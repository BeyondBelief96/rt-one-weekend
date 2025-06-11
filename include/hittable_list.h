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
      bool hit(const Ray& r, double ray_t_min, double ray_t_max, hit_record& rec) const override;
    private:
      std::vector<std::shared_ptr<Hittable>> objects;
  };
}