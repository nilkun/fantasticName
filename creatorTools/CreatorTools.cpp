#include "CreatorTools.h"

void TextureCreator::setColor(Uint8 red, Uint8 green, Uint8 blue, Uint8 alpha) {
  color = {red, green, blue, alpha};
}

SDL_Texture* TextureCreator::fromImage(SDL_Renderer *renderer,
  const char* imageLocation)
{
  SDL_Texture *texture = nullptr;
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

  // Clean up
  SDL_FreeSurface(loadImage);
  return texture;
}

SDL_Texture* TextureCreator::fromFontToText(SDL_Renderer* renderer,
  const char* fontName, const char* text, int fontSize = 20)
{

  /* Set font color */
  SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);

  TTF_Init();
  TTF_Font *font;
  if( (font = TTF_OpenFont(fontName, fontSize)) == nullptr )
  {
      std::cout << "File does not exist: " << fontName << std::endl;
  }
  SDL_Surface *surface = TTF_RenderText_Solid(font, text, color);
  SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);

  SDL_FreeSurface(surface);
  TTF_CloseFont(font);
  TTF_Quit();

  return texture;
}

SDL_Texture* TextureCreator::filledRectangle(SDL_Renderer *renderer) {
  SDL_Texture *texture;
  texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, 50, 50);
  SDL_SetRenderTarget(renderer, texture);
  SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
  SDL_RenderFillRect(renderer, NULL);

  // Return the renderer to window
  SDL_SetRenderTarget(renderer, NULL);
  return texture;
}

SDL_Texture* TextureCreator::createFontAtlas(SDL_Renderer* renderer,
  FontAtlas *fontAtlas, const char* fontName, int fontSize)
{
  TTF_Init();
  TTF_Font *font = TTF_OpenFont(fontName, fontSize);

  // Create all pointers
  SDL_Texture* currentLetter = nullptr;
  SDL_Surface *surface = nullptr;
  SDL_Texture* processing = nullptr;

  // Create variables
  SDL_Rect destination = { 0, 0, 0, 0 };  // Where to store the current letter
  int letterHeight = 0;                   // Height of letter
  int letterWidth = 0;                    // Width of letter
  SDL_Rect textureSize = { 0, 0, 0, 0};

  SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
  color = {255, 0, 0};

  /* Get height of font by using "a" */
  surface = TTF_RenderText_Solid(font, std::string(1, 32).c_str(), color);
  textureSize.h = surface -> h;
  textureSize.w = 1024;          // arbitrary

  /* Create the texture for the atlas */
  processing = SDL_CreateTexture(renderer,
    SDL_PIXELFORMAT_RGBA8888,
    SDL_TEXTUREACCESS_TARGET,
    textureSize.w,
    textureSize.h);

  /* set atlas as render target and copy "a" */
  SDL_SetRenderTarget(renderer, processing);
  currentLetter = SDL_CreateTextureFromSurface(renderer, surface);

  /*  get the height and width of the texture
      and then store the location data in the atlas*/
  SDL_QueryTexture(currentLetter, NULL, NULL, &letterWidth, &letterHeight);
  destination.w = letterWidth;
  destination.h = letterHeight;
  fontAtlas->fontMap[32] = destination;

  /* copy letter to atlas and then clean up */
  SDL_RenderCopy(renderer, currentLetter, NULL, &destination);
  SDL_DestroyTexture(currentLetter);
  SDL_FreeSurface(surface);
  /* move the start location forward, could also be set to destination.w */
  destination.x += letterWidth;

  for(int i = 33; i <= 128; i++) {
    /* create surface from font, and then create the texture */
    surface = TTF_RenderText_Solid(font, std::string(1, i).c_str(), color);
    currentLetter = SDL_CreateTextureFromSurface(renderer, surface);

    /* check size and then set location data in atlas */
    SDL_QueryTexture(currentLetter, NULL, NULL, &letterWidth, &letterHeight);
    destination.w = letterWidth;
    destination.h = letterHeight;
    fontAtlas->fontMap[i] = destination;

    /* Check if resize is needed */
    if((destination.x + destination.w) > textureSize.w) {

      int newWidth = textureSize.w * 2;

      SDL_Texture* temp = processing;
      processing = SDL_CreateTexture(renderer,
        SDL_PIXELFORMAT_RGBA8888,
        SDL_TEXTUREACCESS_TARGET,
        newWidth,
        textureSize.h);
      SDL_SetRenderTarget(renderer, processing);
      SDL_RenderCopy(renderer, temp, &textureSize, &textureSize);

      textureSize.w = newWidth;

      SDL_DestroyTexture(temp);
    }

    SDL_RenderCopy(renderer, currentLetter, NULL, &destination);
    SDL_DestroyTexture(currentLetter);
    SDL_FreeSurface(surface);
    destination.x += letterWidth;
  }

  // Prepare the texture
  // Set the width
  textureSize.w = destination.x;

  fontAtlas -> texture = SDL_CreateTexture(renderer,
    SDL_PIXELFORMAT_RGBA8888,
    SDL_TEXTUREACCESS_TARGET,
    textureSize.w,
    textureSize.h);

  // Create final texture!!!
  SDL_SetRenderTarget(renderer, fontAtlas -> texture);
  SDL_RenderCopy(renderer, processing, &textureSize, NULL);

  // Clean up
  SDL_DestroyTexture(processing);
  SDL_SetRenderTarget(renderer, NULL);
  TTF_Quit();
  return fontAtlas -> texture;
}

SDL_Texture* TextureCreator::fromAtlasToText(SDL_Renderer *renderer, std::string text, FontAtlas *fontAtlas, SDL_Color color)
{
  // ERROR CHECKING
  if(!renderer) std::cout << "Error with renderer in AtlasToText";
  if(!fontAtlas) std::cout << "Error with fontAtlas in AtlasToText";
  // Initialize temporary variables and textures
  SDL_Texture* processing;
  SDL_Texture* temp;
  SDL_Rect letterPosition = { 0, 0, 0, fontAtlas -> fontMap[33].h };
  int textureWidth = 100;
  // Set the color of the font
  SDL_SetTextureColorMod(fontAtlas -> texture, color.r, color.g, color.b);

  // Instantiation
  processing = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, textureWidth, letterPosition.h);
  SDL_SetRenderTarget(renderer, processing);

  for(char& c : text) {
    letterPosition.w = fontAtlas->fontMap[(int) c].w;
    // Resize if necessary
    if(textureWidth < letterPosition.w+letterPosition.x) // While oob
    {
      SDL_Rect targetTexture = { 0, 0, textureWidth, letterPosition.h }; // target location of temp texture
      while(textureWidth < letterPosition.w+letterPosition.x) textureWidth *= 2; // In the unlikely case that the letters are bigger than the texture!
      temp = processing;
      processing = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, textureWidth, letterPosition.h);
      SDL_SetRenderTarget(renderer, processing);
      SDL_RenderCopy(renderer, temp, NULL, &targetTexture);
      SDL_DestroyTexture(temp);
    }
    SDL_RenderCopy(renderer, fontAtlas->texture, &fontAtlas->fontMap[(int) c], &letterPosition);
    letterPosition.x += letterPosition.w;
  }
  SDL_Texture* returnTexture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, letterPosition.x, letterPosition.h);
  SDL_SetRenderTarget(renderer, returnTexture);
  // Recycle letterPosition for placing in texture
  letterPosition = { 0, letterPosition.y, letterPosition.x, letterPosition.h };
  SDL_RenderCopy(renderer, processing, &letterPosition, &letterPosition);
  SDL_DestroyTexture(processing);
  SDL_SetRenderTarget(renderer, NULL);
  return returnTexture;
}

SDL_Texture* TextureCreator::fromAtlasToTextbox(
  SDL_Renderer *renderer,
  std::list<std::string> &strings,
  FontAtlas *fontAtlas,
  SDL_Color color
  )
{
  // ERROR CHECKING
  if(!renderer) std::cout << "Error with renderer in AtlasToTextbox";
  if(!fontAtlas) std::cout << "Error with fontAtlas in AtlasToTextbox";
  // Initialize temporary variables and textures
  SDL_Texture* processing;
  SDL_Texture* temp;
  SDL_Rect letterPosition = { 0, 0, 0, fontAtlas -> fontMap[33].h };
  int textureWidth = 100;
  int padding = 2;
  int textureHeight = strings.size() * letterPosition.h + (strings.size() - 1) * padding;
  int nextLine = letterPosition.h + padding;
  int maxWidth = 0;

  // Set the color of the font
  SDL_SetTextureColorMod(fontAtlas -> texture, color.r, color.g, color.b);
  // Instantiation
  processing = SDL_CreateTexture(renderer,
    SDL_PIXELFORMAT_RGBA8888,
    SDL_TEXTUREACCESS_TARGET,
    textureWidth,
    textureHeight);
  SDL_SetRenderTarget(renderer, processing);
  for(auto text : strings) {
    for(char& c : text) {
      letterPosition.w = fontAtlas->fontMap[(int) c].w;
      if((letterPosition.w + letterPosition.x) > maxWidth) maxWidth = letterPosition.w + letterPosition.x;
      // Resize if necessary
      if(textureWidth < letterPosition.w+letterPosition.x) // While oob
      {
        SDL_Rect targetTexture = { 0, 0, textureWidth, textureHeight }; // target location of temp texture
        while(textureWidth < letterPosition.w+letterPosition.x) textureWidth *= 2; // In the unlikely case that the letters are bigger than the texture!
        temp = processing;
        processing = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, textureWidth, textureHeight);
        SDL_SetRenderTarget(renderer, processing);
        SDL_RenderCopy(renderer, temp, NULL, &targetTexture);
        SDL_DestroyTexture(temp);
      }
      SDL_RenderCopy(renderer, fontAtlas->texture, &fontAtlas->fontMap[(int) c], &letterPosition);
      // std::cout << "Processing '" << text << std::endl;
      letterPosition.x += letterPosition.w;
    }
    letterPosition.y += nextLine;
    letterPosition.x = 0;
  }
  SDL_Texture* returnTexture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, maxWidth, textureHeight);
  SDL_SetRenderTarget(renderer, returnTexture);
  // Recycle letterPosition for placing in texture
  letterPosition = { 0, 0, maxWidth, textureHeight };
  SDL_RenderCopy(renderer, processing, &letterPosition, &letterPosition);
  SDL_DestroyTexture(processing);
  SDL_SetRenderTarget(renderer, NULL);
  return returnTexture;
}

FontAtlas TextureCreator::create8bitAtlas(SDL_Renderer *renderer)
{
  FontAtlas bitfont;
  bitfont.texture = fromImage(renderer, "resources/alphabet.png");
  SDL_Rect destination = { 0, 0, 7, 9 };
  for(int i = 32; i <= 128; i++) {
    /* set location data in atlas */
    bitfont.fontMap[i] = destination;
    destination.x += 6;
  }
  return bitfont;
}

void TextureCreator:: showMessage(SDL_Renderer *renderer, std::string message, FontAtlas *bitfont, int yPos, int xPos) {
  SDL_Texture *messageTexture = nullptr;
  messageTexture = fromAtlasToText(renderer, message.c_str(), bitfont, color);
  int texW = 0;
  int texH = 0;
  SDL_QueryTexture(messageTexture, NULL, NULL, &texW, &texH);
  if(xPos == -1) xPos = (1024 - texW)/2; //centered
  SDL_Rect messageLocation = { xPos, yPos, texW, texH };
  SDL_RenderCopy(renderer, messageTexture, NULL, &messageLocation);
  SDL_DestroyTexture(messageTexture);
}
