#ifndef PARTICLE_H
#define PARTICLE_H

#include "utils.h"
#include <SDL2/SDL.h>
#include <SDL_pixels.h>
#include <sys/types.h>

class Particle {
private:
  float2 pos;
  float2 vel;
  SDL_Color color;

  float lifetime = 9.f;
  float age;

public:
  Particle(float x, float y, float vx, float vy,
           SDL_Color color = {255, 255, 255, 255});

  void setPosition(float x_, float y_);
  void setVelocity(float x_, float y_);
  void setAge(float age_);

  const SDL_Color getColor() const;
  const float2 getPos() const;
  const float2 getVel() const;
  const float getAge() const;
  const float getLifetime() const;
};
#endif
