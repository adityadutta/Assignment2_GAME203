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
#include "InputManager.h"

class Body;
using namespace MATH;
class MarioGame : public Scene {
private:
	SDL_Window *window;
	Matrix4 projectionMatrix;

	Body* player;
	Body* ground;
	std::vector<Body*> coins;
	SDL_Renderer *renderer;

	float elapsedTime;
	bool isRunning;

	SDL_Surface* background;

	SDL_Rect playerRectangle;
	SDL_Rect backgroundRectangle;
	SDL_Rect groundRect;
	SDL_Rect coinRect;

	SDL_Rect cameraRect;
	float cameraScrollSpeed;


	std::shared_ptr<Animation> anims;
	std::unique_ptr <InputManager> HandleControls;
	std::unique_ptr<UIManager> manager; //object UIManager 

	//player stuff
	bool isGrounded = false;
	int playerCoins;

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

