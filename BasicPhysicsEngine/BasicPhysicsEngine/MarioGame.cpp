#include "MarioGame.h"
#include"Body.h"
#include<iostream>
#include"MMath.h"
#include"Collider.h"
#include <algorithm>  
#include <ctime>    // For time()
#include <cstdlib>  // For srand() and rand()

using namespace A3Engine;

void MarioGame::clampVelocity()
{
	float maxSpeed = 10.0f;
	float lSpeed = -maxSpeed;
	if (player->linearVelocity.x > maxSpeed)
		player->linearVelocity.x = maxSpeed;
	if (player->linearVelocity.x < lSpeed)
		player->linearVelocity.x = lSpeed;
}

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

	float aspectRatio = (float)w / (float)h;
	projectionMatrix = MMath::viewportNDC(w, h) * MMath::orthographic(-30.0f, 30.0f, -30.0f * aspectRatio, 30.0f * aspectRatio, 0.0f, 1.0f);

	IMG_Init(IMG_INIT_PNG);

	//initializing the player
	player = new Body("MarioSmallIdle.png", 10.0f, Vec3(0.0f, -15.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f));
	player->addCollider(10.0f, 15.0f);

	//initializing the player
	collector = new Body("MarioLevel.png", 100.0f, Vec3(-20.0f, -30.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f));
	collector->addCollider(300.0f, 12.0f);
	return true;
}

void MarioGame::OnDestroy() {

	IMG_Quit();

	if (player) {
		delete player;
		player = nullptr;
	}
	if (collector) {
		delete collector;
		collector = nullptr;
	}
	SDL_DestroyRenderer(renderer);
}

bool isGrounded = false;
void MarioGame::Update(const float time) {
	elapsedTime += time;

	if (Collider::checkCollision(player->collider, collector->collider)) {
		isGrounded = true;
		player->position.y += 1.0f;
	}
	else {
		isGrounded = false;

	}

	if (!isGrounded) {
		player->acceleration.y += -9.81f;
	}

	//check borders on the x axis for the player
	if (player->position.x > 28.0f || player->position.x < -30.0f) {
		player->linearVelocity.x = -player->linearVelocity.x;
	}

	clampVelocity();

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

	Vec3 collectorCoords = projectionMatrix * collector->position;

	groundRect.h = collector->getImage()->h;
	groundRect.w = collector->getImage()->w;
	groundRect.x = collectorCoords.x; /// implicit type conversions BAD - probably causes a compiler warning
	groundRect.y = collectorCoords.y; /// implicit type conversions BAD - probably causes a compiler warning
	SDL_BlitSurface(collector->getImage(), nullptr, screenSurface, &groundRect);

	SDL_UpdateWindowSurface(window);
}

void MarioGame::HandleEvents(const SDL_Event &_event) {

	if (_event.type == SDL_KEYDOWN)
	{
		switch (_event.key.keysym.sym)
		{
		case SDLK_d:
			//player->linearVelocity += VECTOR3_RIGHT * 100.0f * 0.016;
			player->ApplyForceToCentre(VECTOR3_RIGHT * 2000);
			break;
		case SDLK_a:
			//player->linearVelocity += (VECTOR3_LEFT * 10.0f);
			player->ApplyForceToCentre(VECTOR3_LEFT * 2000);
			break;
		case SDLK_SPACE:
			if (isGrounded) {
				player->ApplyForceToCentre(VECTOR3_UP * 8000);
			}
			break;
		default:
			break;
		}
	}
}

void MarioGame::AddBody(Body* body)
{
	bodies.push_back(body);
}