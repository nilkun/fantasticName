#include "screen.h"



void Screen::render() {
  SDL_RenderPresent(m_renderer);
}


void Screen::clear() {
  SDL_SetRenderDrawColor(m_renderer, 255, 0, 0, 0); // SET SCREEN TO RED
  SDL_RenderClear(m_renderer);
  }

SDL_Renderer* Screen::getRenderer() {
  return m_renderer;
}

Screen::Viewport* Screen::newViewport() {
  //Viewport newViewport;
  viewports.push_back(Viewport());
  return &viewports.back();
}
//
// void Screen::setViewport(Viewport *viewport, int x, int y, int w, int h); {
//   viewport.dimensions = { x, y, w, h };
// }
