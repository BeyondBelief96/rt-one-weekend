#include "materials/lum_metal.h"

namespace Lumina
{
	Metal::Metal(const color& albedo, double fuzz) : albedo(albedo), fuzz(fuzz)
	{
	}

	bool Metal::Scatter(const Ray& r_in, const HitRecord& rec, color& attenuation, Ray& scattered) const
	{
		vec3 reflected_direction = r_in.getDirection().reflect(rec.normal);
		reflected_direction = reflected_direction.unit_vector() + (fuzz * vec3::random_unit_vector_in_unit_sphere());
		scattered = Ray(rec.p, reflected_direction);
		attenuation = albedo;
		return scattered.getDirection().dot(rec.normal) > 0;
	}
}