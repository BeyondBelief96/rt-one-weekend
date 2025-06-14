cmake_minimum_required(VERSION 3.10)

# Set the project name and version
project(RayTracer VERSION 1.0)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Generate compile commands database
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Add include directories
include_directories(${PROJECT_SOURCE_DIR}/include)

# Add executable
add_executable(raytracer
 src/main.cpp
 src/lum_vec3.cpp
 src/lum_ray.cpp
 src/lum_sphere.cpp
 src/lum_hittable_list.cpp
 src/lum_interval.cpp
 src/image_output.cpp
 src/lum_camera.cpp
 src/materials/lum_lambertian.cpp)


# Set output directories
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
