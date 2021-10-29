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

  // Bat
  vertices =  {
    Vector2(113, 417), Vector2(113, 334), Vector2(50, 272),
    Vector2(109, 279), Vector2(113, 191), Vector2(147, 221),
    Vector2(198, 219), Vector2(233, 181), Vector2(241, 274),
    Vector2(295, 270), Vector2(237, 327), Vector2(232, 426),
    Vector2(172, 359)
  };

  // C
  vertices = {
    Vector2(351, 200), Vector2(329, 125), Vector2(223, 120), Vector2(146, 204),
    Vector2(148, 308), Vector2(243, 372), Vector2(345, 343), Vector2(354, 267),
    Vector2(292, 263), Vector2(259, 290), Vector2(231, 252), Vector2(261, 205),
    Vector2(294, 219)
  };

  // Create polygon
  Poly polygon(vertices);
  // Get triangulation
  std::vector<Triangle> triangulation = polygon.getEarClippingTriangulation();
  // Draw triangles
  for(Triangle triangle : triangulation)
    triangle.draw(Color(0, 255, 0));
  polygon.draw(Color(0, 0, 255));

  ConsoleRender::destroy();
  std::cin.get();
}
