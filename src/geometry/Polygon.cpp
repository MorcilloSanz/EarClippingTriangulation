#include "Polygon.h"

Poly::Poly(const std::vector<Vector2>& _vertices)
  : vertices(_vertices), triangulationVertices(_vertices) {
}

Poly::Poly(const Poly& poly)
  : vertices(poly.vertices), triangulationVertices(poly.triangulationVertices),
  triangles(poly.triangles) {
}

Poly::Poly(Poly&& poly) noexcept
  : vertices(std::move(poly.vertices)), triangulationVertices(std::move(poly.triangulationVertices)),
  triangles(std::move(poly.triangles)) {
}

Poly& Poly::operator=(const Poly& poly) {
  vertices = poly.vertices;
  triangulationVertices = poly.triangulationVertices;
  triangles = poly.triangles;
  return *this;
}

/**
  For each vertex:
    Check if the triangle created by the vertex and the previous and following vertex is CONVEX (angle < 180)
    if it is convex, check if there isn't any vertex of the vertices inside of it
    If these two conditions are true, we have found an ear, then add the triangle to a triangle list and remove
    the vertex of the vertex list.
    If one of these two conditions is false, do the same process with the following vertex
    Iterate again...
*/
std::vector<Triangle>& Poly::getEarClippingTriangulation() {
  // Add last triangle and return
  if(triangulationVertices.size() <= 3) {
    triangles.push_back(Triangle(triangulationVertices[0], triangulationVertices[1], triangulationVertices[2]));
    return triangles;
  }
  // Start algorithm
  bool valid = false;
  int vertexIndex = 0;
  std::vector<Vector2> tempVertices;
  do {
    // Neighbor indices
    int previousIndex = (vertexIndex - 1 < 0) ? triangulationVertices.size() - 1 : vertexIndex - 1;
    int followingIndex = (vertexIndex + 1 >= triangulationVertices.size()) ? 0 : vertexIndex + 1;
    // Triangle vertices
    Vector2 currentVertex = triangulationVertices[vertexIndex];
    Vector2 previousVertex = triangulationVertices[previousIndex];
    Vector2 followingVertex = triangulationVertices[followingIndex];
    // Vectors
    Vector2 u(previousVertex.x - currentVertex.x, previousVertex.y - currentVertex.y);  // u = p - v
    Vector2 v(followingVertex.x - currentVertex.x, followingVertex.y - currentVertex.y);  // v = f - v
    float angle = u.getAngle(v);  // Angle between both vectors
    // Check if it is a valid triangle
    valid = (angle < M_PI); // If angle < 180º, its convex so its valid
    if(valid) {
      // Create triangle from the vertices
      Triangle triangle(previousVertex, currentVertex, followingVertex);
      // Check wether there is any point of the vertices set inside of the triangle or not
      for(Vector2 vertex : triangulationVertices) {
        if(vertex != currentVertex && vertex != previousVertex && vertex != followingVertex) {
          if(triangle.contains(vertex)) valid = false;
        }
      }
      // If still valid, add the triangle and remove the found ear
      if(valid) {
        triangles.push_back(triangle);
        // Add every vertex except the current one, what is the same as removing it
        for(Vector2 vertex : triangulationVertices) {
          if((vertex.x == currentVertex.x) && (vertex.y == currentVertex.y)) continue;
          tempVertices.push_back(vertex);
        }
        break;
      }
    }
    // Go to the next vertex
    vertexIndex ++;
    // Repeat until finding a valid vertex
  } while(!valid);
  // Iterate through the rest of the vertices
  triangulationVertices.assign(tempVertices.begin(), tempVertices.end());
  return getEarClippingTriangulation();
}

void Poly::draw(const Color& color) {
  for(int i = 0; i < vertices.size() - 1; i ++)
      ConsoleRender::drawLine(vertices[i].x, vertices[i].y, vertices[i + 1].x, vertices[i + 1].y, color);
  ConsoleRender::drawLine(vertices[vertices.size() - 1].x, vertices[vertices.size() - 1].y, vertices[0].x, vertices[0].y, color);
}
