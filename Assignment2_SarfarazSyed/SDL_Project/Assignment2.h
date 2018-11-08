#ifndef Assignment3_H
#define Assignment3_H
#include <SDL_image.h>
#include "MMath.h"
#include "Scene.h"
#include "ActionFactory.h"
#include "Action.h"
#include <cmath>
#include <SDL.h>
#include "Collider.h"
#include <memory>
#include <vector>
#include "ActionManager.h"
#include "Enemy.h"
#include <SDL_ttf.h>
#include "Player.h"
#include <stack>

using namespace MATH;
class Assignment2 : public Scene {
private:

	SDL_Window *window;
	Matrix4 projectionMatrix;
	float elapsedTime;
	unsigned long frameCount;
	SDL_Renderer* Renderer;
	TTF_Font* font;

public:

	int checkAttack;
	void CheckKey(int chechUI_);	
	std::shared_ptr<ActionManager> returnAction;
	std::shared_ptr<Enemy> enemy;
	std::shared_ptr<Player> player;
	std::shared_ptr<Action> currentAction;
	Assignment2(SDL_Window* sdlWindow);
	std::stack<std::shared_ptr<Action>> Actions;
	~Assignment2(); 
	bool OnCreate();
	void OnDestroy();
	void Update(const float time, int checkScence);
	void Render();
	bool closeWindow;

};

#endif

