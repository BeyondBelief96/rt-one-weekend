#pragma once

#include <string>
#include <vector>
#include "lum_color.h"

namespace Lumina 
{

// Write image data to a PPM file
void write_ppm(const std::string& filename, const std::vector<color>& pixels, int width, int height);

// Write image data to a PNG file
void write_png(const std::string& filename, const std::vector<color>& pixels, int width, int height);

} // namespace Lumina 