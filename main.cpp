#include <SDL2/SDL.h>
#include <cassert>

#ifdef __EMSCRIPTEN__
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
      if (maze[i][j].top()) printf("+   ");
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

void render() {
  SDL_SetRenderDrawColor(renderer, 200, 0, 0, 255);
  SDL_RenderClear(renderer);

  SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
  SDL_RenderDrawLine(renderer, 0, 0, 640, 320);
  SDL_RenderPresent(renderer);

#ifdef EMSCRIPTEN
  emscripten_cancel_main_loop();
#endif
}

int main() {
  n = 10, m = 10;
  maze = Maze(n, m);
  maze.wilson();
  draw_console();

  assert(SDL_Init(SDL_INIT_VIDEO) == 0);
  SDL_CreateWindowAndRenderer(640, 320, 0, &window, &renderer);
#ifdef EMSCRIPTEN
  emscripten_set_main_loop(render, 60, 1);
#else
  render();
#endif
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();

  return 0;
}
