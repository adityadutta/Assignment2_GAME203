#ifndef Action02_H
#define Action02_H
#include "Action.h"
#include <memory>
#include "Enemy.h"


using namespace MATH;

class Action02 : public Action {

public:

	Action02();
	~Action02();;

	// does the action
	void doAction(Enemy &enemy, Player &player1);

	// undo the action
	void unDoAction(Enemy &enemy, Player &player1);



};
#endif

