#ifndef __CREATORTOOLS_H__
#define __CREATORTOOLS_H__

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <unordered_map>
#include <iostream> // For some error messages
#include <string>
#include <list>

class FontAtlas {
public:
  std::unordered_map<int, SDL_Rect> fontMap;
  SDL_Texture *texture;
};

class TextureCreator {
public:

//WHAT ARE THESE?
  void setColor(Uint8 red, Uint8 green, Uint8 blue, Uint8 alpha);
  SDL_Color color;


  // Image
  SDL_Texture *fromImage(
    SDL_Renderer *renderer,
    const char* imageLocation
  );
  // Font to Text (slower than atlas to text)
  SDL_Texture* fromFontToText(
    SDL_Renderer* renderer,
    const char* fontName,
    const char* text,
    int fontSize
  );
  // Filled rectangle
  SDL_Texture* filledRectangle(
    SDL_Renderer* renderer
  );
  // fontAtlas
  SDL_Texture* createFontAtlas(
    SDL_Renderer* renderer,
    FontAtlas *fontAtlas,
    const char* fontName,
    int fontSize
  );
  // Atlas to Text
  SDL_Texture* fromAtlasToText(
    SDL_Renderer *renderer,
    std::string text,
    FontAtlas *fontAtlas,
    SDL_Color color = { 0, 255, 0, 0 }
  );
  SDL_Texture* fromAtlasToTextbox(
    SDL_Renderer *renderer,
    std::list<std::string> &strings,
    FontAtlas *fontAtlas,
    SDL_Color color = { 0, 255, 0, 0 }
  );
};

#endif
