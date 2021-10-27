#include "ConsoleRender.h"

#include <vector>
#include <map>
#include <algorithm>
#include <cmath>

#define CLEAR_COMMAND "cls"

#define M_PI 3.14159265358979323846264338327950288
#define CIRCLE_DIVISIONS 20

namespace cr {

  HWND ConsoleRender::hwnd = nullptr;
  HDC ConsoleRender::hdc = nullptr;
  short ConsoleRender::bufferWidth = 0;
  short ConsoleRender::bufferHeight = 0;
  short ConsoleRender::width = 0;
  short ConsoleRender::height = 0;

  void ConsoleRender::initWindow() {
    ConsoleRender::hwnd = GetConsoleWindow();
    ConsoleRender::hdc = GetDC(ConsoleRender::hwnd);
    RECT rect;
    GetClientRect(ConsoleRender::hwnd, &rect);
    ConsoleRender::width = rect.right;
    ConsoleRender::height = rect.bottom;
  }

  void ConsoleRender::hideCursor() {
    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO info;
    info.dwSize = 100;
    info.bVisible = FALSE;
    SetConsoleCursorInfo(consoleHandle, &info);
  }

  void ConsoleRender::getConsoleScreenBufferInfo() {
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    int ret = GetConsoleScreenBufferInfo(GetStdHandle( STD_OUTPUT_HANDLE ), &csbi);
    if(ret) {
        ConsoleRender::bufferWidth = csbi.dwSize.X;
        ConsoleRender::bufferHeight = csbi.dwSize.Y;
    }
  }

  void ConsoleRender::clearBuffer() {
    system(CLEAR_COMMAND);
  }

  void ConsoleRender::init() {
    initWindow();
    hideCursor();
    getConsoleScreenBufferInfo();
    clearBuffer();
  }

  void ConsoleRender::destroy() {
    ReleaseDC(ConsoleRender::hwnd, ConsoleRender::hdc);
  }

  void ConsoleRender::drawPoint(unsigned int x, unsigned int y, const Color& color) {
      SetPixel(ConsoleRender::hdc, x, y, RGB(color.r, color.g, color.b));
  }

  void ConsoleRender::plotLineLow(int x0, int y0, int x1, int y1, const Color& color) {
    int dx = x1 - x0;
    int dy = y1 - y0;
    int yi = 1;
    if(dy < 0) {
      yi = -1;
      dy = -dy;
    }
    int D = (2 * dy) - dx;
    int y = y0;

    for(int i = x0; i < x1; i ++) {
      drawPoint(i, y, color);
      if(D > 0) {
        y += yi;
        D += 2 * (dy - dx);
      }else
        D += 2 * dy;
    }
  }

  void ConsoleRender::plotLineHigh(int x0, int y0, int x1, int y1, const Color& color) {
    int dx = x1 - x0;
    int dy = y1 - y0;
    int xi = 1;
    if(dx < 0) {
      xi = -1;
      dx = -dx;
    }
    int D = (2  * dx) - dy;
    int x = x0;

    for(int j = y0; j < y1; j ++) {
      drawPoint(x, j, color);
      if(D > 0) {
        x += xi;
        D += 2 * (dx - dy);
      }else
        D += 2 * dx;
    }
  }

  void ConsoleRender::drawLine(int x0, int y0, int x1, int y1, const Color& color) {
    if(abs(y1 - y0) < abs(x1 - x0)) {
      if(x0 > x1)
        plotLineLow(x1, y1, x0, y0, color);
      else
        plotLineLow(x0, y0, x1, y1, color);
    }else {
      if(y0 > y1)
        plotLineHigh(x1, y1, x0, y0, color);
      else
        plotLineHigh(x0, y0, x1, y1, color);
    }
  }

  void ConsoleRender::drawRect(int x, int y, unsigned int width, unsigned int height, const Color& color) {
    for(int i = x; i < x + width; i ++) {
      drawPoint(i, y, color);
      drawPoint(i, y + height, color);
    }
    for(int j = y; j < y + height; j ++) {
      drawPoint(x, j, color);
      drawPoint(x + width, j, color);
    }
  }

  void ConsoleRender::fillRect(int x, int y, unsigned int width, unsigned int height, const Color& color) {
    for(int i = x; i < x + width; i ++) {
      for(int j = y; j < y + height; j ++) {
        drawPoint(i, j, color);
      }
    }
  }

  void ConsoleRender::drawTriangle(int x0, int y0, int x1, int y1, int x2, int y2, const Color& color) {
    drawLine(x0, y0, x1, y1, color);
    drawLine(x1, y1, x2, y2, color);
    drawLine(x2, y2, x0, y0, color);
  }

  void ConsoleRender::fillTriangle(int x0, int y0, int x1, int y1, int x2, int y2, const Color& color) {
    Vec2<int> v1(x0, y0);
    Vec2<int> v2(x1, y1);
    Vec2<int> v3(x2, y2);

    int maxX = max(v1.x, max(v2.x, v3.x));
    int maxY = max(v1.y, max(v2.y, v3.y));
    int minX = min(v1.x, min(v2.x, v3.x));
    int minY = min(v1.y, min(v2.y, v3.y));

    Vec2<int> vs1(v2.x - v1.x, v2.y - v1.y);
    Vec2<int> vs2(v3.x - v1.x, v3.y - v1.y);

    for(int x = minX; x <= maxX; x ++) {
      for(int y = minY; y <= maxY; y ++) {
        Vec2<int> q(x - v1.x, y - v1.y);

        float s = static_cast<float>(q ^ vs2) / (vs1 ^ vs2);
        float t = static_cast<float>(vs1 ^ q) / (vs1 ^ vs2);

        if((s >= 0) && (t >= 0) && (s + t <= 1))
          drawPoint(x, y, color);
      }
    }
  }

  void ConsoleRender::drawCircle(int x, int y, unsigned int radius, const Color& color) {
    const unsigned int divisions = 50;
    for(int i = 0; i < divisions; i ++) {
      double angle = ((2 * M_PI) / divisions) * (i + 1);
      double nextAngle = ((2 * M_PI) / divisions) * (i + 2);
      drawLine(x + radius * cos(angle), y + radius * sin(angle), x + radius * cos(nextAngle), y + radius * sin(nextAngle), color);
    }
  }

  void ConsoleRender::fillCircle(int x, int y, unsigned int radius, const Color& color) {
    const unsigned int divisions = 50;
    for(int i = 0; i < divisions; i ++) {
      double angle = ((2 * M_PI) / divisions) * (i + 1);
      double nextAngle = ((2 * M_PI) / divisions) * (i + 2);
      fillTriangle(x + radius * cos(angle), y + radius * sin(angle), x + radius * cos(nextAngle), y + radius * sin(nextAngle), x, y, color);
    }
  }

  void ConsoleRender::drawText(const std::string& text, int x, int y, const Color& color) {
    RECT rect;
    SetBkMode(ConsoleRender::hdc, TRANSPARENT);
    SetTextColor(ConsoleRender::hdc, RGB(color.r, color.g, color.b));
    rect.left = x;
    rect.top = y;
    rect.right = ConsoleRender::width - x;
    rect.bottom = ConsoleRender::height - y;
    DrawText(hdc, TEXT(text.c_str()), text.size(), &rect, DT_TOP | DT_LEFT | DT_SINGLELINE);
  }

}
