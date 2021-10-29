/*
  MIT License

  Copyright (c) 2021 Alberto Morcillo Sanz

  Permission is hereby granted, free of charge, to any person obtaining a copy
  of this software and associated documentation files (the "Software"), to deal
  in the Software without restriction, including without limitation the rights
  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
  copies of the Software, and to permit persons to whom the Software is
  furnished to do so, subject to the following conditions:

  The above copyright notice and this permission notice shall be included in all
  copies or substantial portions of the Software.

  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
  SOFTWARE.
*/

#pragma once

#include <iostream>
#include <sstream>

#include "Vector2.h"
#include "../consoleRender/ConsoleRender.h"

#define M_PI 3.14159265358979323846264338327950288

using namespace cr;

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

  inline void draw(const Color& color) {
    ConsoleRender::drawTriangle(v1.x, v1.y, v2.x, v2.y, v3.x, v3.y, color);
  }

  inline float getArea() {
    return ( v1.x * (v2.y - v3.y) + v2.x * (v3.y - v1.y) + v3.x * (v1.y - v2.y) ) / 2;
  }

  inline friend std::ostream& operator << (std::ostream& os, const Triangle& triangle) {
      return os << "v1=[" << triangle.v1.x << ", " << triangle.v1.y << "], v2=[" << triangle.v2.x << ", "
      << triangle.v2.y << "], v3=[" << triangle.v3.x << ", " << triangle.v3.y << "]";
  }
};
