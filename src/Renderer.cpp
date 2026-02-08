#include "Renderer.h"
#include <SDL_pixels.h>
#include <SDL_render.h>
#include <SDL_video.h>
#include <iterator>

Renderer::Renderer(int window_width, int window_height, char *title) {
  window = SDL_CreateWindow(title, 0, 0, window_width, window_height,
                            SDL_WINDOW_SHOWN);
  renderer = SDL_CreateRenderer(window, 1, SDL_RENDERER_ACCELERATED);
}
int Renderer::drawCircle(float2 pos, float radius, SDL_Color color) {
  SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
  int r = static_cast<int>(radius);
  int cx = static_cast<int>(pos.x);
  int cy = static_cast<int>(pos.y);

  int x = r;
  int y = 0;
  int decisionOver2 = 1 - x;

  while (y <= x) {
    // Draw 8 octants
    SDL_RenderDrawPoint(renderer, cx + x, cy + y);
    SDL_RenderDrawPoint(renderer, cx + y, cy + x);
    SDL_RenderDrawPoint(renderer, cx - x, cy + y);
    SDL_RenderDrawPoint(renderer, cx - y, cy + x);
    SDL_RenderDrawPoint(renderer, cx - x, cy - y);
    SDL_RenderDrawPoint(renderer, cx - y, cy - x);
    SDL_RenderDrawPoint(renderer, cx + x, cy - y);
    SDL_RenderDrawPoint(renderer, cx + y, cy - x);

    y++;
    if (decisionOver2 <= 0) {
      decisionOver2 += 2 * y + 1;
    } else {
      x--;
      decisionOver2 += 2 * (y - x) + 1;
    }
  }

  return 1;
}

int Renderer::drawRectangle(float2 pos, float2 dimensions, SDL_Color color) {
  SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
  SDL_RenderDrawLine(renderer, pos.x, pos.y, pos.x + dimensions.x, pos.y);
  SDL_RenderDrawLine(renderer, pos.x, pos.y, pos.x, pos.y + dimensions.y);
  SDL_RenderDrawLine(renderer, pos.x, pos.y + dimensions.y,
                     pos.x + dimensions.x, pos.y + dimensions.y);
  SDL_RenderDrawLine(renderer, pos.x + dimensions.x, pos.y,
                     pos.x + dimensions.x, pos.y + dimensions.y);
  return 1;
}
int Renderer::clear(SDL_Color color) {
  SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
  SDL_RenderClear(renderer);
  return 1;
}
void Renderer::present() { SDL_RenderPresent(renderer); }
