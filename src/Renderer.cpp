#include "Renderer.h"
#include <SDL_pixels.h>
#include <SDL_render.h>
#include <SDL_video.h>
#include <vector>

Renderer::Renderer(int window_width, int window_height, char *title) {
  window = SDL_CreateWindow(title, 0, 0, window_width, window_height,
                            SDL_WINDOW_SHOWN);
  renderer = SDL_CreateRenderer(window, 1, SDL_RENDERER_ACCELERATED);
  vertices = new SDL_Vertex[max_particles * 4];
  indices = new int[max_particles * 6];
}
Renderer::~Renderer() {
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  delete[] indices;
  delete[] vertices;
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
void Renderer::drawParticlesBatched(const std::vector<Particle> &particles) {
  int count = std::min((int)particles.size(), max_particles);
  int vertex_idx = 0;
  int indices_idx = 0;
  for (const auto &particle : particles) {
    float2 pos = particle.getPos();
    float r = particle.getRadius();
    SDL_Color color = particle.getColor();

    vertices[vertex_idx] = {{pos.x - r, pos.y - r}, color, {0, 0}};
    vertices[vertex_idx + 1] = {{pos.x + r, pos.y - r}, color, {0, 0}};
    vertices[vertex_idx + 2] = {{pos.x - r, pos.y + r}, color, {0, 0}};
    vertices[vertex_idx + 3] = {{pos.x + r, pos.y + r}, color, {0, 0}};

    indices[indices_idx] = vertex_idx;
    indices[indices_idx + 1] = vertex_idx + 1;
    indices[indices_idx + 2] = vertex_idx + 2;
    indices[indices_idx + 3] = vertex_idx + 1;
    indices[indices_idx + 4] = vertex_idx + 3;
    indices[indices_idx + 5] = vertex_idx + 2;
    vertex_idx += 4;
    indices_idx += 6;
  }
  SDL_RenderGeometry(renderer, nullptr, vertices, count * 4, indices,
                     count * 6);
}
int Renderer::clear(SDL_Color color) {
  SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
  SDL_RenderClear(renderer);
  return 1;
}
void Renderer::present() { SDL_RenderPresent(renderer); }
