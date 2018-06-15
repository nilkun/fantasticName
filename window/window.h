#ifndef __WINDOW_H__
#define __WINDOW_H__

#include <vector> // Used for the viewport vector
#include <SDL2/SDL.h>
#include <iostream> // for error messages
#include "viewport.h"

class Screen {

private:
  int width;
  int height;

  SDL_Window *m_window;
  SDL_Renderer *m_renderer;
  const char* m_title;
  std::vector<Viewport> viewports;

/* initialization.cpp */
public:
  Screen();
  Screen(const char* title, int width, int height);
  void init();
  void close();
  SDL_Renderer* getRenderer();
  Viewport* addViewport() ;
  Viewport* addViewport(SDL_Rect &position);


  void clear();
  void render();
};

#endif
