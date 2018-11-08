#ifndef Enemy_H
#define Enemy_H
#include <SDL_ttf.h>
#include <string>

class Enemy
{
public:
	void render(SDL_Renderer* Renderer, TTF_Font* font);

	Enemy();
	~Enemy();
	int health;
	int mana;
	void setHealth(float health_);
	float GetHealth();

	void setMana(float mana_);
	float GetMana();
	
};
#endif
