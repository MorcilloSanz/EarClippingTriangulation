#include <iostream>
#include <vector>
#include <string>

#include "consoleRender/ConsoleRender.h"

#include "geometry/Polygon.h"

using namespace cr;

int main() {
  ConsoleRender::init();
  ConsoleRender::drawText("Ear clipping triangulation example:", 20, 20, Color(255, 255, 255));

  // House with door
  std::vector<Vector2> vertices = {
    Vector2(300, 300), Vector2(300, 200), Vector2(200, 100),
    Vector2(100, 200), Vector2(100, 300), Vector2(150, 300),
    Vector2(150, 250), Vector2(175, 250), Vector2(175, 300)
  };
  // Create polygon
  Poly polygon(vertices);
  // Get triangulation
  std::vector<Triangle> triangulation = polygon.getEarClippingTriangulation();
  // Draw triangles
  polygon.draw(Color(0, 0, 255));
  for(Triangle triangle : triangulation)
    triangle.draw(Color(0, 255, 0));

  ConsoleRender::destroy();
  std::cin.get();
}
