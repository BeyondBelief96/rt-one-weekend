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

      double x() const;
      double y() const;
      double z() const;

      double r() const;
      double g() const;
      double b() const;

      vec3 operator-() const;
      double operator[](int i) const;
      double& operator[](int i);

      vec3& operator+=(const vec3 &v);
      vec3& operator*=(double t);
      vec3& operator/=(double t);

      double length() const;
      double length_squared() const;
  };

  // point3 alias for geometric points
  using point3 = vec3;

  // vec3 utility function declarations
  std::ostream& operator<<(std::ostream& out, const vec3& v);
  vec3 operator+(const vec3& u, const vec3& v);
  vec3 operator-(const vec3& u, const vec3& v);
  vec3 operator*(const vec3& u, const vec3& v);
  vec3 operator*(double t, const vec3& v);
  vec3 operator*(const vec3& v, double t);
  vec3 operator/(const vec3& v, double t);
  double dot(const vec3& u, const vec3& v);
  vec3 cross(const vec3& u, const vec3& v);
  vec3 unit_vector(const vec3& v);
}