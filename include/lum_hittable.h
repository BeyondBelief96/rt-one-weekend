#pragma once

#include "lum_ray.h"
#include "lum_interval.h"
#include <memory>

namespace Lumina
{

  class Material;

  /// <summary>
  /// Stores information about a hit point on a hittable object.
  /// </summary>
  struct HitRecord
  {
    point3 p;
    vec3 normal;
    double t;
    std::shared_ptr<Material> material;
    bool front_face;

    // Set the face normal of the hit record.
    // If the dot product of the direction of the ray and the outward normal is less than 0, the ray is hitting the front face of the object.
    // Otherwise, the ray is hitting the back face of the object.
    // The normal is the direction of the ray at the point of intersection.
    //outward normal is assumed to be a unit vector.
    void set_face_normal(const Ray& r, const vec3& outward_normal) 
    {
      front_face = r.getDirection().dot(outward_normal) < 0;
      normal = front_face ? outward_normal : -outward_normal;
    }
  };

  class Hittable 
  {
    public:
      virtual ~Hittable() = default;
      virtual bool hit(const Ray& r, Interval ray_t_interval, HitRecord& rec) const = 0;
    private:

  };
}