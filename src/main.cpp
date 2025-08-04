#include "lum_utilities.h"
#include "image_output.h"
#include "lum_sphere.h"
#include "lum_hittable.h"
#include "lum_hittable_list.h"
#include "lum_camera.h"
#include "materials/lum_material.h"
#include "materials/lum_lambertian.h"
#include "materials/lum_metal.h"
#include "materials/lum_dielectric.h"
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
    auto ground_material = std::make_shared<Lambertian>(color(0.5, 0.5, 0.5));
    world.add(std::make_shared<Sphere>(point3(0, -1000, 0), 1000, ground_material));

    for (int a = -11; a < 11; a++) {
        for (int b = -11; b < 11; b++) {
            auto choose_mat = random_double();
            point3 center(a + 0.9 * random_double(), 0.2, b + 0.9 * random_double());

            if ((center - point3(4, 0.2, 0)).length() > 0.9) {
                std::shared_ptr<Material> sphere_material;

                if (choose_mat < 0.8) {
                    // diffuse
                    auto albedo = color::random() * color::random();
                    sphere_material = std::make_shared<Lambertian>(albedo);
                    auto center2 = center + vec3(0, random_double(0, 0.5), 0);
                    world.add(std::make_shared<Sphere>(center, center2, 0.2, sphere_material));
                }
                else if (choose_mat < 0.95) {
                    // metal
                    auto albedo = color::random(0.5, 1);
                    auto fuzz = random_double(0, 0.5);
                    sphere_material = std::make_shared<Metal>(albedo, fuzz);
                    world.add(std::make_shared<Sphere>(center, 0.2, sphere_material));
                }
                else {
                    // glass
                    sphere_material = std::make_shared<Dielectric>(1.5);
                    world.add(std::make_shared<Sphere>(center, 0.2, sphere_material));
                }
            }
        }
    }

    auto material1 = std::make_shared<Dielectric>(1.5);
    world.add(std::make_shared<Sphere>(point3(0, 1, 0), 1.0, material1));

    auto material2 = std::make_shared<Lambertian>(color(0.4, 0.2, 0.1));
    world.add(std::make_shared<Sphere>(point3(-4, 1, 0), 1.0, material2));

    auto material3 = std::make_shared<Metal>(color(0.7, 0.6, 0.5), 0.0);
    world.add(std::make_shared<Sphere>(point3(4, 1, 0), 1.0, material3));

    // Camera setup
    Camera camera{};
    camera.aspect_ratio = 16.0 / 9.0;
    camera.image_width = 1920;
    camera.samples_per_pixel = 10;
    camera.look_from = point3(13, 2, 3);
    camera.look_at = point3(0, 0, 0);
    camera.up = vec3(0, 1, 0);
    camera.vfov = 20.0;
    camera.defocus_angle = 0.6;
    camera.focus_distance = 10.0;
    camera.show_progress = true;
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