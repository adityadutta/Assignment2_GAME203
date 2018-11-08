#include "Assignment3.h"
#include "Body.h"
#include <SDL.h>
#include "GameManager.h"
#include <time.h>
#include <cstdlib> 
#include <iostream>


Assignment3::Assignment3(SDL_Window* sdlWindow_){
	window = sdlWindow_;
	elapsedTime = 0.0f;
	frameCount = 0L;
	closeWindow = false;

}
Assignment3::~Assignment3(){
}

bool Assignment3::OnCreate() {

	enemy = std::shared_ptr<Enemy>(new Enemy());
	player = std::shared_ptr<Player>(new Player());
	returnAction = std::shared_ptr<ActionManager>(new ActionManager());

	int w, h;
	SDL_Init(SDL_INIT_EVERYTHING);
	TTF_Init();
	Renderer = SDL_CreateRenderer(window, -1, 0);
	SDL_GetWindowSize(window,&w,&h);

	font = TTF_OpenFont("OpenSans-Italic.ttf", 20);
	
	projectionMatrix = MMath::viewportNDC(w, h) * MMath::orthographic(-20.0f, 35.0f, -20.0f, 35.0f, 0.0f, 1.0f);

	std::cout << "press F1 for normal attack" << std::endl;
	std::cout << "press F2 to steal mana" << std::endl;
	std::cout << "press F3 for powerfull attack" << std::endl;
	std::cout << "press F4 to undo";

	if (font == NULL) {
		return false;
		OnDestroy();
	}

	return true;

}

void Assignment3::OnDestroy() {

	TTF_CloseFont(font);
	SDL_DestroyRenderer(Renderer);
	IMG_Quit();
	TTF_Quit();

	currentAction = nullptr;
}

void Assignment3::Update(const float Time, int checkScence) {

	if (checkScence > 0 && checkScence < 4) {
		if (enemy->health > 0 && enemy->mana > 0 && player->health > 0 && player->mana > 0) {

			currentAction = returnAction->buildAction(checkScence);
			currentAction->doAction(*enemy, *player);
			Actions.push(currentAction);
		}	
	}
	else if(checkScence == 4){

		if (Actions.empty() == false) {
			Actions.top()->unDoAction(*enemy, *player);
			Actions.pop();
		}
	
	}

}

 void Assignment3::CheckKey(int checkAttack_)
{
	 checkAttack = checkAttack_;
 }

void Assignment3::Render() {

	SDL_RenderClear(Renderer);
	enemy->render(Renderer, font);
	player->render(Renderer, font);
	SDL_RenderPresent(Renderer);

}