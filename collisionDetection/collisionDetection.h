/***********************************
  GAME ENGINE WITH A FANTASTIC NAME
  ---------------------------------
  by nilkun

 **********************************/

#ifndef __COLLISIONDETECTION_H__
#define __COLLISIONDETECTION_H__

#include <SDL2/SDL.h>

class CollisionDetection {
public:
  CollisionDetection();
  bool pointVSCircle(float x1, float y1, float radius, float x2, float y2);
  bool pointVSCircle(SDL_Point &point, SDL_Point &circle, float radius);
  bool rectangleVSCircle(SDL_Rect &rect, SDL_Point &circle, float radius);
  bool rectangleVSCircle(SDL_Rect &rect, SDL_Point &circle, int degrees, float radius);
  bool rectangleOutCircle(SDL_Rect &rect, SDL_Point &circle, int degrees, float radius);
  bool rectangleWithinLine(SDL_Rect &point, int line); // provide four x OR y coordinates
  bool rectangleBeyondLine(SDL_Rect &point, int line);
  void getRectangleX(SDL_Rect &src, SDL_Rect &target, int degrees);
  void getRectangleY(SDL_Rect &src, SDL_Rect &target, int degrees);
  bool polygonVSCircle(SDL_Rect &x_coords, SDL_Rect &y_coords, SDL_Point &circle, float radius);
  bool polygonOutCircle(SDL_Rect &x_coords, SDL_Rect &y_coords, SDL_Point &circle, float radius);
};

#endif
