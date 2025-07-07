#pragma once

#include "lum_ray.h"
#include "lum_hittable.h"
#include "lum_vec3.h"
#include "lum_utilities.h"
#include <string>
#include <vector>

namespace Lumina
{
    class Camera
    {
        public:
            Camera();
            void Initialize();
            void Render(const Hittable& world, const std::string& output_file = "output");

            // Image settings
            double aspect_ratio = 16.0 / 9.0;  // Ratio of image width to height
            int image_width = 1920;            // Width of the image
            int samples_per_pixel = 10;        // Number of samples per pixel
            int max_depth  = 10;               // Maximum number of ray bounces into scene

        private:
            // Camera settings
            int    image_height;   // Rendered image height
            point3 position;       // Camera eye position
            double pixel_samples_scale;  // Color scale factor for a sum of pixel samples to average them
            point3 pixel00_loc;    // Location of pixel 0, 0
            vec3   pixel_delta_u;  // Offset to pixel to the right
            vec3   pixel_delta_v;  // Offset to pixel below

            // Camera setup
            color ray_color(const Ray& r, const Hittable& world, int depth, bool use_lambertian_scatter = true) const;
            Ray get_ray(int i, int j) const;
            vec3 sample_square() const;
    };
}
