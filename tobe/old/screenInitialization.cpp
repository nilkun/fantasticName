#include "screen.h"

Screen::Screen():
  m_window(NULL), m_renderer(NULL), m_texture(NULL), m_title("NILKUN WINDOW HANDLER 0.3") {
    init();
  }

Screen::Screen(const char *title, int width, int height):
  m_window(NULL), m_renderer(NULL), m_texture(NULL),
  m_title(title), width(width), height(height) {
    init();
  }

void Screen::init() {
  if(SDL_Init(SDL_INIT_VIDEO) < 0) {
    cout << "Error initializing SDL." << endl;
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
  m_texture =  SDL_CreateTexture(
                          m_renderer,
                          SDL_PIXELFORMAT_RGBA8888,
                          SDL_TEXTUREACCESS_STATIC,
                          width,
                          height);

  if(m_renderer == NULL) {
    SDL_DestroyWindow(m_window);
    SDL_Quit();
  }
  if(m_texture == NULL) {
    SDL_DestroyRenderer(m_renderer);
    SDL_DestroyWindow(m_window);
    SDL_Quit();
  }
}

void Screen::close() {
  SDL_DestroyRenderer(m_renderer);
  SDL_DestroyTexture(m_texture);
  SDL_DestroyWindow(m_window);
  SDL_Quit();
}
