#include "UIFactory.h"
#include"UI01.h"

static UIFactory* instance = 0;
UIFactory *UIFactory::getInstance()
{
	if (instance == nullptr) {
		instance = new UIFactory();

	}
	return instance;
}
bool UIFactory::onCreate()
{

	currentUI = std::shared_ptr<UI01>(new UI01());
	if (currentUI == nullptr) {
		onDestroy();
		return false;
	}

	if (currentUI->onCreate() == false) {
		onDestroy();
		return false;
	}

	return true;
}

void UIFactory::onDestroy()
{
	currentUI = nullptr;
}


void UIFactory::swapUI(const SDL_Event & _event)
{
	if (_event.type == SDL_KEYDOWN)
	{
		switch (_event.key.keysym.sym)
		{
		case SDLK_1:
			//	Bar*	bar	=	dynamic_cast<Bar*>(base);
			//UI ui1 = dynamic_cast<UI>(currentUI);
			currentUI->onDestroy();
			currentUI = nullptr;
			currentUI = std::shared_ptr<UI01>(new UI01());
			if (currentUI == nullptr) {
				onDestroy();
			}

			if (currentUI->onCreate() == false) {
				onDestroy();
			}
			break;
		default:
			break;
		}
	}
}

std::shared_ptr<UI> UIFactory::loadedUI()
{
	return currentUI;
}

UIFactory::UIFactory()
{
}


UIFactory::~UIFactory()
{
}

