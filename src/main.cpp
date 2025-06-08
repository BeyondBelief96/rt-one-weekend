#include "color.h"
#include "vec3.h"
#include "ray.h"

color ray_color(const Ray& r) 
{
  vec3 unit_direction = unit_vector(r.getDirection());

  // Calculate the interpolation factor 'a' based on the y component of the unit direction vector.
  // The y component is normalized to the range [0, 1] by adding 1.0 and multiplying by 0.5.
  // This effectively maps the range [-1, 1] to [0, 1].
  // The y component of the unit direction vector is used to create a gradient effect in the sky.
  // The value of 'a' will be 0.0 when the y component is -1 (looking straight down) and 1.0 when the y component is 1 (looking straight up).
  // This creates a smooth transition from white at the top of the sky to light blue at the bottom.
  double a = 0.5 * (unit_direction.y() + 1.0);

  // Interpolate between white and a light blue color based on the y component of the ray direction.
  // The y component is used to create a gradient effect in the sky.
  // The color is white at the top (y = 1) and light blue at the bottom (y = -1).
  // The color is calculated as a linear interpolation between white (1.0, 1.0, 1.0) and light blue (0.5, 0.7, 1.0).
  // The interpolation factor 'a' is clamped between 0 and 1.
  return (1.0f - a) * color(1.0, 1.0, 1.0) + a * color(0.5, 0.7, 1.0);
}

int main() 
{
  // Image dimensions and setup
  double aspect_ratio = 16.0 / 9.0;
  int image_width = 1920;
  int image_height = int(image_width / aspect_ratio);
  image_height = (image_height < 1) ? 1 : image_height;

  // Camera setup.
  double focal_length = 1.0;
  double viewport_height = 2.0;
  double viewport_width = viewport_height * (double(image_width) / image_height);
  point3 camera_position = point3(0, 0, 0);
  
  // Define the viewport vectors based on the viewport dimensions.
  vec3 viewport_u = vec3(viewport_width, 0, 0);
  vec3 viewport_v = vec3(0, -viewport_height, 0);

  // Calculate the delta vectors for pixel size in the viewport.
  vec3 pixel_delta_u = viewport_u / image_width;
  vec3 pixel_delta_v = viewport_v / image_height;

  // Calculate the upper left corner of the viewport from the camera position.
  point3 viewport_upper_left = camera_position
  - vec3(0, 0, focal_length) // Move back along the z-axis.
  - viewport_u / 2.0 // move left half the viewport width.
  - viewport_v / 2.0; // move up half the viewport height.

  // Calculate the location of the pixel at (0, 0) in the viewport.
  // This is the upper left corner of the viewport.
  // The pixel at (0, 0) is offset by half a pixel in both u and v directions.
  point3 pixel00_location = viewport_upper_left + 0.5 * (pixel_delta_u + pixel_delta_v);

  // Initialize the PPM file
  std::string output_file = "image.ppm";
  init_ppm_file(output_file, image_width, image_height);

  // Output to console as before
  std::cout << "P3\n" << image_width << " " << image_height << "\n255\n";

  for (int j = 0; j < image_height; j++)
  {
    std::clog << "\rScanlines remaining: " << (image_height - j) << " " << std::flush;
    for (int i = 0; i < image_width; i++)
    {
      // Calculate the pixel location in the viewport.
      point3 pixel_center = pixel00_location + i * pixel_delta_u + j * pixel_delta_v;

      // Create a ray from the camera position to the pixel center.
      vec3 ray_direction = pixel_center - camera_position;
      // Create a ray from the camera to the pixel center.
      Ray r(camera_position, ray_direction);

      color pixel_color = ray_color(r);
      
      // Write to console
      write_color(std::cout, pixel_color);
      
      // Write to file
      write_color_to_file(output_file, pixel_color);
    }
  }

  std::clog << "\nDone.\n";
}