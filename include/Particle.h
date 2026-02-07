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
  const float mass;
  SDL_Color color;

public:
  Particle(float x, float y, float vx, float vy, float mass = 1.0,
           SDL_Color color = {255, 255, 255, 255});

  void setPosition(float x_, float y_);
  void setVelocity(float x_, float y_);

  const SDL_Color getColor() const;
  const float2 getPos() const;
  const float2 getVel() const;
};
#endif
