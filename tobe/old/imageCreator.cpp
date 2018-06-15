
#include "imageCreator.h"
#include <string>
SDL_Texture* ImageCreator::getTexture(SDL_Renderer *renderer, const char* imageLocation) {

  SDL_Texture *texture;
  texture = NULL;

  SDL_Surface* loadImage = IMG_Load(imageLocation);
  if( loadImage == NULL )
  {
      std::cout << "Unable to load file. (@ getTexture.loadImage)"<< std::endl;
  }
  texture = SDL_CreateTextureFromSurface(renderer, loadImage);
  if(texture == NULL)
  {
      std::cout << "Unable to load file. (@ getTexture.texture) REASON:" << SDL_GetError() << std::endl;
  }
  SDL_FreeSurface(loadImage);

  return texture;
}

void ImageCreator::setProperties(SDL_Texture *texture, int *w, int *h, float *ratio) {
  SDL_QueryTexture(texture, NULL, NULL, w, h);
  *ratio = static_cast<float>(*h)/(*w);

}

SDL_Texture* ImageCreator::filledRectangle(SDL_Renderer *renderer) {
  SDL_Texture *texture;
  // SDL_Rect rectangle;
  // Create a 1 X 1 texture
  texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, 50, 50);
  SDL_SetRenderTarget(renderer, texture);
  SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255);
  SDL_RenderFillRect(renderer, NULL);
  SDL_SetRenderTarget(renderer, NULL);

  return texture;
}

SDL_Texture* ImageCreator::fromText(SDL_Renderer* renderer, const char* fontName, const char* text, int fontSize = 20) {
  // SIZE AND COLOR!!!

  SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

  TTF_Init();
  TTF_Font *font = TTF_OpenFont(fontName, fontSize);
  SDL_Surface *surface = TTF_RenderText_Solid(font, text, color);
  SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);

  SDL_FreeSurface(surface);
  TTF_CloseFont(font);
  TTF_Quit();

    //kill init
    // kill font
  return texture;
  }

void ImageCreator::setColor(Uint8 red, Uint8 green, Uint8 blue) {
  color = {red, green, blue};
}
//
// struct TextureAtlas{
//   SDL_Texture* texture;
//   std::vector<SDL_Rect> index;
// }
// class FontAtlas {

  // SDL_Texture* getChar(int index) {
  //   return fontMap;
  // }
  // SDL_Texture* getAtlas() {
  //   return fontTexture;
  // }
  // fontMap[32] = "rect";

// }
// struct FontIndex {
//   SDL_Rect textureLocation;
// }
SDL_Texture* ImageCreator::makeFontAtlas(SDL_Renderer* renderer, FontAtlas *fontAtlas, const char* fontName, int fontSize) {
  SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

  TTF_Init();
  TTF_Font *font = TTF_OpenFont(fontName, fontSize);
  // SDL_Texture* tempAtlas;
  //SDL_Texture* fontAtlas;
  SDL_Texture* currentLetter;
  SDL_Surface *surface;
  SDL_Rect destination = { 0, 0, 0, 0 };
  int atlasHeight = 0;
  int atlasWidth = 0;
  int letterHeight = 0;
  int letterWidth = 0;

  SDL_Texture* copyTexture;
  SDL_Rect oldTextureSize;
  color = {255, 0, 0};

  // FIRST INITIALIZE HEIGHT OF FONT, MAYBE ALSO SIZE
  surface = TTF_RenderText_Solid(font, std::string(1, 32).c_str(), color);

  atlasHeight = surface -> h;
  atlasWidth = 1024;
  destination = { 0, 0, 0, 0 };
  oldTextureSize = { 0, 0, atlasWidth, atlasHeight};

  fontAtlas -> texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, atlasWidth, atlasHeight);
  SDL_SetRenderTarget(renderer, fontAtlas->texture);
  currentLetter = SDL_CreateTextureFromSurface(renderer, surface);

  SDL_QueryTexture(currentLetter, NULL, NULL, &letterWidth, &letterHeight);
  destination.w = letterWidth;
  destination.h = letterHeight;
  fontAtlas->fontMap[32] = destination;

  SDL_RenderCopy(renderer, currentLetter, NULL, &destination);
  SDL_DestroyTexture(currentLetter);
  SDL_FreeSurface(surface);
  destination.x += letterWidth;
//  int lineBreaker = 1;
  //

  for(int i = 33; i <= 128; i++) {
    surface = TTF_RenderText_Solid(font, std::string(1, i).c_str(), color);
    currentLetter = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_QueryTexture(currentLetter, NULL, NULL, &letterWidth, &letterHeight);
    destination.w = letterWidth;
    destination.h = letterHeight;
    fontAtlas->fontMap[i] = destination;

    // TEST FOR SIZE
    if((destination.x + destination.w) > atlasWidth) {
      atlasWidth *= 2;
      copyTexture = fontAtlas -> texture;
      fontAtlas -> texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, atlasWidth, atlasHeight);
      SDL_SetRenderTarget(renderer, fontAtlas->texture);
      SDL_RenderCopy(renderer, copyTexture, &oldTextureSize, &oldTextureSize);
      oldTextureSize.w = atlasWidth;
      SDL_DestroyTexture(copyTexture);
    }


    SDL_RenderCopy(renderer, currentLetter, NULL, &destination);
    SDL_DestroyTexture(currentLetter);
    SDL_FreeSurface(surface);
    destination.x += letterWidth;
  }
  // Create final texture!!!
  copyTexture = fontAtlas -> texture;
  fontAtlas -> texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, destination.x, atlasHeight);
  SDL_SetRenderTarget(renderer, fontAtlas->texture);
  oldTextureSize.w = destination.x;
  SDL_RenderCopy(renderer, copyTexture, &oldTextureSize, NULL);
  SDL_DestroyTexture(copyTexture);

  SDL_SetRenderTarget(renderer, NULL);
  // SDL_DestroyTexture(tempAtlas);
  //SDL_FreeSurface(surface);
  void TTF_Quit();
  return fontAtlas -> texture;
}


  // If too wide, expand
void print(FontAtlas *fontAtlas) {
  // for(int i = 32; i <=128; i++) {
  //   std::cout << "Letter" << (char) i << "dimensions: x:" << fontAtlas -> fontMap[i].x << " y: " << fontAtlas ->fontMap[i].y << " w: " << fontAtlas ->fontMap[i].w << " h: " << fontAtlas ->fontMap[i].h << std::endl;
  // }
}

void renderText(SDL_Renderer *renderer, std::string text, FontAtlas *fontAtlas) {
  int xLocation = 0;
  SDL_Rect target = { 0, 0, 0, 0 };
  target.x = xLocation;
  target.y = 0;
  target.h = fontAtlas->fontMap[33].h;
  //target.w = fontAtlas->fontMap[(int) c].w;

  for(char& c : text) {

    target.w = fontAtlas->fontMap[(int) c].w;
    //std::cout << "Letter: " << c << " Int value: " << (int) c << std::endl;
    // std::cout << "Processing: " << (int) c << "which is char: " << c << std::endl;
  //  std::cout << "x: " << fontAtlas->fontMap[(int) c].x << " y: " <<fontAtlas->fontMap[(int) c].y << " w: " << fontAtlas->fontMap[(int) c].w << " h: " <<fontAtlas->fontMap[(int) c].h <<std::endl;
  //  std::cout << "x: " << target.x << " y: " <<target.y << " w: " << target.w << " h: " <<target.h <<std::endl;
    SDL_RenderCopy(renderer, fontAtlas->texture, &fontAtlas->fontMap[(int) c], &target);
    target.x += target.w;
  }
}
