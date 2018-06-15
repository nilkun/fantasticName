#include "viewport.h"

Viewport::Viewport()
{
  position = { 0, 0, 0, 0};
};

Viewport::Viewport(SDL_Rect position)
{
  this -> position = position;
};

void Viewport::setPosition(SDL_Rect position)
{
  this -> position = position;
};
