
#ifndef UTILS_H
#define UTILS_H
#include <SDL2/SDL.h>
#include <cmath>
const SDL_Color BLUE = {0, 0, 255, 255};
const SDL_Color RED = {255, 0, 0, 255};
const SDL_Color GREEN = {0, 255, 0, 255};
const SDL_Color TEAL = {0, 125, 125, 255};
const SDL_Color PURPLE = {125, 0, 125, 255};
const SDL_Color colors[5] = {BLUE, RED, GREEN, PURPLE, TEAL};
struct float2 {
  float x, y;
  float2() : x(0), y(0) {}
  float2(float x_, float y_) : x(x_), y(y_) {}
  float2 operator+(const float2 &other) const {
    return float2(other.x + x, other.y + y);
  }
  float2 operator-(const float2 &other) const {
    return float2(other.x - x, other.y - y);
  }
  float2 &operator+=(const float2 &other) {
    x += other.x;
    y += other.y;
    return *this;
  }

  float2 &operator-=(const float2 &other) {
    x -= other.x;
    y -= other.y;
    return *this;
  }
  float length() const { return sqrtf(x * x + y * y); }
  float sqrd_length() const { return x * x + y * y; }
  void normalize() {
    float distance = length();
    if (distance == 0.f) {
      x = 0.f;
      y = 0.f;
    }
    x /= distance;
    y /= distance;
  }
};

struct BoundingBox {
  float2 pos;
  float length;
  float height;
  BoundingBox(float2 pos_, float l, float h)
      : pos(pos_), length(l), height(h) {}
  BoundingBox() : pos(float2(0, 0)), length(100.f), height(100.f) {}
};

#endif
