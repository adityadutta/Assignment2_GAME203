#include "InputManager.h"



InputManager::InputManager() {}

InputManager::~InputManager() {}

void InputManager::HandleEvents(const SDL_Event &_event, Body* player, bool isGround_, std::shared_ptr<Animation> anims) {

	const Uint8 *state = SDL_GetKeyboardState(NULL);

	if (state[SDL_SCANCODE_RIGHT] || state[SDL_SCANCODE_D]) {
		/*player->ApplyForceToCentre(VECTOR3_LEFT * 0);
		player->ApplyForceToCentre(VECTOR3_RIGHT * 1000);*/
		player->linearVelocity += (VECTOR3_RIGHT);
		if (isGround_) {
			anims->setAnim(*player, States::WALKING);
		}
	}
	else if (state[SDL_SCANCODE_LEFT] || state[SDL_SCANCODE_A]) {
		player->ApplyForceToCentre(VECTOR3_RIGHT * 0);
		player->ApplyForceToCentre(VECTOR3_LEFT * 1000);
		if (isGround_) {
			anims->setAnimFliped(*player, States::WALKING);
		}
	}
	else if (state[SDL_SCANCODE_SPACE]) {
		//player->ApplyForceToCentre(VECTOR3_UP * 3000);
		if (isGround_) {
			printf("ground");
			player->ApplyForceToCentre(VECTOR3_UP * 2000.0f);
			anims->setAnim(*player, States::JUMPING);
		}
	}
}