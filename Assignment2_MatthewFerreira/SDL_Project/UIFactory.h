#ifndef UIFACTORY_H
#define UIFACTORY_H

#include <SDL.h>

class UIFactory {
public:
	virtual bool OnCreate() = 0;
	virtual void OnDestroy() = 0;
	virtual void Update(const float time) = 0;
	virtual void Render(SDL_Surface *screenSurface) = 0;
};

#endif