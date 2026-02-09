#ifndef PARTICLE_H
#define PARTICLE_H
#include "Force.h"
#include "Renderer.h"
#include "Utility.h"
#include <SDL2/SDL.h>
#include <SDL_pixels.h>
#include <memory>
#include <sys/types.h>
#include <vector>
class Force;

class Particle {
private:
  float2 pos;
  float2 vel;
  float radius = 2.f;

  SDL_Color color;

  float lifetime = 2.9f;
  float age = 0.f;

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
  const float getRadius() const;

  void render(Renderer &renderer);
  void update(float dt, const std::vector<std::unique_ptr<Force>> &forces);

  const bool isDead() const;
};
#endif
