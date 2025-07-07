#include "lum_camera.h"
#include "image_output.h"
#include "materials/lum_material.h"
#include "lum_progress_visualizer.h"
#include <iostream>

namespace Lumina
{
    Camera::Camera() : 
        image_width(800),  // Default width
        aspect_ratio(16.0 / 9.0),  // Default aspect ratio
        samples_per_pixel(100),  // Default samples per pixel
        pixel_samples_scale(1.0 / samples_per_pixel),
        max_depth(50),  // Default maximum ray depth
		image_height(int(image_width / aspect_ratio)) // Calculate default height based on aspect ratio and width
    {
        Initialize();
    };

    void Camera::Initialize()
    {
        // Calculate image height based on aspect ratio
        // aspect_ratio = width/height, so height = width/aspect_ratio
        image_height = int(image_width / aspect_ratio);
        image_height = (image_height < 1) ? 1 : image_height;

        pixel_samples_scale = 1.0 / samples_per_pixel;

        // Set up camera position at origin
        position = point3(0, 0, 0);

        // Camera parameters
        double focal_length = 1.0;  // Distance from camera to viewport
        double viewport_height = 2.0;  // Height of the viewport in world units
        // Calculate viewport width to maintain aspect ratio
        double viewport_width = viewport_height * (double(image_width) / image_height);

        // Define the viewport vectors
        // viewport_u points right along the x-axis
        vec3 viewport_u = vec3(viewport_width, 0, 0);
        // viewport_v points down along the negative y-axis
        vec3 viewport_v = vec3(0, -viewport_height, 0);

        // Calculate the size of each pixel in world units
        // Divide viewport dimensions by number of pixels
        pixel_delta_u = viewport_u / image_width;  // Vector from one pixel to the next horizontally
        pixel_delta_v = viewport_v / image_height; // Vector from one pixel to the next vertically

        // Calculate the viewport's upper left corner
        // Start at camera position
        // Move back by focal_length along z-axis
        // Move left by half the viewport width
        // Move up by half the viewport height
        point3 viewport_upper_left = position
            - vec3(0, 0, focal_length)  // Move back along the z-axis
            - viewport_u / 2.0          // Move left half the viewport width
            - viewport_v / 2.0;         // Move up half the viewport height

        // Calculate the location of pixel (0,0)
        // Start at viewport_upper_left
        // Move right by half a pixel and down by half a pixel
        // This centers the first pixel in its grid cell
        pixel00_loc = viewport_upper_left + 0.5 * (pixel_delta_u + pixel_delta_v);
    }

    void Camera::Render(const Hittable& world, const std::string& output_file)
    {
        // Create progress visualizer
        ProgressVisualizer progress(image_height, 50);

        // Create a vector to store all pixels
        std::vector<color> pixels;
        pixels.reserve(image_width * image_height);

        // Render the image row by row, from top to bottom
        for (int j = 0; j < image_height; j++)
        {
            for (int i = 0; i < image_width; i++)
            {
                color pixel_color(0, 0, 0);
                for (int s = 0; s < samples_per_pixel; s++)
                {
                    Ray r = get_ray(i, j);
                    pixel_color += ray_color(r, world, max_depth);
                }

                // Average the samples
                pixel_color = pixel_color * pixel_samples_scale;
                pixels.push_back(pixel_color);
            }

            // Update progress after each scanline
            progress.update(j + 1);
        }

        // Finish progress display
        progress.finish();

        std::cout << "Writing output files...\n";

        // Write both PPM and PNG files
        write_ppm(output_file + ".ppm", pixels, image_width, image_height);
        write_png(output_file + ".png", pixels, image_width, image_height);

        std::cout << "Files written successfully!\n";
        std::cout << "   " << output_file << ".ppm\n";
        std::cout << "   " << output_file << ".png\n\n";
    }

    color Camera::ray_color(const Ray& r, const Hittable& world, int depth, bool use_lambertian_scatter) const
    {
        // If we've exceeded the ray bounce limit, no more light is gathered
        if (depth <= 0)
            return color(0,0,0);

        HitRecord rec;
        // Check if the ray hits any object in the world
        if (world.hit(r, Interval(0.001, infinity), rec)) {
            Ray scattered_ray;
            color attenuation;
            if (rec.material->Scatter(r, rec, attenuation, scattered_ray))
            {
                return attenuation * ray_color(scattered_ray, world, depth - 1);
            }
            else
            {
                return color(0, 0, 0);
            }
        }

        // If no hit, create a sky gradient
        vec3 unit_direction = r.getDirection().unit_vector();
        auto a = 0.5*(unit_direction.y() + 1.0);  // Map y from [-1,1] to [0,1]
        return (1.0-a)*color(1.0, 1.0, 1.0) + a*color(0.5, 0.7, 1.0);
    }

    Ray Camera::get_ray(int i, int j) const
    {
        // Get a random offset within the pixel
        vec3 offset = sample_square();

        // Calculate the pixel sample location in the viewport
        point3 pixel_sample = pixel00_loc
            + ((i + offset.x()) * pixel_delta_u)
            + ((j + offset.y()) * pixel_delta_v);

        // Create a ray from the camera position to the pixel sample
        vec3 ray_direction = pixel_sample - position;
        return Ray(position, ray_direction);
    }

    vec3 Camera::sample_square() const
    {
        // Returns a random point in the [-0.5, 0.5] square
        return vec3(random_double() - 0.5, random_double() - 0.5, 0);
    }
}