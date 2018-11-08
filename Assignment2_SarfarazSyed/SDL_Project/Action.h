#ifndef Action_H
#define Action_H
#include <vector>
#include "MMath.h"
#include "Enemy.h"
#include "Player.h"

class Action {
public:


	virtual void doAction(Enemy &enemy, Player &player1) = 0;
	virtual void unDoAction(Enemy &enemy, Player &player1) = 0;

};

#endif
