#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include "lum_utilities.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION
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

    void color_to_rgb(const Lumina::color& pixel_color, unsigned char* rgb) {
        rgb[0] = static_cast<unsigned char>(255.999 * linear_to_gamma_2(pixel_color.x()));
        rgb[1] = static_cast<unsigned char>(255.999 * linear_to_gamma_2(pixel_color.y()));
        rgb[2] = static_cast<unsigned char>(255.999 * linear_to_gamma_2(pixel_color.z()));
}

    void close_ppm_file(const std::string& filename) {
        if (ppm_file.is_open()) {
            ppm_file.close();
        }
    }

    void close_png_file(const std::string& filename) {
        if (!png_data.empty()) {
            if (!stbi_write_png(filename.c_str(), png_width, png_height, 3, png_data.data(), png_width * 3)) {
                std::cerr << "Error: Could not write PNG file " << filename << std::endl;
            }
            png_data.clear();
        }
    }

    void write_ppm(const std::string& filename, const std::vector<color>& pixels, int width, int height) {
        std::ofstream out(filename);
        if (!out) {
            std::cerr << "Error: Could not open file " << filename << " for writing" << std::endl;
            return;
        }

        // Write PPM header
        out << "P3\n" << width << " " << height << "\n255\n";

        // Write pixel data
        for (const auto& pixel : pixels) {
            // Convert from [0,1] to [0,255] and clamp
            static const Interval intensity(0.000, 0.999);
            int r = static_cast<int>(256 * intensity.clamp(linear_to_gamma_2(pixel.x())));
            int g = static_cast<int>(256 * intensity.clamp(linear_to_gamma_2(pixel.y())));
            int b = static_cast<int>(256 * intensity.clamp(linear_to_gamma_2(pixel.z())));
            out << r << " " << g << " " << b << "\n";
        }

        close_ppm_file(filename);
    }

    void write_png(const std::string& filename, const std::vector<color>& pixels, int width, int height) {
        // Convert pixels to RGB format
        std::vector<unsigned char> rgb_data(width * height * 3);
        for (int i = 0; i < pixels.size(); ++i) {
            static const Interval intensity(0.000, 0.999);
            rgb_data[i * 3] = static_cast<unsigned char>(256 * intensity.clamp(linear_to_gamma_2(pixels[i].x())));
            rgb_data[i * 3 + 1] = static_cast<unsigned char>(256 * intensity.clamp(linear_to_gamma_2(pixels[i].y())));
            rgb_data[i * 3 + 2] = static_cast<unsigned char>(256 * intensity.clamp(linear_to_gamma_2(pixels[i].z())));
        }

        // Write PNG file
        if (!stbi_write_png(filename.c_str(), width, height, 3, rgb_data.data(), width * 3)) {
            std::cerr << "Error: Could not write PNG file " << filename << std::endl;
        }

        close_png_file(filename);
    }
}