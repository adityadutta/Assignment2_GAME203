#ifndef MARIOGAME_H
#define MARIOGAME_H

#include "Matrix.h"
#include"Vector.h"
#include "Scene.h"
#include<vector>
#include "Animation.h"
#include <SDL.h>
#include<SDL_image.h>
#include <memory>

class Body;
using namespace MATH;
class MarioGame : public Scene {
private:
	SDL_Window *window;
	Matrix4 projectionMatrix;

	Body* player;
	Body* collector;
	std::vector<Body*> bodies;
	SDL_Renderer *renderer;

	float elapsedTime;
	bool isRunning;

	SDL_Surface* background;

	SDL_Rect playerRectangle;
	SDL_Rect backgroundRectangle;
	SDL_Rect groundRect;

	void clampVelocity();

	void ScrollCamera();
	SDL_Rect cameraRect;
	float cameraScrollSpeed;
	std::unique_ptr <Animation> anims;

public:
	MarioGame(SDL_Window* sdlWindow);
	bool OnCreate();
	void OnDestroy();
	void Update(const float time);
	void Render();
	void HandleEvents(const SDL_Event &_event);
	void AddBody(Body* body);
};

#endif //!MARIOGAME_H

