#ifndef MARIOGAME_H
#define MARIOGAME_H

#include "Scene.h"

#include "json.hpp"
#include <fstream>

using json = nlohmann::json;

class Body;
using namespace MATH;
class MarioGame : public Scene {
private:
	Body* player;
	Body* ground;
	std::vector<Body*> platforms;
	std::vector<Body*> coins;
	std::vector<Body*> enemies;

	float elapsedTime;
	bool isRunning;

	SDL_Surface* background;

	SDL_Rect playerRectangle;
	SDL_Rect backgroundRectangle;
	SDL_Rect groundRect;
	SDL_Rect coinRect;
	SDL_Rect enemyRect;

	SDL_Rect cameraRect;
	float cameraScrollSpeed;


	std::shared_ptr<Animation> anims;
	std::unique_ptr<InputManager> HandleControls;
	std::unique_ptr<UIManager> manager; //object UIManager 

	//player stuff
	int playerCoins;
	int playerScore;

	void AddToList(std::vector<Body*> &list, Body* body);
	void drawColliders(SDL_Rect _rect, Vec3 _color);

public:
	MarioGame(SDL_Window* sdlWindow);
	bool OnCreate();
	void Load();
	void OnDestroy();
	void Update(const float time);
	void Render();
	void HandleEvents(const SDL_Event &_event);	
};

#endif //!MARIOGAME_H

