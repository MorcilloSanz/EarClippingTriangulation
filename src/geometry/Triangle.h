#pragma once

#include <iostream>
#include <sstream>

#include "Vector2.h"

#define M_PI 3.14159265358979323846264338327950288

struct Triangle {
  Vector2 v1, v2, v3;

  Triangle(const Vector2& _v1, const Vector2& _v2, const Vector2& _v3)
    : v1(_v1), v2(_v2), v3(_v3) {
  }
  Triangle() = default;
  ~Triangle() = default;

  bool contains(const Vector2& point) {
    Vector2 vs1(v2.x - v1.x, v2.y - v1.y);
    Vector2 vs2(v3.x - v1.x, v3.y - v1.y);
    Vector2 q(point.x - v1.x, point.y - v1.y);

    float s = static_cast<float>(q ^ vs2) / (vs1 ^ vs2);
    float t = static_cast<float>(vs1 ^ q) / (vs1 ^ vs2);

    return (s >= 0) && (t >= 0) && (s + t <= 1);
  }

  inline float getArea() {
    return ( v1.x * (v2.y - v3.y) + v2.x * (v3.y - v1.y) + v3.x * (v1.y - v2.y) ) / 2;
  }

  inline friend std::ostream& operator << (std::ostream& os, const Triangle& triangle) {
      return os << "v1=[" << triangle.v1.x << ", " << triangle.v1.y << "], v2=[" << triangle.v2.x << ", "
      << triangle.v2.y << "], v3=[" << triangle.v3.x << ", " << triangle.v3.y << "]";
  }
};
