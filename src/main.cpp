#include "Emitter.h"
#include "FountainEmitter.h"
#include "Particle.h"
#include "PhysicsSystem.h"
#include "Renderer.h"
#include "utils.h"
#include <SDL2/SDL.h>
#include <SDL_events.h>
#include <SDL_keycode.h>
#include <SDL_pixels.h>
#include <SDL_render.h>
#include <SDL_stdinc.h>
#include <SDL_timer.h>
#include <SDL_video.h>
#include <iostream>
#include <ostream>
#include <vector>

int main() {
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {

    std::cerr << "Failure Initializating SDL : " << SDL_GetError() << std::endl;
    return -1;
  }
  Renderer renderer(800, 800, "Aziz's Particle System");

  bool isRunning = true;
  SDL_Event event;
  std::vector<Particle> particles;
  PhysicsSystem physics_system(particles, 0.016f);
  std::vector<Emitter> emitter_arr;
  Uint32 lastTime = SDL_GetTicks();
  while (isRunning) {
    Uint32 currentTime = SDL_GetTicks();
    float dt = (currentTime - lastTime) / 1000.f;
    lastTime = currentTime;
    while (SDL_PollEvent(&event)) {
      if (event.type == SDL_QUIT) {

        isRunning = false;
      }
      if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE) {
        isRunning = false;
      }
      if (event.type == SDL_MOUSEBUTTONDOWN) {
        emitter_arr.emplace_back(particles,
                                 float2(event.motion.x, event.motion.y), 0.01);
      }
    }
    renderer.clear({0, 0, 0, 0});
    BoundingBox bounding_box = physics_system.getBoundingBox();
    for (auto &e : emitter_arr)
      e.emitParticles(dt);
    renderer.drawRectangle(bounding_box.pos,
                           float2(bounding_box.length, bounding_box.height),
                           {255, 0, 0, 255});
    physics_system.update(dt);
    for (const auto &particle : particles) {
      SDL_Color color = particle.getColor();

      renderer.drawCircle(particle.getPos(), particle.getRadius(), color);
    }
    renderer.present();
    SDL_Delay(16);
  }
  SDL_Quit();
  std::cout << "Hello World, I'm a Particle System\n";
  return 0;
}
