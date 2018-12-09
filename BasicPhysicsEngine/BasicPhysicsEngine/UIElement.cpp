#include "UIElement.h"


UIElement::UIElement(char * _imageName, Vec3 _position)
{
	bodyImage = IMG_Load(_imageName);
	if (bodyImage == nullptr) {
		/// What should we do?
	}

	position = _position;
}

SDL_Surface* UIElement::getImage() {
	return bodyImage;
}
