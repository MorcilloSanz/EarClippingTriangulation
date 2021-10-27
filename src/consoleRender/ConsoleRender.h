/*
  Console 2D rendering library for Windows

  Draw line Bresenham algorithm:
    https://en.wikipedia.org/wiki/Bresenham%27s_line_algorithm

  Triangle rasterization Barycentric Algorithm:
    http://www.sunshine2k.de/coding/java/TriangleRasterization/TriangleRasterization.html

  GitHub: https://github.com/MorcilloSanz/ConsoleRender
  Twitter: @MorcilloSanz

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

#include "Windows.h"
#include <iostream>
#include <string>

namespace cr {

  template <class T>
  inline const T& max (const T& a, const T& b) {
    return (a < b) ? b : a;
  }

  template <class T>
  inline const T& min (const T& a, const T& b) {
    return (a < b) ? a : b;
  }

  template<typename T>
  struct Vec2 {
      T x, y;
      Vec2(T _x, T _y)
        : x(_x), y(_y) {
      }

      // Dot product
      inline T operator * (const Vec2& rhs) const {
        return x * rhs.x + y * rhs.y;
      }

      // Cross product
      inline T operator ^ (const Vec2& rhs) const {
        return x * rhs.y - y * rhs.x;
      }
  };

  struct Color {
      unsigned int r, g, b;
      Color(unsigned int _r, unsigned int _g, unsigned int _b)
        : r(_r), g(_g), b(_b) {
      }
  };

  class ConsoleRender {
  private:
    static HWND hwnd;
    static HDC hdc;
    static short bufferWidth, bufferHeight;
    static short width, height;
  private:
    // Context
    static void initWindow();
    static void hideCursor();
    static void getConsoleScreenBufferInfo();
    static void clearBuffer();
    // Graphics
    static void plotLineLow(int x0, int y0, int x1, int y1, const Color& color);
    static void plotLineHigh(int x0, int y0, int x1, int y1, const Color& color);
  public:
    // Context
    static void init();
    static void destroy();
    // Graphics
    static void drawPoint(unsigned int x, unsigned int y, const Color& color);
    static void drawLine(int x0, int y0, int x1, int y1, const Color& color);
    static void drawRect(int x, int y, unsigned int width, unsigned int height, const Color& color);
    static void fillRect(int x, int y, unsigned int width, unsigned int height, const Color& color);
    static void drawTriangle(int x0, int y0, int x1, int y1, int x2, int y2, const Color& color);
    static void fillTriangle(int x0, int y0, int x1, int y1, int x2, int y2, const Color& color);
    static void drawCircle(int x, int y, unsigned int radius, const Color& color);
    static void fillCircle(int x, int y, unsigned int radius, const Color& color);
    static void drawText(const std::string& text, int x, int y, const Color& color);
  public:
    // Getters
    static inline short getBufferWidth() {
      return bufferWidth;
    }

    static inline short getBufferHeight() {
      return bufferHeight;
    }

    static inline short getWidth() {
      return width;
    }

    static inline short getHeight() {
      return height;
    }
  };
}
