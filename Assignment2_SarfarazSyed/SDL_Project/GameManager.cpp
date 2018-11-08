#include "GameManager.h"
#include "Window.h"
#include "Timer.h"
#include "Assignment3.h"
#include <iostream>

GameManager::GameManager() {
	timer = nullptr;
	isRunning = true;
	currentScene = nullptr;
	checkScence = 0;

}

/// In this OnCreate() method, fuction, subroutine, whatever the word, 
bool GameManager::OnCreate() {
	const int SCREEN_WIDTH = 1280;
	const int SCREEN_HEIGHT = 720;
	ptr = new Window(SCREEN_WIDTH, SCREEN_HEIGHT);
	if (ptr == nullptr) {
		OnDestroy();
		return false;
	}
	if (ptr->OnCreate() == false) {
		OnDestroy();
		return false;
	}

	timer = new Timer();
	if (timer == nullptr) {
		OnDestroy();
		return false;
	}
	currentScene = new Assignment3(ptr->GetSDL_Window());

	if (currentScene == nullptr) {
		OnDestroy();
		return false;
	}

	if (currentScene->OnCreate() == false) {
		OnDestroy();
		return false;
	}
	return true;
}


/// Here's the whole game
void GameManager::Run() {

	SDL_Event event;

	timer->Start();
	while (isRunning) {
		if (SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT) {
				isRunning = false;
			}
			else if (event.type == SDL_KEYDOWN) {
				switch (event.key.keysym.sym) {
				case SDLK_F1:	
					checkScence = 1;
					currentScene->CheckKey(checkScence);
					break;
				case SDLK_F2:
					checkScence = 2;
					currentScene->CheckKey(checkScence);
					break;
				case SDLK_F3:
					checkScence = 3;
					currentScene->CheckKey(checkScence);
					break;
				case SDLK_F4:
					checkScence = 4;
					currentScene->CheckKey(checkScence);
					break;
				}
			}
		}
		timer->UpdateFrameTicks();	
		currentScene->Update(timer->GetDeltaTime(), checkScence);
		currentScene->Render();	
		checkScence = 0;
		currentScene->CheckKey(checkScence);
		/// Keeep the event loop running at a proper rate
		SDL_Delay(timer->GetSleepTime(60)); ///60 frames per sec
	}
}

int GameManager::returnCheck() {

	return checkScence;
}
	
GameManager::~GameManager() {}

void GameManager::OnDestroy(){
	if (ptr) delete ptr;
	if (timer) delete timer;
	if (currentScene) delete currentScene;
}