#include <SDL2/SDL.h>
#include <cassert>

#ifdef EMSCRIPTEN
#include <emscripten.h>
#endif

#include "./maze.hpp"

using namespace std;

SDL_Window *window;
SDL_Renderer *renderer;

Maze maze;
int n, m;

void draw_console() {
  for (int i=0; i<n; i++) {
    for (int j=0; j<m; j++) {
      if (maze[i][j].up()) printf("+   ");
      else printf("+---");
    }
    printf("+\n");
    for (int j=0; j<m; j++) {
      if (maze[i][j].left()) printf("    ");
      else printf("|   ");
    }
    if (maze[i][m-1].right()) printf(" \n");
    else printf("|\n");
  }
  for (int j=0; j<m; j++) {
    if (maze[n-1][j].down()) printf("+   ");
    else printf("+---");
  }
  printf("+\n");
}

int grid_x;
int grid_y;

void render() {
  SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
  SDL_RenderClear(renderer);

  SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

  for (int i=0; i<n; i++) {
    for (int j=0; j<m; j++) {
      SDL_Rect rect{
                    (j*2+1)*grid_y,
                    (i*2+1)*grid_x,
                    grid_y,
                    grid_x};
      SDL_RenderFillRect(renderer, &rect);
      if (maze[i][j].up()) {
        SDL_Rect rect{
                      (j*2+1)*grid_y,
                      (i*2)*grid_x,
                      grid_y,
                      grid_x};
        SDL_RenderFillRect(renderer, &rect);
      }
      if (maze[i][j].down()) {
        SDL_Rect rect{
                      (j*2+1)*grid_y,
                      (i*2+2)*grid_x,
                      grid_y,
                      grid_x};
        SDL_RenderFillRect(renderer, &rect);
      }
      if (maze[i][j].left()) {
        SDL_Rect rect{
                      (j*2)*grid_y,
                      (i*2+1)*grid_x,
                      grid_y,
                      grid_x};
        SDL_RenderFillRect(renderer, &rect);
      }
      if (maze[i][j].right()) {
        SDL_Rect rect{
                      (j*2+2)*grid_y,
                      (i*2+1)*grid_x,
                      grid_y,
                      grid_x};
        SDL_RenderFillRect(renderer, &rect);
      }
    }
  }

  SDL_RenderPresent(renderer);

#ifdef EMSCRIPTEN
  emscripten_cancel_main_loop();
#endif
}

extern "C" {
void init_maze(int _n, int _m, int _h, int _w) {
  n = _n;
  m = _m;
  grid_x = _h / (_n*2+1);
  grid_y = _w / (_m*2+1);

  maze = Maze(n, m);
  maze.wilson();

  assert(SDL_Init(SDL_INIT_VIDEO) == 0);
  SDL_CreateWindowAndRenderer(_w, _h, 0, &window, &renderer);
#ifdef EMSCRIPTEN
  emscripten_set_main_loop(render, 60, 1);
#else
  render();
#endif
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();
}
}
