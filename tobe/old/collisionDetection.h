#ifndef __COLLISION__
#define __COLLISION__

// bool rectRect(SDL_Rect *source, SDL_Rect *Target) {
//   (if source.)
// //  if(SDL_IntersectRect(const SDL_Rect* A, const SDL_Rect* B, SDL_Rect*       result))
// }

bool dotCheck(SDL_Rect *target, int x, int *offset) {
  if (x < target -> x) {
    *offset = target-> x - x;
    return true;
  }
  else if (x > target-> x + target-> w) {
    *offset = (target-> x + target-> w) - x;
    return true;
  }
  return false;
}

#endif
