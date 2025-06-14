#pragma once

#include "lum_hittable.h"
#include "lum_utilities.h"

namespace Lumina
{
    class Material
    {
        public:
            virtual ~Material() = default;
            virtual bool Scatter(const Ray& r_in, const HitRecord& rec, color& attenuation, Ray& scattered) const = 0;
    };
}