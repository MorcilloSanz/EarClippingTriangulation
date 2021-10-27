#include <iostream>
#include <vector>
#include <string>

#include "consoleRender/ConsoleRender.h"

#include "geometry/Polygon.h"

using namespace cr;

inline void drawTriangle(Triangle& triangle, const Color& color) {
  ConsoleRender::drawTriangle(triangle.v1.x, triangle.v1.y, triangle.v2.x,
    triangle.v2.y, triangle.v3.x, triangle.v3.y, color);
}

int main() {
  ConsoleRender::init();
  ConsoleRender::drawText("Ear clipping triangulation example:", 20, 20, Color(255, 255, 255));

  // Generate vertices
  unsigned int divisions = 9;
  unsigned int cx = 250, cy = 250;
  unsigned int radius = 150;
  std::vector<Vector2> vertices;
  for(int i = 0; i < divisions; i ++) {
    double angle = ((2 * M_PI) / divisions) * (i + 1);
    vertices.push_back(Vector2(cx + radius * cos(angle), cy + radius * sin(angle)));
  }
  // Create polygon
  Poly polygon(vertices);
  polygon.drawPolygon(Color(0, 0, 255));
  // Get triangulation
  std::vector<Triangle> triangulation = polygon.getEarClippingTriangulation();
  // Draw triangles
  for(Triangle triangle : triangulation) {
    drawTriangle(triangle, Color(0, 255, 0));
  }

  ConsoleRender::destroy();
  std::cin.get();
}
