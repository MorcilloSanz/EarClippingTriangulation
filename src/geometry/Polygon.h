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
  void drawPolygon(const Color& color);
public:
  inline std::vector<Vector2>& getVertices() {
    return vertices;
  }

  inline std::vector<Vector2>& getTriangulationVertices() {
    return triangulationVertices;
  }
};
