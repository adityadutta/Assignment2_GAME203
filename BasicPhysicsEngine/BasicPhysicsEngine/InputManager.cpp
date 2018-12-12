#include "InputManager.h"



InputManager::InputManager() {}

InputManager::~InputManager() {}

void InputManager::HandleEvents(const SDL_Event &_event, Body* player, bool isGround_, std::shared_ptr<Animation> anims) {

	const Uint8 *state = SDL_GetKeyboardState(NULL);

	if (state[SDL_SCANCODE_RIGHT] || state[SDL_SCANCODE_D]) {
		player->linearVelocity += (VECTOR3_RIGHT * 100.0f);
		if (isGround_) {
			anims->setAnim(*player, States::WALKING);
			CheckFliped = true;
		}
		if (!isGround_) {
			anims->setAnim(*player, States::JUMPING);
		}
	}
	else if (state[SDL_SCANCODE_LEFT] || state[SDL_SCANCODE_A]) {
		player->linearVelocity += (VECTOR3_LEFT * 100.0f);
		if (isGround_) {
			anims->setAnimFliped(*player, States::WALKING);
			CheckFliped = false;
		}
		if (!isGround_) {
			anims->setAnimFliped(*player, States::JUMPING);
		}
	}
	else if (state[SDL_SCANCODE_SPACE]) {
		if (isGround_) {
			player->ApplyForceToCentre(VECTOR3_UP * 20000.0f);
			if (CheckFliped == true) {
				anims->setAnim(*player, States::JUMPING);
			}
			if (CheckFliped == false) {
				anims->setAnimFliped(*player, States::JUMPING);
			}
			player->isGrounded = false;
		}
	}
	else if (state[SDL_SCANCODE_LCTRL]) {
		player->Shoot();
	}
	else {
		player->linearVelocity.x = 0.0f;
	}
}