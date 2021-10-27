#pragma once

#include <iostream>
#include <cmath>
#include <sstream>

struct Vector2 {

  float x, y;

  Vector2(float _x, float _y)
    : x(_x), y(_y) {
  }

  inline float getModule() {
    return sqrt(x * x + y * y);
  }

  inline Vector2 getUnit() {
    return Vector2(x / getModule(), y / getModule());
  }

  inline float getAngle(Vector2& vector) {
    return acos((*this * vector) / (getModule() * vector.getModule()));
  }

  // Dot product
  inline float operator * (const Vector2& rhs) const {
    return x * rhs.x + y * rhs.y;
  }

  // Cross product
  inline float operator ^ (const Vector2& rhs) const {
    return x * rhs.y - y * rhs.x;
  }

  inline friend std::ostream& operator << (std::ostream& os, const Vector2& vec) {
      return os << "x: " << vec.x << ", y: " << vec.y;
  }
};
