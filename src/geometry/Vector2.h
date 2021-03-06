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

  inline bool operator == (const Vector2& rhs) const {
    return (x == rhs.x && y == rhs.y);
  }

  inline bool operator != (const Vector2& rhs) const {
    return (x != rhs.x || y != rhs.y);
  }

  inline friend std::ostream& operator << (std::ostream& os, const Vector2& vec) {
      return os << "x: " << vec.x << ", y: " << vec.y;
  }
};
