#include "lum_vec3.h"
#include "lum_utilities.h"

namespace Lumina
{
  vec3::vec3()
  {
    e[0] = 0;
    e[1] = 0;
    e[2] = 0;
  }

  vec3::vec3(double e0, double e1, double e2)
  {
    e[0] = e0;
    e[1] = e1;
    e[2] = e2;
  }

  vec3 vec3::operator-() const
  {
    return vec3(-e[0], -e[1], -e[2]);
  }

  double vec3::operator[](int i) const
  {
      return e[i];
  }

  double& vec3::operator[](int i)
  {
      return e[i];
  }

  double vec3::x() const { return e[0]; }
  double vec3::y() const { return e[1]; }
  double vec3::z() const { return e[2]; }
  double vec3::r() const { return e[0]; }
  double vec3::g() const { return e[1]; }
  double vec3::b() const { return e[2]; }

  vec3& vec3::operator+=(const vec3 &v)
  {
    e[0] += v.e[0];
    e[1] += v.e[1];
    e[2] += v.e[2];
    return *this;
  }

  vec3& vec3::operator*=(double t)
  {
    e[0] *= t;
    e[1] *= t;
    e[2] *= t;
    return *this;
  }

  vec3& vec3::operator/=(double t)
  {
    return *this *= 1/t;
  }

  vec3 vec3::operator+(const vec3& v) const
  {
    return vec3(e[0] + v.e[0], e[1] + v.e[1], e[2] + v.e[2]);
  }

  vec3 vec3::operator-(const vec3& v) const
  {
    return vec3(e[0] - v.e[0], e[1] - v.e[1], e[2] - v.e[2]);
  }

  vec3 vec3::operator*(const vec3& v) const
  {
    return vec3(e[0] * v.e[0], e[1] * v.e[1], e[2] * v.e[2]);
  }

  vec3 vec3::operator*(double t) const
  {
    return vec3(t * e[0], t * e[1], t * e[2]);
  }

  vec3 vec3::operator/(double t) const
  {
    return (1/t) * (*this);
  }

  double vec3::length() const
  {
    return std::sqrt(length_squared());
  }

  double vec3::length_squared() const
  {
    return e[0] * e[0] + e[1] * e[1] + e[2] * e[2];
  }

  double vec3::dot(const vec3& v) const
  {
    return e[0] * v.e[0] + e[1] * v.e[1] + e[2] * v.e[2];
  }

  vec3 vec3::cross(const vec3& v) const
  {
    return vec3(e[1] * v.e[2] - e[2] * v.e[1],
                e[2] * v.e[0] - e[0] * v.e[2],
                e[0] * v.e[1] - e[1] * v.e[0]);
  }

  vec3 vec3::unit_vector() const
  {
    return *this / length();
  }

  vec3 vec3::reflect(const vec3& normal) const  
  {  
      return *this - 2 * dot(normal) * normal;  
  }

  vec3 vec3::random()
  {
    return vec3(random_double(), random_double(), random_double());
  }

  vec3 vec3::random(double min, double max)
  {
    return vec3(random_double(min, max), random_double(min, max), random_double(min, max));
  }

  /// <summary>
  /// Generates a random unit vector that lies within a unit sphere.
  /// </summary>
  /// <returns>A vec3 that lies on a point on a unit sphere.</returns>
  vec3 vec3::random_unit_vector_in_unit_sphere()
  {
    while(true) {
      vec3 p = random(-1, 1);
      double len_sq = p.length_squared();
      if(1e-160 < len_sq && len_sq <= 1) {
        return p / sqrt(len_sq);
      }
    }
  }

  /// <summary>
  /// Generates a random unit vector that lies on the surface of a unit sphere
  /// on the same hemisphere as the given normal vector.
  /// </summary>
  /// <param name="normal">The normal vector that defines the hemisphere direction.</param>
  /// <returns>A vec3 on the unit sphere in the hemisphere the normal vector points towards.</returns>
  vec3 vec3::random_on_hemisphere(const vec3& normal)
  {
    vec3 on_unit_sphere = random_unit_vector_in_unit_sphere();
    double dot_normal = on_unit_sphere.dot(normal);
    if(dot_normal > 0.0) {
      return on_unit_sphere;
    } else {
      return -on_unit_sphere;
    }
  }

  bool vec3::near_zero(const vec3& v)
  {
    // return true if the vector is close to zero in all dimensions
    const double eps = 1e-8;
    return (fabs(v.e[0]) < eps) && (fabs(v.e[1]) < eps) && (fabs(v.e[2]) < eps);
  }

  // Non-member operators that use public interface
  std::ostream& operator<<(std::ostream& out, const vec3& v)
  {
    return out << v.x() << ' ' << v.y() << ' ' << v.z();
  }

  vec3 operator*(double t, const vec3& v)
  {
    return v * t;
  }
}