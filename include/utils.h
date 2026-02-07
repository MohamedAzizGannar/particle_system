#ifndef UTILS_H
#define UTILS_H
#include <cmath>
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
};
#endif
