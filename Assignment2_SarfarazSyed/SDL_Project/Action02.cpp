#include "Action02.h"


Action02::Action02() {

}


// Do action
void Action02::doAction(Enemy &enemy, Player &player1) {

	float tempMana;
	float tempMana1;
	// get manga
	tempMana = enemy.GetMana();
	tempMana1 = player1.GetMana();
	// steel mana;
	tempMana -= 10;
	tempMana1 += 10;
	// Set mana
	enemy.setMana(tempMana);
	player1.setMana(tempMana1);
}


void Action02::unDoAction(Enemy &enemy, Player &player1) {

	float tempMana;
	float tempMana1;
	// get manga
	tempMana = enemy.GetMana();
	tempMana1 = player1.GetMana();
	// steel mana;
	tempMana += 10;
	tempMana1 -= 10;
	// Set mana
	enemy.setMana(tempMana);
	player1.setMana(tempMana1);
}

Action02::~Action02()
{
}
