#include "Enemy.h"
#include <iostream>


Enemy::Enemy()
{
	health = 100;
	mana = 60;
}


void Enemy::setHealth(float health_) {

	health = health_;

}

float Enemy::GetHealth() {

	return health;
}


void Enemy::setMana(float mana_) {

	mana = mana_;

}

float Enemy::GetMana() {

	return mana;
}


void Enemy::render(SDL_Renderer* Renderer, TTF_Font* font) {

	// set the color of the text
	SDL_Color TextColor = { 255, 255, 255 };

	//SDL_RenderClear(Renderer);


	std::string comp =   "Enemy----->>   Health: "+ std::to_string(health) + "    Mana: " + std::to_string(mana);

	// create the surface
	SDL_Surface *surface = TTF_RenderText_Solid(font, comp.c_str(), TextColor);
	// create the texture
	SDL_Texture *texture = SDL_CreateTextureFromSurface(Renderer, surface);

	// the size of the text
	int texW = 0;
	int texH = 0;
	SDL_QueryTexture(texture, NULL, NULL, &texW, &texH);
	SDL_Rect dstrect = {500, 50, texW, texH };

	// draw to screen
	SDL_RenderCopy(Renderer, texture, NULL, &dstrect);

	SDL_DestroyTexture(texture);
	SDL_FreeSurface(surface);
}


Enemy::~Enemy()
{
}
