#ifndef DYNAMICSCENE_H
#define DYNAMICSCENE_H

#include "MMath.h"
#include "Object.h"
#include "Scene.h"
#include <SDL.h>
#include <map>

using namespace MATH;
using namespace std;

class DynamicScene : public Scene {
private:
	SDL_Window *window;
	Matrix4 projectionMatrix;

	Object Object1;
	Object Object2;
public:
	DynamicScene(SDL_Window* sdlWindow);
	~DynamicScene();
	bool OnCreate();
	void OnDestroy();
	void Update(const float time);
	void Render();
	void HandleEvents(const SDL_Event& event);
	map<string, Object>myMap;
};

#endif

