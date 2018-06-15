#include "window.h"

void Screen::render() {
  SDL_RenderPresent(m_renderer);
}

void Screen::clear() {
  SDL_SetRenderDrawColor(m_renderer, 0, 0, 0, 0); // SET SCREEN TO BLACK
  SDL_RenderClear(m_renderer);
  }
