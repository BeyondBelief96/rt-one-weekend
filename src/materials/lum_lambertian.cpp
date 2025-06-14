#include "materials/lum_lambertian.h"
#include "lum_utilities.h"

namespace Lumina
{
    Lambertian::Lambertian(const color& a) : albedo(a) {}

    bool Lambertian::Scatter(const Ray& r_in, const HitRecord& rec, color& attenuation, Ray& scattered) const
    {
        vec3 scatter_direction = rec.p + vec3::random_unit_vector_in_unit_sphere();

        // Ensure the scatter direction is not zero, if so use the normal direction
        if(vec3::near_zero(scatter_direction)) 
        {
            scatter_direction = rec.normal;
        }
        scattered = Ray(rec.p, scatter_direction);
        attenuation = albedo;
        return true;
    }
}