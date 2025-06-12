#include "lum_utilities.h"
#include "image_output.h"
#include "lum_sphere.h"
#include "lum_hittable.h"
#include "lum_hittable_list.h"
#include "lum_camera.h"
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
    } else {
        output_filename = "output";
    }
    std::cout << "Output filename: " << output_filename << std::endl;

    // Create output directory if it doesn't exist
    std::filesystem::create_directory("output");

    // Image dimensions and setup
    double aspect_ratio = 16.0 / 9.0;
    int image_width = 1920;

    // World setup
    HittableList world;
    world.add(std::make_shared<Sphere>(point3(0,0,-1), 0.5));
    world.add(std::make_shared<Sphere>(point3(0,-100.5,-1), 100));

    // Camera setup
    Camera camera{};
    camera.aspect_ratio = 16.0 / 9.0;
    camera.image_width = 1920;
    camera.samples_per_pixel = 100;
    camera.Initialize();

    // Construct the full output path
    std::string output_path = "output/" + output_filename;
    std::cout << "Writing to: " << output_path << ".ppm and " << output_path << ".png" << std::endl;

    // Render the scene with the specified filename
    camera.Render(world, output_path);

    return 0;
}