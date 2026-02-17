
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
inline float fast_inv_sqrt(float x) {
  float half = 0.5f * x;
  int i = *(int *)&x;            // Interpret float bits as int
  i = 0x5f3759df - (i >> 1);     // Magic constant approximation
  float y = *(float *)&i;        // Back to float
  y = y * (1.5f - half * y * y); // One Newton-Raphson iteration
  return y;
}
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
  float2 operator*(const float scalar) const {
    return float2(x * scalar, y * scalar);
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
  float2 &operator+=(const float scalar) {
    x += scalar;
    y += scalar;
    return *this;
  }
  float2 &operator-=(const float scalar) {
    x -= scalar;
    y -= scalar;
    return *this;
  }
  float2 &operator*=(const float scalar) {
    x *= scalar;
    y *= scalar;
    return *this;
  }
  float2 &operator/=(const float scalar) {
    x /= scalar;
    y /= scalar;
    return *this;
  }
  float length() const { return sqrtf(x * x + y * y); }
  float sqrd_length() const { return x * x + y * y; }
  void normalize() {
    float distance = length();
    if (distance == 0.f) {
      x = 0.f;
      y = 0.f;
      return;
    }
    x /= distance;
    y /= distance;
  }
  void fast_normalize() {
    float sq = sqrd_length();
    if (sq == 0.f) {
      x = 0.f;
      y = 0.f;
      return;
    }
    float inv = fast_inv_sqrt(sq);
    x *= inv;
    y *= inv;
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
