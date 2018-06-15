#include "window.h"

Screen::Screen():
  m_window(NULL),
  m_renderer(NULL),
  m_title("NILKUN WINDOW HANDLER 0.4")
{
  init();
}

Screen::Screen(const char *title, int width, int height):
  m_window(NULL),
  m_renderer(NULL),
  m_title(title),
  width(width),
  height(height)
{
  init();
}

void Screen::init() {
  if(SDL_Init(SDL_INIT_VIDEO) < 0) {
    std::cout << "Error initializing SDL." << std::endl;
  }
  m_window =
    SDL_CreateWindow( m_title,
                      SDL_WINDOWPOS_UNDEFINED,
                      SDL_WINDOWPOS_UNDEFINED,
                      width,
                      height,
                      SDL_WINDOW_SHOWN);
  if(m_window == NULL) {
    SDL_Quit();
  }
  m_renderer =  SDL_CreateRenderer(m_window, -1,
                SDL_RENDERER_PRESENTVSYNC);


  if(m_renderer == NULL) {
    SDL_DestroyWindow(m_window);
    SDL_Quit();
  }
}

void Screen::close() {
  SDL_DestroyRenderer(m_renderer);
  SDL_DestroyWindow(m_window);
  SDL_Quit();
}

SDL_Renderer* Screen::getRenderer() {
  return m_renderer;
}

Viewport* Screen::addViewport() {
  viewports.push_back(Viewport());
  return &viewports.back();
}

Viewport* Screen::addViewport(SDL_Rect &position) {
  viewports.push_back(Viewport(position));
  return &viewports.back();
}
