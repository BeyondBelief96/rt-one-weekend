#pragma once
// common headers
#include <cmath>
#include <limits>
#include <memory>
#include <random>
#include <vector>
#include "lum_ray.h"
#include "lum_vec3.h"
#include "lum_interval.h"

using std::numeric_limits;
namespace Lumina
{
    // aliases
    using color = vec3;
    // constants
    const double infinity = numeric_limits<double>::infinity();
    const double pi = 3.1415926535897932385;

    // utility functions

    inline double degrees_to_radians(double degrees)
    {
        return degrees * pi / 180.0;
    }

    // Returns a random number in the range of [0,1)
    inline double random_double()
    {
        static std::uniform_real_distribution<double> distribution(0.0, 1.0);
        static std::mt19937 generator;
        return distribution(generator);
    }

    // Returns a random number in the range of [min,max)
    inline double random_double(double min, double max)
    {
        return min + (max - min) * random_double();
    }

    inline double linear_to_gamma_2(double linear_component)
    {
        if (linear_component > 0.0)
        {
            return sqrt(linear_component);
        }
        else
        {
            return 0.0;
        }
    }
}
