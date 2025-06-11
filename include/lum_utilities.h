#pragma once
// common headers
#include <cmath>
#include <limits>
#include <memory>
#include <vector>
#include "lum_color.h"
#include "lum_ray.h"
#include "vec3.h"

using std::numeric_limits;
namespace Lumina
{
    // constants
    const double infinity = numeric_limits<double>::infinity();
    const double pi = 3.1415926535897932385;

    // utility functions

    inline double degrees_to_radians(double degrees)
    {
    return degrees * pi / 180.0;
    }
}
