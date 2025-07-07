#pragma once
#include "lum_material.h"

namespace Lumina
{
    class Lambertian : public Material
    {
        public:
            Lambertian(const color& albedo);
            bool Scatter(const Ray& r_in, const HitRecord& rec, color& attenuation, Ray& scattered) const override;
        private:
            color albedo;
    };
}