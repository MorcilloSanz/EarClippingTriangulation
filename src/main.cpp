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
  unsigned int divisions = 11;
  unsigned int cx = 250, cy = 250;
  unsigned int radius = 100;
  std::vector<Vector2> vertices;
  for(int i = 0; i < divisions; i ++) {
    double angle = ((2 * M_PI) / divisions) * (i + 1);
    vertices.push_back(Vector2(cx + radius * cos(angle), cy + radius * sin(angle)));
  }

  // House without door
  vertices = {
    Vector2(300, 300), Vector2(300, 200), Vector2(200, 100), Vector2(100, 200), Vector2(100, 300)
  };

  // House with door
  vertices = {
    Vector2(300, 300), Vector2(300, 200), Vector2(200, 100), Vector2(100, 200), Vector2(100, 300), Vector2(150, 300), Vector2(150, 250), Vector2(175, 250), Vector2(175, 300)
  };

  // Create polygon
  Poly polygon(vertices);
  // Draw Polygon
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
