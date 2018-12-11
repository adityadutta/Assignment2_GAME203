#ifndef SCENE_H
#define SCENE_H

#include <SDL.h>
#include<SDL_image.h>
#include <memory>
#include<vector>
#include <iostream>

#include "InputManager.h"
#include"Body.h"
#include"MMath.h"
#include"Collider.h"
#include"UIManager.h"

class Scene {
protected:
	SDL_Window *window;
	Matrix4 projectionMatrix;

	SDL_Renderer* renderer;
public:
	virtual bool OnCreate() = 0;
	virtual void OnDestroy() = 0;
	virtual void Update(const float time) = 0;
	virtual void Render() = 0;
	virtual void HandleEvents(const SDL_Event &_event) = 0;
};

#endif
