#ifndef __VIEWPORT_H__
#define __VIEWPORT_H__

#include <SDL2/SDL.h>

struct Viewport
{
  SDL_Rect position; // where to position the viewport
  Viewport();
  Viewport(SDL_Rect position);
  void setPosition(SDL_Rect position);
};

#endif
