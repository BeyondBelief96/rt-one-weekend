#include "lum_sphere.h"

namespace Lumina
{
  Sphere::Sphere(point3 center, double radius) : center(center), radius(radius) {};

  bool Sphere::hit(const Ray& r, double ray_t_min, double ray_t_max, hit_record& rec) const
  {
    // Vector from the center of the sphere to the origin of the ray.
    vec3 oc = r.getOrigin() - center;
    // The length squared of the direction of the ray.
    double a = r.getDirection().length_squared();
    // The dot product of the direction of the ray and the vector from the center of the sphere to the origin of the ray.
    double h = dot(r.getDirection(), oc);
    // The length squared of the vector from the center of the sphere to the origin of the ray minus the radius squared.
    double c = oc.length_squared() - radius * radius;
    double discriminant = h * h - a * c;

    if(discriminant < 0)
    {
      return false;
    }

    double sqrtd = std::sqrt(discriminant);
    double root = (h - sqrtd) / a;

    // Check if the root is within the range of the ray.
    if (root <= ray_t_min || ray_t_max <= root)
    {
      // Check the other root.
      root = (h + sqrtd) / a;
      if (root <= ray_t_min || ray_t_max <= root)
      {
        // If both roots are outside the range of the ray, return false.
        return false;
      }
    }

    // The root is the closest point of intersection.
    rec.t = root;
    rec.p = r.at(rec.t);
    // The outward normal is the direction of the ray at the point of intersection.
    vec3 outward_normal = (rec.p - center) / radius;
    rec.set_face_normal(r, outward_normal);
    return true;
    }
}