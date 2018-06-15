#include "screen.h"
#include <iostream>
//
// void Screen::draw() {
//   // Renders the whole texture
//   for(Block block : blocks) {
//
//     SDL_RenderCopy(m_renderer, block.texture, NULL, &block.targetDimensions);
//   }
// }
// Screen::Block::Block(SDL_Rect sourceDimensions, SIZE_MODE sizeMode, float ratioX, float ratioY) :
//     sourceDimensions(sourceDimensions), sizeMode(sizeMode), ratioX(ratioX), ratioY(ratioY)
// {
//   targetDimensions = sourceDimensions;
// }
//
// Screen::Block* Screen::add(SDL_Rect sourceDimensions, SIZE_MODE sizeMode, float ratioX, float ratioY) {
//   Block adding(sourceDimensions, sizeMode, ratioX, ratioY);
//   blocks.push_back(adding);
//   return &blocks.back();
// }
//
// Screen::Block* Screen::add(int x, int y, int w, int h, SIZE_MODE sizeMode, float ratioX, float ratioY) {
//   SDL_Rect sourceDimensions = { x, y, w, h };
//   Block adding(sourceDimensions, sizeMode, ratioX, ratioY);
//   blocks.push_back(adding);
//   return &blocks.back();
// }
//
//
// void Screen::rescale() {
//   int xCoordinate = 0;
//   int yCoordinate = 0;
//   for(Block& block: blocks) {
//     block.targetDimensions.x = xCoordinate;
//     block.targetDimensions.y = yCoordinate;
//     block.rescale(width, height, fixedY);
//     xCoordinate += block.targetDimensions.w;
//     if (block.isLast) {
//       yCoordinate += block.targetDimensions.h;
//       xCoordinate = 0;
//     }
//   }
// }
// void Screen::calculateFreeArea() {
//   bool found = false;
//   fixedY = 0;
//   for(Block& block: blocks) {
//     if(!found) {
//       if(block.sizeMode == FIXED || block.sizeMode == FIXED_Y) {
//         fixedY += block.sourceDimensions.h;
//         found = true;
//       }
//     }
//     if (block.isLast) found = false;
//   }
// }
// void Screen::Block::rescale(int width, int height, int fixedY) {
//   int freeY = height - fixedY;
//   switch(sizeMode) {
//     case FIXED:
//       break;
//     case ASPECT_BOUND_TO_X:
//
//       targetDimensions.w = (width * ratioY);
//       targetDimensions.h = (targetDimensions.w * ratioY);
//       break;
//     case ASPECT_BOUND_TO_Y:
//       targetDimensions.h = (freeY * ratioY);
//       targetDimensions.w = (targetDimensions.h / ratioX);
//       break;
//     case STRETCH:
//       targetDimensions.w = (width * ratioX);
//       targetDimensions.h = (freeY * ratioY);
//       break;
//     case FIXED_X:
//       break;
//     case FIXED_Y:
//       targetDimensions.w = width - targetDimensions.x;
//       break;
//     case AUTOSCALE:
//       targetDimensions.h = freeY * ratioY;
//       targetDimensions.w = targetDimensions.h / ratioX;
//       if(targetDimensions.w > width) {
//         targetDimensions.w = (width);
//         targetDimensions.h = (targetDimensions.w * ratioX);
//       }
//
//   }
// }
