#include "lum_utilities.h"
#include "image_output.h"
#include "lum_sphere.h"
#include "lum_hittable.h"
#include "hittable_list.h"
#include <vector>

using namespace Lumina;


color ray_color(const Ray& r, const Hittable& world) {
    hit_record rec;
    if (world.hit(r, Interval(0, infinity), rec)) {
        return 0.5 * (rec.normal + color(1,1,1));
    }

    vec3 unit_direction = unit_vector(r.getDirection());
    auto a = 0.5*(unit_direction.y() + 1.0);
    return (1.0-a)*color(1.0, 1.0, 1.0) + a*color(0.5, 0.7, 1.0);
}


int main() 
{
  // Image dimensions and setup
  double aspect_ratio = 16.0 / 9.0;
  int image_width = 1920;
  int image_height = int(image_width / aspect_ratio);
  image_height = (image_height < 1) ? 1 : image_height;

  // World setup

  HittableList world;
  world.add(std::make_shared<Sphere>(point3(0,0,-1), 0.5));
  world.add(std::make_shared<Sphere>(point3(0,-100.5,-1), 100));

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

  // Create a vector to store all pixels
  std::vector<color> pixels;
  pixels.reserve(image_width * image_height);

  // Output progress to console
  std::cout << "Rendering image...\n";

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

      color pixel_color = ray_color(r, world);
      pixels.push_back(pixel_color);
    }
  }

  std::clog << "\nWriting output files...\n";

  // Write both PPM and PNG files
  write_ppm("output.ppm", pixels, image_width, image_height);
  write_png("output.png", pixels, image_width, image_height);

  std::clog << "Done.\n";
}