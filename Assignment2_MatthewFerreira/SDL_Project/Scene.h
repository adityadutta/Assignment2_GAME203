#ifndef SCENE_H
#define SCENE_H
#include "UIFactory.h"

class Scene {
public:
	UIFactory *ui;
	virtual bool OnCreate() = 0;
	virtual void OnDestroy() = 0;
	virtual void Update(const float time) = 0;
	virtual void Render() = 0;
	virtual void HandleEvents(const SDL_Event& event) = 0;
};

#endif
