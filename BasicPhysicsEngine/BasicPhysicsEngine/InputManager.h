#ifndef INPUTMANAGER_H
#define INPUTMANAGER_H

#include "Body.h"
#include <SDL.h>
#include <SDL_keycode.h>
#include <SDL_keyboard.h>
#include "Animation.h"
#include <memory>

class InputManager
{
public:
	InputManager();
	~InputManager();

	void HandleEvents(const SDL_Event &_event, Body*player, bool isGround_, std::shared_ptr<Animation> anims);
	bool CheckFliped;
	float shootTimer;
	void SetTimer(float time_);

};

#endif

