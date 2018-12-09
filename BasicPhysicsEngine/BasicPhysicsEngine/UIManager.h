#ifndef UIMANAGER_H
#define UIMANAGER_H
#include<SDL.h>
#include<memory>
#include"MMath.h"
#include"UI01.h"

class UI;
class UIManager
{
	UI* currentUI;																	//stores the current UI
public:

	bool onCreate();
	void onDestroy();
	void update(const float time);
	void render(MATH::Matrix4 _projectionMatrix, SDL_Surface *_screenSurface);		//calls the render method of the current UI
																					//<params> projectionMatrix - projection matrix created in the scene
																					//			screenSurface - surface which renders the UI

	void handleEvents(const SDL_Event &_event);										//calls the swapUI method of the UIFactory to swap UIs by passing the SDL_Event

	inline UI01* getCurrentUI() {
		return dynamic_cast<UI01*>(currentUI);
	}

	UIManager();
	~UIManager();
};

#endif //!UIMANAGER_H

