#include "Particle.h"
#include "PhysicsSystem.h"
#include <SDL2/SDL.h>
#include <SDL_events.h>
#include <SDL_keycode.h>
#include <SDL_pixels.h>
#include <SDL_render.h>
#include <SDL_timer.h>
#include <SDL_video.h>
#include <iostream>
#include <ostream>
#include <vector>
const SDL_Color BLUE = {0, 0, 255, 255};
const SDL_Color RED = {255, 0, 0, 255};
const SDL_Color GREEN = {0, 255, 0, 255};

int main() {
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {

    std::cerr << "Failure Initializating SDL : " << SDL_GetError() << std::endl;
    return -1;
  }
  SDL_Window *window = SDL_CreateWindow("Aziz's Particle System", 0, 0, 500,
                                        500, SDL_WINDOW_SHOWN);
  if (!window) {
    std::cerr << "Failure Creating Window : " << SDL_GetError() << std::endl;
    SDL_Quit();
    return -1;
  }
  SDL_Renderer *renderer =
      SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
  if (!renderer) {
    std::cerr << "Failure Creating Renderer : " << SDL_GetError() << std::endl;
    SDL_DestroyWindow(window);
    SDL_Quit();
  }
  bool isRunning = true;
  SDL_Event event;
  std::vector<Particle> particles;
  particles.push_back(Particle(250, 250, 10, 0, 1, BLUE));
  particles.push_back(Particle(350, 350, -40, 0, 1, RED));

  PhysicsSystem physics_system(particles, 0.016f);
  while (isRunning) {
    while (SDL_PollEvent(&event)) {
      if (event.type == SDL_QUIT) {
        isRunning = false;
      }
      if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE) {
        isRunning = false;
      }
    }
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    physics_system.update();
    for (const auto &particle : particles) {
      SDL_Color color = particle.getColor();

      SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
      SDL_RenderDrawPoint(renderer, particle.getPos().x, particle.getPos().y);
    }
    SDL_RenderPresent(renderer);
    SDL_Delay(16);
  }
  SDL_DestroyWindow(window);
  SDL_DestroyRenderer(renderer);
  SDL_Quit();
  std::cout << "Hello World, I'm a Particle System\n";
  return 0;
}
