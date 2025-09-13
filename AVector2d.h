//
// Created by jacob on 2025/5/26.
//

#ifndef TESTMAP__VECTOR2D_H_
#define TESTMAP__VECTOR2D_H_

#include <cmath>
#include <iostream>
namespace ak_util{

class Vector2d{

 public:
  constexpr Vector2d():x(0.0), y(0.0){};
  constexpr Vector2d(float x, float y):x(x), y(y){}
  constexpr Vector2d(int x, int y):x(static_cast<float>(x)), y(static_cast<float>(y)){}
  ~Vector2d() = default;
  Vector2d(const Vector2d&) = default;
  Vector2d(Vector2d&&) noexcept = default;
  Vector2d& operator=(const Vector2d&) = default;
  Vector2d& operator=(Vector2d&&) noexcept = default;

  // Add
  [[nodiscard]] constexpr Vector2d operator+(const Vector2d& _vec2) const noexcept{
    return {x+_vec2.x, y+_vec2.y};
  }

  constexpr Vector2d& operator+=(const Vector2d& _vec2) noexcept{
    x += _vec2.x; y += _vec2.y; return *this;
  }

  // Minus
  [[nodiscard]] constexpr Vector2d operator-(const Vector2d& rhs) const noexcept {
    return {x - rhs.x, y - rhs.y};
  }
  constexpr Vector2d& operator-=(const Vector2d& rhs) noexcept {
    x -= rhs.x;  y -= rhs.y;  return *this;
  }
  [[nodiscard]] constexpr Vector2d operator-() const noexcept { return {-x, -y}; }

  // Scalar Product
  [[nodiscard]] constexpr Vector2d operator*(float k) const noexcept {
    return {x * k, y * k};
  }
  constexpr Vector2d& operator*=(float k) noexcept {
    x *= k;  y *= k;  return *this;
  }

  friend constexpr Vector2d operator*(float k, const Vector2d& v) noexcept {
    return {v.x * k, v.y * k};
  }

  // Scalar Div
  [[nodiscard]] constexpr Vector2d operator/(float k) const noexcept {
    return {x / k, y / k};
  }
  constexpr Vector2d& operator/=(float k) noexcept {
    x /= k;  y /= k;  return *this;
  }

  // Length
  [[nodiscard]] constexpr float length2() const noexcept {
    return x * x + y * y;
  }

  [[nodiscard]] float length() const noexcept {
    return std::sqrt(length2());
  }

  // Distance
  [[nodiscard]] static constexpr float distance2(const Vector2d& a,
                                                 const Vector2d& b) noexcept {
    return (a - b).length2();
  }
  [[nodiscard]] static float distance(const Vector2d& a,
                                                const Vector2d& b) noexcept {
    using std::sqrt;
    return sqrt(distance2(a, b));
  }

  // !=, ==, equals
  [[nodiscard]] constexpr bool equals(const Vector2d& rhs,
                                      float eps = kEpsilon) const noexcept {
    return distance2(*this, rhs) <= eps * eps;
  }
  friend constexpr bool operator==(const Vector2d& lhs,
                                   const Vector2d& rhs) noexcept {
    return lhs.equals(rhs);
  }
  friend constexpr bool operator!=(const Vector2d& lhs,
                                   const Vector2d& rhs) noexcept {
    return !(lhs == rhs);
  }

  // Normalization
  [[nodiscard]] Vector2d normalized() const noexcept {
    float len = length();
    return len > kEpsilon ? (*this / len) : *this;
  }

  constexpr void set(float newX, float newY) noexcept {x = newX; y = newY;}

  void print() const { std::cout << "(" << x << ", " << y << ")";}
  void println() const { std::cout << "(" << x << ", " << y << ")\n";}



public:
  float x;
  float y;
private:
  static constexpr float kEpsilon = 1e-6f;
};

static inline const Vector2d Zero  {0.0f, 0.0f};
static inline const Vector2d UnitX {1.0f, 0.0f};
static inline const Vector2d UnitY {0.0f, 1.0f};

//todo: 改为使用format, 注意std::format是20的
[[nodiscard]] inline std::string to_Str(const Vector2d& vec) {
  return std::string("(") + std::to_string(vec.x) + ", " + std::to_string(vec.y) + ")";
}

}



#endif//TESTMAP__VECTOR2D_H_
