#ifndef RENDERER_h
#define RENDERER_h
#include "Utility.h"
#include <SDL2/SDL.h>
#include <SDL_pixels.h>
#include <SDL_render.h>
#include <SDL_video.h>
class Renderer {
private:
  SDL_Window *window;
  SDL_Renderer *renderer;

public:
  Renderer(int window_width, int window_height, char *title);
  int drawCircle(float2 pos, float radius, SDL_Color color);
  int drawRectangle(float2 pos, float2 dimensions, SDL_Color color);
  int clear(SDL_Color color);
  void present();
};
#endif
