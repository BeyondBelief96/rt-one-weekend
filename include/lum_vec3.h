#pragma once

#include <cmath>
#include <iostream>

namespace Lumina
{
  class vec3
  {
    public:
      double e[3];

      vec3();
      vec3(double e0, double e1, double e2);

      // Component accessors
      double x() const;
      double y() const;
      double z() const;
      double r() const;
      double g() const;
      double b() const;

      // Vector operations
      vec3 operator-() const;
      double operator[](int i) const;
      double& operator[](int i);

      vec3& operator+=(const vec3 &v);
      vec3& operator*=(double t);
      vec3& operator/=(double t);

      vec3 operator+(const vec3& v) const;
      vec3 operator-(const vec3& v) const;
      vec3 operator*(const vec3& v) const;
      vec3 operator*(double t) const;
      vec3 operator/(double t) const;

      double length() const;
      double length_squared() const;
      double dot(const vec3& v) const;
      vec3 cross(const vec3& v) const;
      vec3 unit_vector() const;

      // Static methods
      static vec3 random();
      static vec3 random(double min, double max);
      static vec3 random_unit_vector_in_unit_sphere();
      static vec3 random_on_hemisphere(const vec3& normal);
  };

  // point3 alias for geometric points
  using point3 = vec3;

  // Non-member operators that use public interface
  std::ostream& operator<<(std::ostream& out, const vec3& v);
  vec3 operator*(double t, const vec3& v);
}