#include "image_output.h"
#include "lum_color.h"
#include <fstream>
#include <vector>
#include <stdexcept>
#include "stb_image_write.h"

namespace Lumina 
{

// Global variables to store image data
static std::ofstream ppm_file;
static std::vector<unsigned char> png_data;
static int png_width = 0;
static int png_height = 0;

void init_ppm_file(const std::string& filename, int width, int height) {
    ppm_file.open(filename);
    if (!ppm_file.is_open()) {
        throw std::runtime_error("Could not open PPM file: " + filename);
    }
    ppm_file << "P3\n" << width << " " << height << "\n255\n";
}

void init_png_file(const std::string& filename, int width, int height) {
    png_width = width;
    png_height = height;
    png_data.resize(width * height * 3); // 3 channels (RGB)
}

void write_color_to_ppm(const std::string& filename, const Lumina::color& pixel_color) {
    ppm_file << static_cast<int>(255.999 * pixel_color.x()) << ' '
             << static_cast<int>(255.999 * pixel_color.y()) << ' '
             << static_cast<int>(255.999 * pixel_color.z()) << '\n';
}

void color_to_rgb(const Lumina::color& pixel_color, unsigned char* rgb) {
    rgb[0] = static_cast<unsigned char>(255.999 * pixel_color.x());
    rgb[1] = static_cast<unsigned char>(255.999 * pixel_color.y());
    rgb[2] = static_cast<unsigned char>(255.999 * pixel_color.z());
}

void write_color_to_png(const std::string& filename, const Lumina::color& pixel_color, int x, int y) {
    unsigned char rgb[3];
    color_to_rgb(pixel_color, rgb);
    
    int index = (y * png_width + x) * 3;
    png_data[index] = rgb[0];
    png_data[index + 1] = rgb[1];
    png_data[index + 2] = rgb[2];
}

void close_ppm_file(const std::string& filename) {
    if (ppm_file.is_open()) {
        ppm_file.close();
    }
}

void close_png_file(const std::string& filename) {
    if (!png_data.empty()) {
        stbi_write_png(filename.c_str(), png_width, png_height, 3, png_data.data(), png_width * 3);
        png_data.clear();
    }
}

}