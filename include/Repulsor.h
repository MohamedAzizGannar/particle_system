#ifndef REPULSOR_H
#define REPULSOR_H
#include "Particle.h"
class Repulsor : public Force {

private:
  float radius;
  float2 pos;

public:
  Repulsor(float strength, float2 pos, float radius);
  void render(Renderer &renderer) const override;
  void applyForce(Particle &p, float dt) override;
};

#endif // !REPULSOR_H
