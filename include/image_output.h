#pragma once

#include <string>
#include <vector>
#include "lum_utilities.h"

namespace Lumina 
{
    // Write image data to a PPM file
    void write_ppm(const std::string& filename, const std::vector<color>& pixels, int width, int height);

    // Write image data to a PNG file
    void write_png(const std::string& filename, const std::vector<color>& pixels, int width, int height);

    // Close a PPM file
    void close_ppm_file(const std::string& filename);

    // Close a PNG file
    void close_png_file(const std::string& filename);

} // namespace Lumina 