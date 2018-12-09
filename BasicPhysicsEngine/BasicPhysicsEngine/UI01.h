#ifndef UI01_H
#define UI01_H

#include "UI.h"

class UI01 : public UI {
private:
	//player stats, to manipulated by player object in future
	//score stuff
	int coins;
	int score;

	//UI labels
	UILabel* clock;
	UILabel* playerCoins;
	UILabel* playerScore;

public:
	UI01();
	bool onCreate();
	void onDestroy();
	void update(const float time);
	void render(MATH::Matrix4 _projectionMatrix, SDL_Surface * _screenSurface);
	void handleEvents(const SDL_Event &_event);
	void AddElement(UIElement* element);
	void AddLabel(UILabel* label);

	void SetCoins(int _coins);
	void SetScore(int _score);
};

#endif

