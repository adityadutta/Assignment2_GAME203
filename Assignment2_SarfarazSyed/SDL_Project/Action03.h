#ifndef Action03_H
#define Action03_H
#include "Action.h"
#include <memory>
#include "Enemy.h"


using namespace MATH;

class Action03 : public Action {

public:

	Action03();
	~Action03();;

	// does the action
	void doAction(Enemy &enemy, Player &player1);

	// undo the action
	void unDoAction(Enemy &enemy, Player &player1);



};
#endif

