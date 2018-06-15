#include "screen.h"
#include <SDL2/SDL_image.h>







SDL_Renderer* Screen::getRenderer() {
  return m_renderer;
}

void Screen::close() {
  SDL_DestroyRenderer(m_renderer);
  SDL_DestroyTexture(m_texture);
  SDL_DestroyWindow(m_window);
  SDL_Quit();
}

void Screen::toggleScreen() {
  switch(screenMode) {
    case 1:
      SDL_SetWindowFullscreen(m_window, SDL_WINDOW_FULLSCREEN);
      screenMode++;
      break;
    case 2:
      SDL_SetWindowFullscreen(m_window, SDL_WINDOW_FULLSCREEN_DESKTOP);
      screenMode++;
      break;
    case 3:
      SDL_SetWindowFullscreen(m_window, 0);
      screenMode=1;
      break;
  }


}

void Screen::resize() {
  //if(x < 1) x = 1;
  //if(y < 1) y = 1;
  //SDL_GetWindowSize(m_window, &width, &height);
  SDL_GetRendererOutputSize(m_renderer, &width, &height);
  // SDL_GetRendererOutputSize(m_renderer, &width, &height);
  // std::cout << "SDL_GetRendererOutputSize: " << width << " " << height;
  // SDL_GetWindowSize(m_window, &width, &height);
  // std::cout << "SDL_GetGetWindowSize: " << width << " " << height;
  // SDL_GL_GetDrawableSize(m_window, &width, &height);
  // std::cout << "SDL_GL_GetDrawableSize: " << width << " " << height;
}

void Screen::Block::setTexture(SDL_Texture *texture) {
  this -> texture = texture;
}
