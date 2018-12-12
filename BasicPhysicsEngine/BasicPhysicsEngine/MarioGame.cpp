#include<iostream>
#include <algorithm>  
#include <ctime>    // For time()
#include <cstdlib>  // For srand() and rand()

#include "MarioGame.h"
#include"Body.h"
#include"Collider.h"

using namespace A3Engine;

MarioGame::MarioGame(SDL_Window* sdlWindow_) {

	isRunning = false;
	window = sdlWindow_;
	elapsedTime = 0.0f;
}

bool MarioGame::OnCreate() {

	int w, h;
	SDL_GetWindowSize(window, &w, &h);
	background = IMG_Load("Sprites/background.png");
	renderer = SDL_CreateRenderer(window, -1, 0);

	if (background == nullptr) {
		return false;
	}

	cameraRect = { 0, 0, w, h };

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
	projectionMatrix = MMath::viewportNDC(w, h) * MMath::orthographic(0.0f, 780.0f, 0.0f, 400.0f, 0.0f, 1.0f);

	IMG_Init(IMG_INIT_PNG);

	//initializing the player
	player = new Body("Sprites/Mario/MarioBigIdle.png", 10.0f, Vec3(10.0f, 150.0f, 0.0f), VECTOR3_ZERO, VECTOR3_ZERO);\
	// Read from a file
	MarioGame::Load();

	for (auto platform : platforms) {
		if (platform == nullptr) {
			return false;
		}
	}

	for (auto coin : coins) {
		if (coin == nullptr) {
			return false;
		}

	}

	for (auto enemy : enemies) {
		if (enemy == nullptr) {
			return false;
		}
		else {
			enemy->linearVelocity.Set(VECTOR3_LEFT);
		}
	}

	//player stuff
	playerCoins = 0;
	playerScore = 0;


	return true;

}

void MarioGame::OnDestroy() {

	IMG_Quit();

	if (player) {
		delete player;
		player = nullptr;
	}

	if (victoryBox) {
		victoryBox = nullptr;
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

	if (player == nullptr) {
		return;
	}

	elapsedTime += time;
	manager->update(elapsedTime);
	HandleControls->SetTimer(time);

	if (Collider::checkCollision(player->collider, victoryBox->collider)) {
		std::cout << "You win";
		manager->getCurrentUI()->Victory();
		if (player) {
			delete player;
			player = nullptr;
			return;
		}
	}

	for (auto platform : platforms) {
		if (!player->isGrounded) {
			if (Vec3::Distance(player->position, platform->position) < 31.0f) {
				if (Collider::checkCollision(player->collider, platform->collider)) {					
					player->isGrounded = true;
					player->linearVelocity.y = 0.0f;
				}
			}

		}	
	}
	//check collision of player with coins
	for (int i = 0; i < coins.size(); i++) {
		if (Collider::checkCollision(player->collider, coins[i]->collider)) {
			std::cout << playerCoins << "\n";
			auto it = std::find(coins.begin(), coins.end(), coins[i]);
			if (it != coins.end()) {
				coins.erase(it);
				++playerCoins;
				playerScore += 50;
				manager->getCurrentUI()->SetCoins(playerCoins);
				manager->getCurrentUI()->SetScore(playerScore);
			}
		}
	}

	//check collision of player with enemies
	for (int i = 0; i < enemies.size(); i++) {
		if (Collider::checkCollision(player->collider, enemies[i]->collider)) {
			std::cout << "You died";
			manager->getCurrentUI()->GameOver();
			if (player) {
				delete player;
				player = nullptr;
				return;
			}
		}
	}

	//check collision of fireballs with enemies and walls
	for (int i = 0; i < enemies.size(); i++) {
		for (int j = 0; j < player->projectiles.size(); j++) {
			if (enemies[i] != nullptr) {
				if (Collider::checkCollision(enemies[i]->collider, player->projectiles[j]->collider)) {
					auto it = std::find(enemies.begin(), enemies.end(), enemies[i]);
					if (it != enemies.end()) {
						enemies.erase(it);
						std::cout << "Goomba died!";
						playerScore += 100;
						manager->getCurrentUI()->SetScore(playerScore);
					}

					it = std::find(player->projectiles.begin(), player->projectiles.end(), player->projectiles[j]);
					if (it != player->projectiles.end()) {
						player->projectiles.erase(it);
					}
				}
			}
		}
	}

	for (int i = 0; i < platforms.size(); i++) {
		for (int j = 0; j < player->projectiles.size(); j++) {
			if (Collider::checkCollision(platforms[i]->collider, player->projectiles[j]->collider)) {
				auto it = std::find(player->projectiles.begin(), player->projectiles.end(), player->projectiles[j]);
				if (it != player->projectiles.end()) {
					player->projectiles.erase(it);
				}
			}
		}
	}

	for (int i = 0; i < enemies.size(); i++) {
		for (int j = 0; j < platforms.size(); j++) {
			if (Collider::checkCollision(enemies[i]->collider, platforms[j]->collider)) {
				enemies[i]->isGrounded = true;
				enemies[i]->linearVelocity.y = 0.0f;
			}
			if (!enemies[i]->isGrounded) {
				enemies[i]->acceleration.y += -10.0f;
			}
			if (enemies[i]) enemies[i]->update(time);
		}
	}

	player->linearVelocity.x = MATH::clamp(player->linearVelocity.x, -100.0f, 100.0f);

	Vec3 Realplayer = projectionMatrix * player->position;

	cameraRect.x = Realplayer.x - 390;
	if (cameraRect.x < 0) {
		cameraRect.x = 0;
	}
	if (cameraRect.y > cameraRect.h) {
		cameraRect.y = cameraRect.h;
	}

	if (player->position.y < platforms[0]->position.y - 20.0f) {
		manager->getCurrentUI()->GameOver();
		if (player) {
			delete player;
			player = nullptr;
			return;
		}
	}

	if (!player->isGrounded) {
		player->acceleration.y += -30.0f;
	}

	//update player
	if (player) {
		player->update(time);
		if (player->projectiles.size() > 0) {
			for (auto fb : player->projectiles) {
				fb->update(time);
			}
		}
	}
}

void MarioGame::Render() {

	SDL_Surface *screenSurface = SDL_GetWindowSurface(window);
	SDL_FillRect(screenSurface, nullptr, SDL_MapRGB(screenSurface->format, 0x00, 0x00, 0x00));

	backgroundRectangle.h = background->h;
	backgroundRectangle.w = background->w;
	backgroundRectangle.x = 0.0f; /// implicit type conversions BAD - probably causes a compiler warning
	backgroundRectangle.y = 0.0f; /// implicit type conversions BAD - probably causes a compiler warning
	SDL_BlitSurface(background, nullptr, screenSurface, &backgroundRectangle);

	if (player != nullptr) {
		Vec3 playerCoords = projectionMatrix * player->position;

		playerRectangle.h = player->getImage()->h;
		playerRectangle.w = player->getImage()->w;
		playerRectangle.x = playerCoords.x - cameraRect.x; /// implicit type conversions BAD - probably causes a compiler warning
		playerRectangle.y = playerCoords.y; /// implicit type conversions BAD - probably causes a compiler warning
		SDL_BlitSurface(player->getImage(), nullptr, screenSurface, &playerRectangle);

		for (auto fb : player->projectiles) {
			Vec3 fbCoords = projectionMatrix * fb->position;

			playerRectangle.h = fb->getImage()->h;
			playerRectangle.w = fb->getImage()->w;
			playerRectangle.x = fbCoords.x - cameraRect.x; /// implicit type conversions BAD - probably causes a compiler warning
			playerRectangle.y = fbCoords.y; /// implicit type conversions BAD - probably causes a compiler warning
			SDL_BlitSurface(fb->getImage(), nullptr, screenSurface, &playerRectangle);
		}
	}

	Vec3 victoryCoords = projectionMatrix * victoryBox->position;

	groundRect.h = victoryBox->getImage()->h;
	groundRect.w = victoryBox->getImage()->w;
	groundRect.x = victoryCoords.x - cameraRect.x; /// implicit type conversions BAD - probably causes a compiler warning
	groundRect.y = victoryCoords.y; /// implicit type conversions BAD - probably causes a compiler warning
	SDL_BlitSurface(victoryBox->getImage(), nullptr, screenSurface, &groundRect);

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
	if (player != nullptr) {
		HandleControls->HandleEvents(_event, player, player->isGrounded, anims);
	}
	manager->handleEvents(_event);
}

void MarioGame::Load() {
	//Creates a json variable
	json j;

	//Opening and reading from a json file
	std::ifstream i("Levels/Level3.json");
	i >> j;

	//Iterates through the json data
	for (json::iterator it = j.begin(); it != j.end(); ++it) {
		std::string imageName = j[it.key()]["image"];
		if (j[it.key()]["type"] == "Coin") {
			AddToList(coins, new Body(imageName, 1.0f, Vec3(j[it.key()]["x"], j[it.key()]["y"], 0), VECTOR3_ZERO, VECTOR3_ZERO));
		}
		if (j[it.key()]["type"] == "Enemies") {
			AddToList(enemies, new Body(imageName, 1.0f, Vec3(j[it.key()]["x"], j[it.key()]["y"], 0), VECTOR3_ZERO, VECTOR3_ZERO));
		}
		if (j[it.key()]["type"] == "Terrain") {
			AddToList(platforms, new Body(imageName, 1.0f, Vec3(j[it.key()]["x"], j[it.key()]["y"], 0), VECTOR3_ZERO, VECTOR3_ZERO));
		}
		if (j[it.key()]["type"] == "UsedBlock") {
			AddToList(platforms, new Body(imageName, 1.0f, Vec3(j[it.key()]["x"], j[it.key()]["y"], 0), VECTOR3_ZERO, VECTOR3_ZERO));
		}
		if (j[it.key()]["type"] == "Goal") {
			victoryBox = std::unique_ptr<Body>(new Body(imageName, 1.0f, Vec3(j[it.key()]["x"], j[it.key()]["y"], 0), VECTOR3_ZERO, VECTOR3_ZERO));
			victoryBox->addCollider(2.0f, 2.0f);
		}
	}

	//Closes the file
	i.close();
}

void MarioGame::AddToList(std::vector<Body*> &list, Body * body)
{
	list.push_back(body);
}

void MarioGame::drawColliders(SDL_Rect _rect, Vec3 _color)
{
	SDL_SetRenderDrawColor(renderer, 0x00, 0xFF, 0x00, 0xFF);
	Vec3 screenCoords = projectionMatrix * Vec3(_rect.x, _rect.y, 0.0f);
	groundRect.h = _rect.h;
	groundRect.w = _rect.w;
	groundRect.x = screenCoords.x;
	groundRect.y = screenCoords.y;
	SDL_RenderDrawRect(renderer, &groundRect);
	//Update the Renderer.
	SDL_RenderPresent(renderer);
}
