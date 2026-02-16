#ifndef RENDERER_h
#define RENDERER_h
#include "Particle.h"
#include "Utility.h"
#include <SDL2/SDL.h>
#include <SDL_pixels.h>
#include <SDL_render.h>
#include <SDL_video.h>
class Renderer {
private:
  SDL_Window *window;
  SDL_Renderer *renderer;
  SDL_Vertex *vertices;
  int *indices;
  int max_particles = 10000;

public:
  Renderer(int window_width, int window_height, char *title);
  ~Renderer();

  int drawCircle(float2 pos, float radius, SDL_Color color);
  int drawRectangle(float2 pos, float2 dimensions, SDL_Color color);
  void drawParticlesBatched(const std::vector<Particle> &particles);
  int clear(SDL_Color color);

  SDL_Renderer *getRenderer() { return renderer; }
  SDL_Window *getWindow() { return window; }
  void present();
};
#endif
