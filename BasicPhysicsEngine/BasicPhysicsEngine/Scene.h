#ifndef SCENE_H
#define SCENE_H

#include<vector>
#include <SDL.h>
#include<SDL_image.h>
#include <memory>

#include "MMath.h"
#include"Vector.h"
#include "InputManager.h"
#include "Animation.h"
#include"UIManager.h"

class Scene {
protected:
	SDL_Window *window = 0;
	Matrix4 projectionMatrix = 0;

	SDL_Renderer* renderer = 0;
public:
	virtual bool OnCreate() = 0;
	virtual void OnDestroy() = 0;
	virtual void Update(const float time) = 0;
	virtual void Render() = 0;
	virtual void HandleEvents(const SDL_Event &_event) = 0;
};

#endif
