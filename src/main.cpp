#include "lum_utilities.h"
#include "image_output.h"
#include "lum_sphere.h"
#include "lum_hittable.h"
#include "lum_hittable_list.h"
#include "lum_camera.h"
#include "materials/lum_material.h"
#include "materials/lum_lambertian.h"
#include "materials/lum_metal.h"
#include <vector>
#include <filesystem>
#include <string>
#include <iostream>

using namespace Lumina;

int main(int argc, char* argv[])
{
    // Get output filename from command line arguments or use default
    std::string output_filename;
    if (argc > 1) {
        output_filename = argv[1];
    }
    else {
        output_filename = "output";
    }

    // Create output directory if it doesn't exist
    std::filesystem::create_directory("output");

    // World setup
    HittableList world;
    auto material_ground = std::make_shared<Lambertian>(color(0.8, 0.8, 0.0));
    auto material_center = std::make_shared<Lambertian>(color(0.1, 0.2, 0.5));
    auto material_left = std::make_shared<Metal>(color(0.8, 0.8, 0.8), 0.3);
    auto material_right = std::make_shared<Metal>(color(0.8, 0.6, 0.2), 0.1);

    world.add(std::make_shared<Sphere>(point3(0.0, -100.5, -1.0), 100.0, material_ground));
    world.add(std::make_shared<Sphere>(point3(0.0, 0.0, -1.2), 0.5, material_center));
    world.add(std::make_shared<Sphere>(point3(-1.0, 0.0, -1.0), 0.5, material_left));
    world.add(std::make_shared<Sphere>(point3(1.0, 0.0, -1.0), 0.5, material_right));

    // Camera setup
    Camera camera{};
    camera.aspect_ratio = 16.0 / 9.0;
    camera.image_width = 1920;
    camera.samples_per_pixel = 100;
    camera.show_progress = true;  // Enable the cool progress visualization!
    camera.Initialize();

    // Construct the full output path
    std::string output_path = "output/" + output_filename;

    // Print initial info
    std::cout << "Target: " << output_path << ".ppm and " << output_path << ".png\n";
    std::cout << "Resolution: " << camera.image_width << "x" << int(camera.image_width / camera.aspect_ratio) << "\n";
    std::cout << "Samples per pixel: " << camera.samples_per_pixel << "\n\n";

    // Render the scene with the cool progress visualization
    camera.Render(world, output_path);

    return 0;
}