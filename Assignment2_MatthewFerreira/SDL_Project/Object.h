#ifndef OBJECT_H
#define OBJECT_H

#include "MMath.h"
#include <SDL.h>

using namespace MATH;

class Object
{
public:
	SDL_Surface *image;
	Vec3 pos;
	SDL_Rect rect;

	inline void SetImage(SDL_Surface* image_) {
		image = image_;
	}
	inline void SetPos(Vec3 pos_) {
		pos = pos_;
	}
};
#endif

