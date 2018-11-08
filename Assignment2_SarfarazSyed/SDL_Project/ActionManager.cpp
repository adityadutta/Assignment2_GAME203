#include "ActionManager.h"



ActionManager::ActionManager()
{


}


std::shared_ptr<Action> ActionManager::buildAction(int checkAction) {

	// building the ui
	returnAction = factory->LoadAction(checkAction);
	// returing the ui
	return returnAction;

}

void ActionManager::OnDestroy() {
	factory = nullptr;
}

ActionManager::~ActionManager()
{
}
