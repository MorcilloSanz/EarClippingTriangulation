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
#include <vector>

#include <algorithm>

#include "Triangle.h"
#include "../consoleRender/ConsoleRender.h"

using namespace cr;

class Poly {
private:
  std::vector<Triangle> triangles;
  std::vector<Vector2> vertices, triangulationVertices;
public:
  Poly(const std::vector<Vector2>& _vertices);
  Poly(const Poly& poly);
  Poly(Poly&& poly) noexcept;
  Poly() = default;
  ~Poly() = default;
  Poly& operator=(const Poly& poly);
public:
  std::vector<Triangle>& getEarClippingTriangulation(); // Counterclockwise direction
  void draw(const Color& color);
public:
  inline std::vector<Vector2>& getVertices() {
    return vertices;
  }

  inline std::vector<Vector2>& getTriangulationVertices() {
    return triangulationVertices;
  }
};
