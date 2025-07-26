#pragma once
#include "lum_material.h"

namespace Lumina
{
	class Dielectric : public Material
	{
	public:
		Dielectric(double refraction_index);
		bool Scatter(const Ray& r_in, const HitRecord& rec, color& attenuation, Ray& scattered) const override;
	private:
		// Refractive index in vacuum or air, or the ratio of the material's refractive index over
		// the refractive index of the enclosing media
		double refraction_index;

		static double reflectance(double cosine, double refraction_index);
	};
}