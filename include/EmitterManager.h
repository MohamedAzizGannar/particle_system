#ifndef EMITTERMANAGER_H
#define EMITTERMANAGER_H
#include "Emitter.h"
#include "Force.h"
#include "Particle.h"
#include "Renderer.h"
#include "Utility.h"
#include <memory>
#include <vector>
class EmitterManager {
private:
  bool isGravityActive = true;
  bool isWindActive = true;
  bool renderForces = true;

  float lifetime = 2.f;
  float spread_angle = M_PI / 3.f;
  float spawn_interval = .01f;

  const int max_particles = 20000;
  const int max_forces = 20;
  const int max_emitters = 100;

  std::vector<Particle> particles;
  std::vector<std::unique_ptr<Emitter>> emitters;
  std::vector<std::unique_ptr<Force>> forces;

public:
  EmitterManager();

  int getParticleCount() { return particles.size(); }
  float getParticleLifetime() { return lifetime; }
  void update(float dt);
  void render(Renderer &renderer);

  void addEmitter(float2 pos);
  void addFountainEmitter(float2 pos, bool isUp = true);
  void clearEmitters();

  void toggleGravity();
  void toggleWind();
  void toggleForceRendering();

  void addPositionalForce(float strength, float2 pos, float radius,
                          bool isAttractor);

  void updateGravity(float new_strength);
  void updateWind(float new_strength);
  void updateLifetime(float lifetime_);
  void updateSpawnInterval(float spawn_interval_);
  void updateSpreadAngle(float spread_angle_);

  void clearForces();
};

#endif // !EMITTERMANAGER_H
