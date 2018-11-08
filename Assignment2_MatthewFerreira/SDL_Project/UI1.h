#ifndef UI1_H
#define UI1_H

#include "MMath.h"
#include "UIFactory.h"
#include <SDL.h>

using namespace MATH;
class UI1 : public UIFactory {
private:
	SDL_Window *window;
	Matrix4 projectionMatrix;

	SDL_Surface *healthBarImage;
	Vec3 healthBarPos;
	SDL_Rect healthBarRect;
public:
	UI1(SDL_Window* sdlWindow);
	~UI1();
	bool OnCreate();
	void OnDestroy();
	void Update(const float time);
	void Render(SDL_Surface *screenSurface);
};

#endif
