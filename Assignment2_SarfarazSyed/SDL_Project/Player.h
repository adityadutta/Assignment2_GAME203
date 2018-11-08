#ifndef Player_H
#define Player_H
#include <SDL_ttf.h>
#include <string>

class Player
{
public:
	void render(SDL_Renderer* Renderer, TTF_Font* font);

	Player();
	~Player();
	int health;
	int mana;
	void setHealth(float health_);
	float GetHealth();

	void setMana(float mana_);
	float GetMana();
	
};
#endif
