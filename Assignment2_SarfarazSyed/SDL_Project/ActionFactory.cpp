#include "ActionFactory.h"



ActionFactory::ActionFactory()
{

}

std::shared_ptr<Action> ActionFactory::LoadAction(int checkAction) {

	// checking what action the user is asking
	switch (checkAction) {
	case 1:
		return std::shared_ptr<Action01>(new Action01());
		break;
	case 2:
		return std::shared_ptr<Action02>(new Action02());
		break;
	case 3:
		return std::shared_ptr<Action03>(new Action03());
		break;
	}
}


ActionFactory::~ActionFactory()
{
}
