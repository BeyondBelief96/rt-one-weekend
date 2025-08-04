#include "lum_sphere.h"

namespace Lumina
{
  Sphere::Sphere(point3 center, double radius, std::shared_ptr<Material> material) 
      : center(center, vec3(0,0,0)), radius(std::fmax(0, radius)), material(material) {};

  Sphere::Sphere(const point3& startPoint, const point3& endPoint, double radius, std::shared_ptr<Material> mat)
	  : center(startPoint, endPoint - startPoint), radius(std::fmax(0, radius)), material(mat)
  {
  }

  bool Sphere::hit(const Ray& r, Interval ray_t_interval, HitRecord& rec) const
  {
    // Vector from the ray origin to the center of the sphere.
    point3 currentCenter = center.at(r.getTime());
    vec3 oc = currentCenter - r.getOrigin();
    // The length squared of the direction of the ray.
    double a = r.getDirection().length_squared();
    // The dot product of the direction of the ray and the vector from the center of the sphere to the origin of the ray.
    double h = r.getDirection().dot(oc);
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
    if (!ray_t_interval.contains(root))
    {
      // Check the other root.
      root = (h + sqrtd) / a;
      if (!ray_t_interval.contains(root))
      {
        // If both roots are outside the range of the ray, return false.
        return false;
      }
    }

    // The root is the closest point of intersection.
    rec.t = root;
    rec.p = r.at(rec.t);
    // The outward normal is the direction of the ray at the point of intersection.
    vec3 outward_normal = (rec.p - currentCenter) / radius;
    rec.set_face_normal(r, outward_normal);
    rec.material = material;  
    return true;
    }
}