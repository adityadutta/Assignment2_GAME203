#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

#include "Scene.h"

class Window;
class Timer;
class GameManager {
private:
	Window *window;
	Timer *timer;
	bool isRunning;
	Scene *currentScene;


public:
	GameManager();
	~GameManager();
	bool onCreate();
	void onDestroy();

	void Run();
};
#endif


