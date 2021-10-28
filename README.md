# EarClippingTriangulation

Basic ear clipping triangulation algorithm in C++

## Usage

Create a polygon and get the triangulation

```cpp
  std::vector<Vector2> vertices = {
      Vector2(300, 300), Vector2(300, 200), Vector2(200, 100), 
      Vector2(100, 200), Vector2(100, 300), Vector2(150, 300), 
      Vector2(150, 250), Vector2(175, 250), Vector2(175, 300)
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
```

## Demo

![alt text](https://github.com/MorcilloSanz/EarClippingTriangulation/blob/main/img/demo.png)  
