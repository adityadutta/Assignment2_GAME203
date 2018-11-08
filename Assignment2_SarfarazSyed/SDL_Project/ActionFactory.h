#ifndef ActionFactory_H
#define ActionFactory_H
#include "Action01.h"
#include "Action02.h"
#include "Action03.h"

class GameManager;
class ActionFactory
{
public:

	ActionFactory();
	~ActionFactory();
	std::shared_ptr<Action> LoadAction(int checkAction);

	//std::shared_ptr<Action> currentAction; 
};
#endif
