#pragma once

#include "vec3.h"
#include <iostream>
#include <fstream>
#include <string>

namespace Lumina
{
  using color = vec3;

  // Standard write to stream function
  void write_color(std::ostream& out, color pixel_color)
  {
    auto r = pixel_color.x();
    auto g = pixel_color.y();
    auto b = pixel_color.z();

    // Translate the [0,1] component values to the byte range [0,255].  
    out << static_cast<int>(255.999 * r) << ' '
        << static_cast<int>(255.999 * g) << ' '
        << static_cast<int>(255.999 * b) << '\n';
  }

  // New function to initialize PPM file
  void init_ppm_file(const std::string& filename, int width, int height) {
    std::ofstream file(filename);
    if (file.is_open()) {
      file << "P3\n" << width << " " << height << "\n255\n";
      file.close();
    } else {
      std::cerr << "Could not open file: " << filename << std::endl;
    }
  }

  // New function to write color to PPM file
  void write_color_to_file(const std::string& filename, color pixel_color, bool append = true) {
    std::ofstream file(filename, append ? std::ios::app : std::ios::out);
    if (file.is_open()) {
      auto r = pixel_color.x();
      auto g = pixel_color.y();
      auto b = pixel_color.z();

      // Translate the [0,1] component values to the byte range [0,255].
      file << static_cast<int>(255.999 * r) << ' '
          << static_cast<int>(255.999 * g) << ' '
          << static_cast<int>(255.999 * b) << '\n';
      file.close();
    } else {
      std::cerr << "Could not open file: " << filename << std::endl;
    }
  }
}