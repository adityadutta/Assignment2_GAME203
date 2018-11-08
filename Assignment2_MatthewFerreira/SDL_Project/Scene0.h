#ifndef SCENE0_H
#define SCENE0_H

#include "MMath.h"
#include "Scene.h"
#include <SDL.h>

#include "UI0.h"
#include "UI1.h"

using namespace MATH;
class Scene0 : public Scene {
private:
	SDL_Window *window;
	Matrix4 projectionMatrix;

	SDL_Surface *jetSkiImage;
	Vec3 jetSkiPos;
	SDL_Rect jetSkiRect;
public:
	Scene0(SDL_Window* sdlWindow);
	~Scene0();
	UIFactory *ui;
	bool OnCreate();
	void OnDestroy();
	void Update(const float time);
	void Render();
	void HandleEvents(const SDL_Event& event);
};

#endif

