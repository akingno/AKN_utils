//
// Created by jacob on 2025/5/26.
//

#ifndef TESTMAP__VECTOR2D_H_
#define TESTMAP__VECTOR2D_H_

#include <cmath>
#include <iostream>
namespace AKN{

class Vector2d{

 public:
  constexpr Vector2d():_x(0.0), _y(0.0){};
  constexpr Vector2d(float x, float y):_x(x), _y(y){}
  ~Vector2d() = default;
  Vector2d(const Vector2d&) = default;
  Vector2d(Vector2d&&) noexcept = default;
  Vector2d& operator=(const Vector2d&) = default;
  Vector2d& operator=(Vector2d&&) noexcept = default;

  // Add
  [[nodiscard]] constexpr Vector2d operator+(const Vector2d& _vec2) const noexcept{
    return {_x+_vec2._x, _y+_vec2._y};
  }

  constexpr Vector2d& operator+=(const Vector2d& _vec2) noexcept{
    _x += _vec2._x; _y += _vec2._y; return *this;
  }

  // Minus
  [[nodiscard]] constexpr Vector2d operator-(const Vector2d& rhs) const noexcept {
    return {_x - rhs._x, _y - rhs._y};
  }
  constexpr Vector2d& operator-=(const Vector2d& rhs) noexcept {
    _x -= rhs._x;  _y -= rhs._y;  return *this;
  }
  [[nodiscard]] constexpr Vector2d operator-() const noexcept { return {-_x, -_y}; }

  // Scalar Product
  [[nodiscard]] constexpr Vector2d operator*(float k) const noexcept {
    return {_x * k, _y * k};
  }
  constexpr Vector2d& operator*=(float k) noexcept {
    _x *= k;  _y *= k;  return *this;
  }

  friend constexpr Vector2d operator*(float k, const Vector2d& v) noexcept {
    return {v._x * k, v._y * k};
  }

  // Scalar Div
  [[nodiscard]] constexpr Vector2d operator/(float k) const noexcept {
    return {_x / k, _y / k};
  }
  constexpr Vector2d& operator/=(float k) noexcept {
    _x /= k;  _y /= k;  return *this;
  }

  // Length
  [[nodiscard]] constexpr float length2() const noexcept {
    return _x * _x + _y * _y;
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
  [[nodiscard]] constexpr Vector2d normalized() const noexcept {
    float len = length();
    return len > kEpsilon ? (*this / len) : *this;
  }

  constexpr Vector2d& normalize() noexcept {
    float len = length();
    if (len > kEpsilon) { _x /= len;  _y /= len; }
    return *this;
  }

  [[nodiscard]] constexpr float x() const noexcept { return _x; }
  [[nodiscard]] constexpr float y() const noexcept { return _y; }

  constexpr void set(float newX, float newY) noexcept {_x = newX; _y = newY;}
  constexpr void setX(float newX) noexcept { _x = newX;}
  constexpr void setY(float newY) noexcept { _y = newY;}

  void print() const { std::cout << "(" << _x << ", " << _y << ")";}


 private:
  float _x;
  float _y;
  static constexpr float kEpsilon = 1e-6f;
};

static inline const Vector2d Zero  {0.0f, 0.0f};
static inline const Vector2d UnitX {1.0f, 0.0f};
static inline const Vector2d UnitY {0.0f, 1.0f};


}



#endif//TESTMAP__VECTOR2D_H_
