#ifndef __IMAGECREATOR_H__
#define __IMAGECREATOR_H__

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <unordered_map>
#include <iostream>

class FontAtlas {
public:
  std::unordered_map<int, SDL_Rect> fontMap;
  SDL_Texture *texture;
};

class ImageCreator {
public:
  SDL_Texture *getTexture(SDL_Renderer *renderer, const char* imageLocation);
  void setProperties(SDL_Texture *texture, int *w, int *h, float *ratio);
  SDL_Texture* filledRectangle(SDL_Renderer* renderer);
  SDL_Texture* fromText(SDL_Renderer* renderer, const char* fontName, const char* text, int fontSize);
  void setColor(Uint8 red, Uint8 green, Uint8 blue);
  SDL_Color color;
  SDL_Texture* makeFontAtlas(SDL_Renderer* renderer, FontAtlas *fontAtlas, const char* fontName, int fontSize);
};

void print(FontAtlas *fontAtlas);
void renderText(SDL_Renderer *renderer, std::string text, FontAtlas *fontAtlas);

#endif
