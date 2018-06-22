#include "collisionDetection.h"
#include <cmath>
#include <iostream>
CollisionDetection::CollisionDetection() {

}

bool CollisionDetection::pointVSCircle(float x1, float y1, float radius, float x2, float y2) {
  int x = (x1 - x2)*(x1 - x2);
  int y = (y1 - y2)*(y1 - y2);
  int distance = x + y;
  int collisionRadius = radius * radius;
  if(collisionRadius >= distance) return true;
  else return false;
}
bool CollisionDetection::pointVSCircle(SDL_Point &point, SDL_Point &circle, float radius) {
  int x = (point.x - circle.x)*(point.x - circle.x);
  int y = (point.y - circle.y)*(point.y - circle.y);

  int distance = x + y;
  int collisionRadius = radius * radius;
  if(collisionRadius >= distance) return true;
  else return false;
}

bool CollisionDetection::rectangleVSCircle(SDL_Rect &rect, SDL_Point &circle, float radius)
{
  // pointVSCircle code
  // top corner
  int x = (rect.x - circle.x)*(rect.x - circle.x);
  int y = (rect.y - circle.y)*(rect.y - circle.y);
  int distance = x + y;
  int collisionRadius = radius * radius;
  if(collisionRadius >= distance) return true;

  // top right
  x = (rect.x + rect.w - circle.x)*(rect.x + rect.w - circle.x);
  y = (rect.y - circle.y)*(rect.y - circle.y);
  distance = x + y;
  collisionRadius = radius * radius;
  if(collisionRadius >= distance) return true;

  // bottom right
  x = (rect.x + rect.w - circle.x)*(rect.x + rect.w - circle.x);
  y = (rect.y + rect.h - circle.y)*(rect.y + rect.h - circle.y);
  distance = x + y;
  collisionRadius = radius * radius;
  if(collisionRadius >= distance) return true;

  // bottom left
  x = (rect.x - circle.x)*(rect.x - circle.x);
  y = (rect.y + rect.h - circle.y)*(rect.y + rect.h - circle.y);
  distance = x + y;
  collisionRadius = radius * radius;
  if(collisionRadius >= distance) return true;

  return false; // NOT colliding
}

bool CollisionDetection::polygonVSCircle(SDL_Rect &x_coords, SDL_Rect &y_coords, SDL_Point &circle, float radius)
{
  float posX = (x_coords.x - circle.x)*(x_coords.x - circle.x);
  float posY = (y_coords.x - circle.y)*(y_coords.x - circle.y);
  float distance = posX + posY;
  float collisionRadius = radius * radius;
  if(collisionRadius >= distance) return true;

  posX = (x_coords.y - circle.x)*(x_coords.y - circle.x);
  posY = (y_coords.y - circle.y)*(y_coords.y - circle.y);
  distance = posX + posY;
  collisionRadius = radius * radius;
  if(collisionRadius >= distance) return true;

  posX = (x_coords.w - circle.x)*(x_coords.w - circle.x);
  posY = (y_coords.w - circle.y)*(y_coords.w - circle.y);
  distance = posX + posY;
  collisionRadius = radius * radius;
  if(collisionRadius >= distance) return true;

  posX = (x_coords.h - circle.x)*(x_coords.h - circle.x);
  posY = (y_coords.h - circle.y)*(y_coords.h - circle.y);
  distance = posX + posY;
  collisionRadius = radius * radius;
  if(collisionRadius >= distance) return true;

  return false;
}

bool CollisionDetection::polygonOutCircle(SDL_Rect &x_coords, SDL_Rect &y_coords, SDL_Point &circle, float radius)
{
  float posX = (x_coords.x - circle.x)*(x_coords.x - circle.x);
  float posY = (y_coords.x - circle.y)*(y_coords.x - circle.y);
  float distance = posX + posY;
  float collisionRadius = radius * radius;
  if(collisionRadius < distance) return true;

  posX = (x_coords.y - circle.x)*(x_coords.y - circle.x);
  posY = (y_coords.y - circle.y)*(y_coords.y - circle.y);
  distance = posX + posY;
  collisionRadius = radius * radius;
  if(collisionRadius < distance) return true;

  posX = (x_coords.w - circle.x)*(x_coords.w - circle.x);
  posY = (y_coords.w - circle.y)*(y_coords.w - circle.y);
  distance = posX + posY;
  collisionRadius = radius * radius;
  if(collisionRadius < distance) return true;

  posX = (x_coords.h - circle.x)*(x_coords.h - circle.x);
  posY = (y_coords.h - circle.y)*(y_coords.h - circle.y);
  distance = posX + posY;
  collisionRadius = radius * radius;
  if(collisionRadius < distance) return true;

  return false;
}


bool CollisionDetection::rectangleVSCircle(SDL_Rect &rect, SDL_Point &circle, int degrees, float radius) {
  float PI = 3.14159265;
  float radians = PI * degrees / 180;
  float x = rect.w * cos(radians);
  float y = rect.h * sin(radians);
  float sinX = rect.w * sin(radians);
  float cosY = rect.h * cos(radians);
  //float ratio = rect.h/rect.w;
  //SDL_Point current;
  std::cout << x << " = " << sin(radians) << " from " << radians << std::endl;
  std::cout << PI << " and " << degrees << std::endl;
  std::cout << y << std::endl;
    // pointVSCircle code
  // top corner (same) could be different if axis are involved...
  //current = { rect.x, rect.y };
  float pointX = rect.x;
  float pointY = rect.y;
  float posX = (pointX - circle.x)*(pointX - circle.x);
  float posY = (pointY - circle.y)*(pointY - circle.y);
  float distance = posX + posY;
  float collisionRadius = radius * radius;
  std::cout << distance << " at1 " << pointY << std::endl;
  if(collisionRadius >= distance) return true;

    // top right
  pointX += x;
  pointY += y;
  posX = (pointX - circle.x)*(pointX - circle.x);
  posY = (pointY - circle.y)*(pointY - circle.y);
  distance = posX + posY;
  std::cout << distance << " at2 " << pointY << std::endl;
  if(collisionRadius >= distance) return true;

  // bottom right
  pointX -= sinX;
  pointY += cosY;
  posX = (pointX - circle.x)*(pointX - circle.x);
  posY = (pointY - circle.y)*(pointY - circle.y);
  distance = posX + posY;
  std::cout << distance << " at3 " << pointY << std::endl;
  if(collisionRadius >= distance) return true;

  // bottom left
  pointX -= x;
  pointY -= y;
  posX = (pointX - circle.x)*(pointX - circle.x);
  posY = (pointY - circle.y)*(pointY - circle.y);
  distance = posX + posY;
  std::cout << distance << " at4 " << pointY << std::endl;
  if(collisionRadius >= distance) return true;
  return false;
}

bool CollisionDetection::rectangleOutCircle(SDL_Rect &rect, SDL_Point &circle, int degrees, float radius) {
  float PI = 3.14159265;
  float radians = PI * degrees / 180;
  float x = rect.w * cos(radians);
  float y = rect.h * sin(radians);
  float sinX = rect.w * sin(radians);
  float cosY = rect.h * cos(radians);
  // float ratio = rect.h/rect.w;
//  SDL_Point current;
  std::cout << x << " = " << sin(radians) << " from " << radians << std::endl;
  std::cout << PI << " and " << degrees << std::endl;
  std::cout << y << std::endl;

  // pointVSCircle code
  // top corner (same) could be different if axis are involved...
  //current = { rect.x, rect.y };
  float pointX = rect.x;
  float pointY = rect.y;
  float posX = (pointX - circle.x)*(pointX - circle.x);
  float posY = (pointY - circle.y)*(pointY - circle.y);
  float distance = posX + posY;
  float collisionRadius = radius * radius;
  std::cout << distance << " at1 " << pointY << std::endl;
  if(collisionRadius < distance) return true;

    // top right
  pointX += x;
  pointY += y;
  posX = (pointX - circle.x)*(pointX - circle.x);
  posY = (pointY - circle.y)*(pointY - circle.y);
  distance = posX + posY;
  std::cout << distance << " at2 " << pointY << std::endl;
  if(collisionRadius < distance) return true;

  // bottom right
  pointX -= sinX;
  pointY += cosY;
  posX = (pointX - circle.x)*(pointX - circle.x);
  posY = (pointY - circle.y)*(pointY - circle.y);
  distance = posX + posY;
  std::cout << distance << " at3 " << pointY << std::endl;
  if(collisionRadius < distance) return true;

  // bottom left
  pointX -= x;
  pointY -= y;
  posX = (pointX - circle.x)*(pointX - circle.x);
  posY = (pointY - circle.y)*(pointY - circle.y);
  distance = posX + posY;
  std::cout << distance << " at4 " << pointY << std::endl;
  if(collisionRadius < distance) return true;
  return false;
}

bool CollisionDetection::rectangleWithinLine(SDL_Rect &point, int line)
{
  if(point.x < line) return true;
  else if(point.y < line) return true;
  else if(point.w < line) return true;
  else if(point.h < line) return true;
  return false;
}

bool CollisionDetection::rectangleBeyondLine(SDL_Rect &point, int line)
{
  if(point.x > line) return true;
  else if(point.y > line) return true;
  else if(point.w > line) return true;
  else if(point.h > line) return true;
  return false;
}

void CollisionDetection::getRectangleX(SDL_Rect &src, SDL_Rect &target, int degrees) // PROVIDE THE REAL X OR Y COORDINATES OF SKEWED RECTANGLE
{
  float PI = 3.14159265;
  float radians = PI * degrees / 180;
  float constant = src.w * cos(radians);
  float sine = src.w * sin(radians);

  float processing;
  processing = src.x;
  target.x = src.x; // ok!
  processing += constant;
  target.y = processing; // ok!
  processing -= sine;
  target.w = processing;
  processing -= constant;
  target.h = processing;
}
void CollisionDetection::getRectangleY(SDL_Rect &src, SDL_Rect &target, int degrees) // PROVIDE THE REAL X OR Y COORDINATES OF SKEWED RECTANGLE
{
  float PI = 3.14159265;
  float radians = PI * degrees / 180;
  float constant = src.h * sin(radians);
  float cosine = src.h * cos(radians);

  float processing;
  processing = src.y;
  target.x = src.y; // ok!
  processing += constant;
  target.y = processing; // ok!
  processing += cosine;
  target.w = processing;
  processing -= constant;
  target.h = processing;
}
