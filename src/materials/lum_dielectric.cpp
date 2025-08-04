#include "materials/lum_dielectric.h"


namespace Lumina
{
	Dielectric::Dielectric(double refraction_index) : refraction_index(refraction_index)
	{
	}

	bool Dielectric::Scatter(const Ray& r_in, const HitRecord& rec, color& attenuation, Ray& scattered) const
	{
		attenuation = color(1.0, 1.0, 1.0);
		double ri = rec.front_face ? (1.0 / refraction_index) : refraction_index;

		vec3 unit_direction = r_in.getDirection().unit_vector();
		double cos_theta = std::fmin(-unit_direction.dot(rec.normal), 1.0);
		double sin_theta = std::sqrt(1.0 - cos_theta * cos_theta);

		bool cannot_refract = ri * sin_theta > 1.0;
		vec3 direction;

		if (cannot_refract || reflectance(cos_theta, ri) > random_double())
		{
			direction = unit_direction.reflect(rec.normal);
		}
		else
		{
			direction = r_in.getDirection().refract(unit_direction, rec.normal, ri);
		}

		scattered = Ray(rec.p, direction, r_in.getTime());
		return true;
	}

	double Dielectric::reflectance(double cosine, double refraction_index)
	{
		// Use Schlick's approximation for reflectance
		auto r0 = (1.0 - refraction_index) / (1.0 + refraction_index);
		r0 = r0 * r0;
		return r0 + (1.0 - r0) * std::pow((1.0 - cosine), 5.0);
	}


}



