#pragma once
#include "lum_material.h"

namespace Lumina
{
	class Metal : public Material
	{
	public:
		Metal(const color& albedo, double fuzz);
		bool Scatter(const Ray& r_in, const HitRecord& rec, color& attenuation, Ray& scattered) const override;
	private:
		color albedo;
		double fuzz;
	};
}