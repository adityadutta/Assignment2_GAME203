#ifndef ActionManager_H
#define ActionManager_H
#include "Action01.h"
#include "ActionFactory.h"
#include <vector>

class ActionManager
{
public:

	ActionManager();
	~ActionManager();
	std::shared_ptr<Action> buildAction(int checkui);
	std::shared_ptr<ActionFactory> factory;
	std::shared_ptr<Action> returnAction;
	void OnDestroy();


};
#endif
