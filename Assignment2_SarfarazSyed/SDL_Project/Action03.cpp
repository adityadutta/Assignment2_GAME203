#include "Action03.h"


Action03::Action03() {

}


// Do action
void Action03::doAction(Enemy &enemy, Player &player1) {


	float tempMana1;
	float temphealth;
	float temphealth1;

	// get manga
	tempMana1 = player1.GetMana();

	// get Health
	temphealth = enemy.GetHealth();
	temphealth1 = player1.GetHealth();


	// attack enemy
	temphealth1 -= 10;
	temphealth -= 30;

	// use mana;
	tempMana1 -= 10;

	// Set mana
	enemy.setHealth(temphealth);
	player1.setHealth(temphealth1);
	player1.setMana(tempMana1);
}


void Action03::unDoAction(Enemy &enemy, Player &player1) {

	float tempMana1;
	float temphealth;
	float temphealth1;

	// get manga
	tempMana1 = player1.GetMana();

	// get Health
	temphealth = enemy.GetHealth();
	temphealth1 = player1.GetHealth();


	// attack enemy
	temphealth1 += 10;
	temphealth += 30;

	// use mana;
	tempMana1 += 10;

	// Set mana
	enemy.setHealth(temphealth);
	player1.setHealth(temphealth1);
	player1.setMana(tempMana1);
}

Action03::~Action03()
{
}
