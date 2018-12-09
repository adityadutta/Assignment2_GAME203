#include<iostream>
#include <algorithm>  
#include <ctime>    // For time()
#include <cstdlib>  // For srand() and rand()

#include "MarioGame.h"
#include"Body.h"
#include"MMath.h"
#include"Collider.h"
#include"UIManager.h"

using namespace A3Engine;

MarioGame::MarioGame(SDL_Window* sdlWindow_) {

	isRunning = false;
	window = sdlWindow_;
	elapsedTime = 0.0f;
}

bool MarioGame::OnCreate() {

	int w, h;
	SDL_GetWindowSize(window, &w, &h);
	renderer = SDL_CreateRenderer(window, -1, 0);
	background = IMG_Load("background.png");
	if (background == nullptr) {
		return false;
	}

	cameraRect = { 0, 0, w, h };
	cameraScrollSpeed = 20.0f;


	HandleControls = std::unique_ptr<InputManager>(new InputManager());

	anims = std::shared_ptr<Animation>(new Animation());

	manager = std::unique_ptr<UIManager>(new UIManager());
	if (manager == nullptr) {
		OnDestroy();
		return false;
	}

	if (manager->onCreate() == false) {
		OnDestroy();
		return false;
	}

	float aspectRatio = (float)w / (float)h;
	projectionMatrix = MMath::viewportNDC(w, h) * MMath::orthographic(-30.0f, 30.0f, -30.0f * aspectRatio, 30.0f * aspectRatio, 0.0f, 1.0f);

	IMG_Init(IMG_INIT_PNG);

	//initializing the player
	player = new Body("MarioBigIdle.png", 10.0f, Vec3(0.0f, -15.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f));
	player->addCollider(3.0f, 6.0f);

	//initializing the player
	ground = new Body("MarioLevel.png", 100.0f, Vec3(-20.0f, -30.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f));
	ground->addCollider(300.0f, 6.0f);

	// Read from a file
	MarioGame::Load();
	
	AddBody(new Body("Sprites/coin.png", 1.0f, Vec3(16.0f, -15.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f)));
	AddBody(new Body("Sprites/coin.png", 1.0f, Vec3(10.0f, -24.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f)));
	AddBody(new Body("Sprites/coin.png", 1.0f, Vec3(8.0f, -24.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f)));
	AddBody(new Body("Sprites/coin.png", 1.0f, Vec3(12.0f, -24.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f)));
	
	for (auto coin : coins) {
		if (coin == nullptr) {
			return false;
		}
		else {
			coin->addCollider(0.16f, 0.16f);
		}
	}

	//player stuff
	playerCoins = 0;

	return true;

}

void MarioGame::Load() {
	//Creates a json variable
	json j;

	//Opening and reading from a json file
	std::ifstream i("savedata.json");
	i >> j;

	//Iterates through the json data
	for (json::iterator it = j.begin(); it != j.end(); ++it) {
		std::cout << j[it.key()] << std::endl;
		if (j[it.key()]["type"] == "Terrain") {
			/*std::string image = j[it.key()]["image"];
			std::string * image1 = &image;
			const char * imchar = image1->c_str();*/
			AddBody(new Body("Sprites/coin.png", 1.0f, Vec3(j[it.key()]["x"], j[it.key()]["y"], 0), Vec3(0, 0, 0), Vec3(0, 0, 0)));
			std::cout << "I'm here" << std::endl;
		}
		else if (j[it.key()]["type"] == "Enemies") {
			//myOBJs["Enemies"].push_back(new Button(j[it.key()]["image"], Vec3(j[it.key()]["x"], j[it.key()]["y"], 0)));
		}
	}

	//Closes the file
	i.close();
}

void MarioGame::OnDestroy() {

	IMG_Quit();

	if (player) {
		delete player;
		player = nullptr;
	}
	if (ground) {
		delete ground;
		ground = nullptr;
	}

	for (auto coin : coins) {
		if (coin) {
			delete coin;
			coin = nullptr;
		}
	}

	SDL_DestroyRenderer(renderer);
}

void MarioGame::Update(const float time) {

	elapsedTime += time;
	manager->update(elapsedTime);

	if (Collider::checkCollision(player->collider, ground->collider)) {
		isGrounded = true;
		player->linearVelocity.y = 0.0f;
	}
	else {
		isGrounded = false;
	}

	if (!isGrounded) {
		player->acceleration.y += -9.81f;
	}

	//check collision of player with balls
	for (int i = 0; i < coins.size(); i++) {
		if (Collider::checkCollision(player->collider, coins[i]->collider)) {
			++playerCoins;
			std::cout<< playerCoins << "\n";
			//Collider::HandleCollision(*player, *coins[i], 1.0f);
			auto it = std::find(coins.begin(), coins.end(), coins[i]);
			if (it != coins.end()) {
				coins.erase(it);
			}
			manager->getCurrentUI()->SetCoins(playerCoins);
		}
	}

	player->linearVelocity.x = MATH::clamp(player->linearVelocity.x, -10.0f, 10.0f);

	cameraRect.x = player->position.x * cameraScrollSpeed; // multiplying by camera scroll speed.

	//update player
	if (player) player->update(time);
}

void MarioGame::Render() {

	SDL_Surface *screenSurface = SDL_GetWindowSurface(window);
	SDL_FillRect(screenSurface, nullptr, SDL_MapRGB(screenSurface->format, 0x00, 0x00, 0x00));

	backgroundRectangle.h = background->h;
	backgroundRectangle.w = background->w;
	backgroundRectangle.x = 0.0f; /// implicit type conversions BAD - probably causes a compiler warning
	backgroundRectangle.y = 0.0f; /// implicit type conversions BAD - probably causes a compiler warning
	SDL_BlitSurface(background, nullptr, screenSurface, &backgroundRectangle);

	Vec3 playerCoords = projectionMatrix * player->position;

	playerRectangle.h = player->getImage()->h;
	playerRectangle.w = player->getImage()->w;
	playerRectangle.x = playerCoords.x; /// implicit type conversions BAD - probably causes a compiler warning
	playerRectangle.y = playerCoords.y; /// implicit type conversions BAD - probably causes a compiler warning
	SDL_BlitSurface(player->getImage(), nullptr, screenSurface, &playerRectangle);

	for (auto coin : coins) {
		Vec3 screenCoords = projectionMatrix * coin->position;

		coinRect.h = coin->getImage()->h;
		coinRect.w = coin->getImage()->w;
		coinRect.x = screenCoords.x; /// implicit type conversions BAD - probably causes a compiler warning
		coinRect.y = screenCoords.y; /// implicit type conversions BAD - probably causes a compiler warning
		SDL_BlitSurface(coin->getImage(), nullptr, screenSurface, &coinRect);
	}

	Vec3 collectorCoords = projectionMatrix * ground->position;
	groundRect.h = ground->getImage()->h;
	groundRect.w = ground->getImage()->w;
	groundRect.x = collectorCoords.x; /// implicit type conversions BAD - probably causes a compiler warning
	groundRect.y = collectorCoords.y; /// implicit type conversions BAD - probably causes a compiler warning
	SDL_BlitSurface(ground->getImage(), &cameraRect, screenSurface, &groundRect);

	manager->render(projectionMatrix, screenSurface);

	SDL_UpdateWindowSurface(window);
}

void MarioGame::HandleEvents(const SDL_Event &_event) {
	HandleControls->HandleEvents(_event, player, isGrounded, anims);
	manager->handleEvents(_event);
}



void MarioGame::AddBody(Body* body)
{
	coins.push_back(body);
}