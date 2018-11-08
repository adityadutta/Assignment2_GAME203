#ifndef Action01_H
#define Action01_H
#include "Action.h"
#include <memory>
#include "Enemy.h"


using namespace MATH;

class Action01 : public Action {

	public:	

		Action01();
		~Action01();;	
		
		// does the action
		void doAction(Enemy &enemy, Player &player1);

		// undo the action
		void unDoAction(Enemy &enemy, Player &player1);



	};
#endif

