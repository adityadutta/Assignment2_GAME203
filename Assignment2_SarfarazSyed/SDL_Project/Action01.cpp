#include "Action01.h"


Action01::Action01() {

}


// Do action
void Action01::doAction(Enemy &enemy, Player &player1) {

	float tempHealth;
	// get Health
	tempHealth = enemy.GetHealth();
	// attack Enemy;
	tempHealth -= 10;
	// Set new Health
	enemy.setHealth(tempHealth);
}


void Action01::unDoAction(Enemy &enemy, Player &player1) {

	float tempHealth;
	// Get Health
	tempHealth = enemy.GetHealth();
	// add health
	tempHealth += 10;
	// set the new health
	enemy.setHealth(tempHealth);

}


Action01::~Action01()
{
}
