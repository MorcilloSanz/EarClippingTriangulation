# EarClippingTriangulation
Basic ear clipping triangulation algorithm in C++

### Usage
Create a polygon and get the triangulation

```cpp

  // Vertices
  std::vector<Vector2> vertices = {
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
  
```

**Warning:** Counterclockwise triangulation

### Demo
![alt text](https://github.com/MorcilloSanz/EarClippingTriangulation/blob/main/img/demo.png)  
