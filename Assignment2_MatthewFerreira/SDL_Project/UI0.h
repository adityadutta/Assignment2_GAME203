#ifndef UI0_H
#define UI0_H

#include "MMath.h"
#include "UIFactory.h"
#include <SDL.h>

using namespace MATH;
class UI0 : public UIFactory {
private:
	SDL_Window *window;
	Matrix4 projectionMatrix;

	SDL_Surface *healthBar1Image;
	Vec3 healthBar1Pos;
	SDL_Rect healthBar1Rect;

	SDL_Surface *healthBar2Image;
	Vec3 healthBar2Pos;
	SDL_Rect healthBar2Rect;
public:
	UI0(SDL_Window* sdlWindow);
	~UI0();
	bool OnCreate();
	void OnDestroy();
	void Update(const float time);
	void Render(SDL_Surface *screenSurface);
};

#endif
