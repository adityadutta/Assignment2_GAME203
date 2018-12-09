#ifndef UIFACTORY_H
#define UIFACTORY_H
#include<SDL.h>
#include<memory>
#include"UI.h"

class UIFactory
{
private:
	UIFactory();
	~UIFactory();
	std::shared_ptr<UI> currentUI;
public:
	//singleton of the factory
	static UIFactory* getInstance();

	bool onCreate();
	void onDestroy();
	void swapUI(const SDL_Event &_event);		//gets a keyboard input and swaps UI
	std::shared_ptr<UI> loadedUI();				//returns the current loaded UI to the manager
};

#endif //!UIFACTORY_H