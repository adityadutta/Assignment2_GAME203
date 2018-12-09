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
	player = new Body("MarioBigIdle.png", 10.0f, Vec3(0.0f, -15.0f, 0.0f), VECTOR3_ZERO, VECTOR3_ZERO);
	player->addCollider(3.0f, 6.0f);

	//initializing the ground
	ground = new Body("MarioLevel.png", 100.0f, Vec3(-20.0f, -30.0f, 0.0f), VECTOR3_ZERO, VECTOR3_ZERO);
	ground->addCollider(300.0f, 6.0f);

	AddToList(platforms, new Body("Sprites/Block.png", 1.0f, Vec3(-10.0f, -30.0f, 0.0f), VECTOR3_ZERO, VECTOR3_ZERO));
	AddToList(platforms, new Body("Sprites/Block.png", 1.0f, Vec3(-15.0f, -30.0f, 0.0f), VECTOR3_ZERO, VECTOR3_ZERO));

	AddToList(platforms, new Body("Sprites/Block.png", 1.0f, Vec3(-20.0f, -30.0f, 0.0f), VECTOR3_ZERO, VECTOR3_ZERO));
	AddToList(platforms, new Body("Sprites/Block.png", 1.0f, Vec3(-25.0f, -30.0f, 0.0f), VECTOR3_ZERO, VECTOR3_ZERO));
	AddToList(platforms, new Body("Sprites/Block.png", 1.0f, Vec3(-30.0f, -30.0f, 0.0f), VECTOR3_ZERO, VECTOR3_ZERO));
	AddToList(platforms, new Body("Sprites/Block.png", 1.0f, Vec3(-40.0f, -30.0f, 0.0f), VECTOR3_ZERO, VECTOR3_ZERO));

	// Read from a file
	//MarioGame::Load();

	AddToList(coins, new Body("Sprites/coin.png", 1.0f, Vec3(16.0f, -15.0f, 0.0f), VECTOR3_ZERO, VECTOR3_ZERO));
	AddToList(coins, new Body("Sprites/coin.png", 1.0f, Vec3(10.0f, -24.0f, 0.0f), VECTOR3_ZERO, VECTOR3_ZERO));
	AddToList(coins, new Body("Sprites/coin.png", 1.0f, Vec3(8.0f, -24.0f, 0.0f), VECTOR3_ZERO, VECTOR3_ZERO));
	AddToList(coins, new Body("Sprites/coin.png", 1.0f, Vec3(12.0f, -24.0f, 0.0f), VECTOR3_ZERO, VECTOR3_ZERO));

	AddToList(enemies, new Body("Sprites/GoombaWalk1.png", 1.0f, Vec3(15.0f, -15.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f)));

	for (auto platform : platforms) {
		if (platform == nullptr) {
			return false;
		}
		else {
			platform->addCollider(16.0f, 16.0f);
		}
	}

	for (auto coin : coins) {
		if (coin == nullptr) {
			return false;
		}
		else {
			coin->addCollider(0.16f, 0.16f);
		}
	}

	for (auto enemy : enemies) {
		if (enemy == nullptr) {
			return false;
		}
		else {
			enemy->addCollider(16.0f, 10.0f);
			enemy->linearVelocity.Set(VECTOR3_LEFT);
		}
	}

	//player stuff
	playerCoins = 0;
	playerScore = 0;


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
		if (j[it.key()]["type"] == "Collectible") {
			AddToList(coins, new Body("Sprites/coin.png", 1.0f, Vec3(j[it.key()]["x"], j[it.key()]["y"], 0), VECTOR3_ZERO, VECTOR3_ZERO));
			std::cout << "I'm here" << std::endl;
		}
		else if (j[it.key()]["type"] == "Enemies") {
			AddToList(enemies, new Body("Sprites/GoombaWalk1.png", 1.0f, Vec3(j[it.key()]["x"], j[it.key()]["y"], 0), VECTOR3_ZERO, VECTOR3_ZERO));
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

	for (auto platform : platforms) {
		if (platform) {
			delete platform;
			platform = nullptr;
		}
	}

	for (auto coin : coins) {
		if (coin) {
			delete coin;
			coin = nullptr;
		}
	}

	for (auto enemy : enemies) {
		if (enemy) {
			delete enemy;
			enemy = nullptr;
		}
	}

}

void MarioGame::Update(const float time) {

	elapsedTime += time;
	manager->update(elapsedTime);

	if (Collider::checkCollision(player->collider, ground->collider)) {
		player->isGrounded = true;
		player->linearVelocity.y = 0.0f;
	}
	else {
		player->isGrounded = false;
	}

	/*for (int i = 0; i < platforms.size(); i++) {
		if (Collider::checkCollision(player->collider, platforms[i]->collider)) {
			player->isGrounded = true;
			player->linearVelocity.y = 0.0f;
		}
		else {
			player->isGrounded = false;
		}
	}*/


	if (!player->isGrounded) {
		player->acceleration.y += -9.81f;
	}

	//check collision of player with coins
	for (int i = 0; i < coins.size(); i++) {
		if (Collider::checkCollision(player->collider, coins[i]->collider)) {		
			std::cout << playerCoins << "\n";
			//Collider::HandleCollision(*player, *coins[i], 1.0f);
			auto it = std::find(coins.begin(), coins.end(), coins[i]);
			if (it != coins.end()) {
				coins.erase(it);
				++playerCoins;
				manager->getCurrentUI()->SetCoins(playerCoins);
			}
		}
	}


	//check collision of player with enemies
	for (int i = 0; i < enemies.size(); i++) {
		if (Collider::checkCollision(player->collider, enemies[i]->collider)) {
			//Collider::HandleCollision(*player, *coins[i], 1.0f);
			auto it = std::find(enemies.begin(), enemies.end(), enemies[i]);
			if (it != enemies.end()) {
				enemies.erase(it);
				std::cout << "Goomba died!";
				playerScore += 100;
				manager->getCurrentUI()->SetScore(playerScore);
			}
		}
	}

	for (int i = 0; i < enemies.size(); i++) {
		if (Collider::checkCollision(enemies[i]->collider, ground->collider)) {
			enemies[i]->isGrounded = true;
			enemies[i]->linearVelocity.y = 0.0f;
		}
		if (!enemies[i]->isGrounded) {
			enemies[i]->acceleration.y += -10.0f;
		}
		if (enemies[i]) enemies[i]->update(time);
	}

	player->linearVelocity.x = MATH::clamp(player->linearVelocity.x, -10.0f, 10.0f);

	//cameraRect.x = player->position.x * cameraScrollSpeed; // multiplying by camera scroll speed.

	Vec3 Realplayer = projectionMatrix * player->position;

	cameraRect.x = Realplayer.x - 320;
	if (cameraRect.x < 0) {
		cameraRect.x = 0;
	}
	if (cameraRect.y > cameraRect.h) {
		cameraRect.y = cameraRect.h;
	}

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

	Vec3 playerCoords = projectionMatrix * player->position ;

	playerRectangle.h = player->getImage()->h;
	playerRectangle.w = player->getImage()->w;
	playerRectangle.x = playerCoords.x - cameraRect.x; /// implicit type conversions BAD - probably causes a compiler warning
	playerRectangle.y = playerCoords.y; /// implicit type conversions BAD - probably causes a compiler warning
	SDL_BlitSurface(player->getImage(), nullptr, screenSurface, &playerRectangle);

	Vec3  groundCoords = projectionMatrix * ground->position;
	groundRect.h = ground->getImage()->h;
	groundRect.w = ground->getImage()->w;
	groundRect.x = groundCoords.x  - cameraRect.x ; /// implicit type conversions BAD - probably causes a compiler warning
	groundRect.y = groundCoords.y; /// implicit type conversions BAD - probably causes a compiler warning
	SDL_BlitSurface(ground->getImage(), nullptr, screenSurface, &groundRect);

	for (auto platform : platforms) {
		Vec3 screenCoords = projectionMatrix * platform->position;

		groundRect.h = platform->getImage()->h;
		groundRect.w = platform->getImage()->w;
		groundRect.x = screenCoords.x - cameraRect.x; /// implicit type conversions BAD - probably causes a compiler warning
		groundRect.y = screenCoords.y; /// implicit type conversions BAD - probably causes a compiler warning
		SDL_BlitSurface(platform->getImage(), nullptr, screenSurface, &groundRect);
	}

	for (auto coin : coins) {
		Vec3 screenCoords = projectionMatrix * coin->position;

		coinRect.h = coin->getImage()->h;
		coinRect.w = coin->getImage()->w;
		coinRect.x = screenCoords.x - cameraRect.x; /// implicit type conversions BAD - probably causes a compiler warning
		coinRect.y = screenCoords.y; /// implicit type conversions BAD - probably causes a compiler warning
		SDL_BlitSurface(coin->getImage(), nullptr, screenSurface, &coinRect);
	}

	for (auto enemy : enemies) {
		Vec3 screenCoords = projectionMatrix * enemy->position;

		enemyRect.h = enemy->getImage()->h;
		enemyRect.w = enemy->getImage()->w;
		enemyRect.x = screenCoords.x - cameraRect.x; /// implicit type conversions BAD - probably causes a compiler warning
		enemyRect.y = screenCoords.y; /// implicit type conversions BAD - probably causes a compiler warning
		SDL_BlitSurface(enemy->getImage(), nullptr, screenSurface, &enemyRect);
	}

	manager->render(projectionMatrix, screenSurface);

	SDL_UpdateWindowSurface(window);
		
}

void MarioGame::HandleEvents(const SDL_Event &_event) {
	HandleControls->HandleEvents(_event, player, player->isGrounded, anims);
	manager->handleEvents(_event);
}


void MarioGame::AddToList(std::vector<Body*> &list, Body * body)
{
	list.push_back(body);
}