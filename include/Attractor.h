#ifndef ATTRACTOR_H
#define ATTRACTOR_H
#include "Particle.h"
#include "Renderer.h"
#include "Utility.h"
const float GRAVITATIONAL_CONSTANT = 6.67e-11;
class Attractor : public Force {
private:
  float radius;

  float2 pos;

public:
  Attractor(float strength, float2 pos, float radius);
  void render(Renderer &renderer) const override;
  void applyForce(Particle &p, float dt) override;
};
#endif
