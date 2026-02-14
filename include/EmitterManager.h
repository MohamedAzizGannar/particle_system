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
  std::vector<Particle> particles;
  std::vector<std::unique_ptr<Emitter>> emitters;
  std::vector<std::unique_ptr<Force>> forces;

public:
  EmitterManager();
  void update(float dt);
  void render(Renderer &renderer);

  void addEmitter(float2 pos, float spawn_interval);
  void addFountainEmitter(float2 pos, float spawn_interval, float spread_angle);
  void clearEmitters();

  void switchGravity();
  void switchWind();

  void addPositionalForce(float strength, float2 pos, float radius,
                          bool isAttractor);
  void clearForces();
  void switchForceRendering();
};

#endif // !EMITTERMANAGER_H
