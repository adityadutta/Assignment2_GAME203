#ifndef UIELEMENT_H
#define UIELEMENT_H

#include<SDL.h>
#include<SDL_image.h>
#include"Vector.h"

using namespace MATH;
class UIElement
{
	SDL_Surface *bodyImage;
public:
	Vec3 position;								//variable to hold the value of position

	UIElement(char* _imageName, Vec3 _position);

	SDL_Surface* getImage();
};
#endif //!UIELEMENT_H