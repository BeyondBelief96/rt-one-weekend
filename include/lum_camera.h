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
            double aspect_ratio = 16.0 / 9.0;   // Ratio of image width to height
            int image_width = 1920;             // Width of the image
            int samples_per_pixel = 10;         // Number of samples per pixel
            int max_depth  = 10;                // Maximum number of ray bounces into scene
			double vfov = 90.0;                 // Vertical field of view in degrees
			point3 look_from = point3(0, 0, 0); // Camera position in world space
			point3 look_at = point3(0, 0, -1);  // Point the camera is looking at
			vec3 up = vec3(0, 1, 0);            // Up direction for the camera
			double defocus_angle = 0.0; 	    // Angle for defocus blur
			double focus_distance = 10.0;       // Distance to the focus point
            bool show_progress = true;          // Whether to show progress visualization

        private:
            // Camera settings
            int    image_height;   // Rendered image height
            point3 position;       // Camera eye position
            double pixel_samples_scale;  // Color scale factor for a sum of pixel samples to average them
            point3 pixel00_loc;    // Location of pixel 0, 0
            vec3   pixel_delta_u;  // Offset to pixel to the right
            vec3   pixel_delta_v;  // Offset to pixel below
            vec3   u, v, w;        // Camera frame basis vectors
			vec3   defocus_u, defocus_v; // Basis vectors for defocus blur

            // Camera setup
            color ray_color(const Ray& r, const Hittable& world, int depth, bool use_lambertian_scatter = true) const;
            Ray get_ray(int i, int j) const;
            vec3 sample_square() const;
            point3 defocus_disk_sample() const;
    };
}
