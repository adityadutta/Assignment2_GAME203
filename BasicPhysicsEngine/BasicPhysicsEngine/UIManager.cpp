#include "UIManager.h"
#include"UI.h"
#include"UIFactory.h"

bool UIManager::onCreate()
{
	if (UIFactory::getInstance()->onCreate() == false) {
		onDestroy();
		return false;
	}

	return true;
}

void UIManager::onDestroy()
{
	if (currentUI) {
		currentUI->onDestroy();
		delete currentUI;
		currentUI = nullptr;
	}

	UIFactory::getInstance()->onDestroy();
}

void UIManager::update(const float time)
{
	if (currentUI)
		currentUI->update(time);
}

void UIManager::render(MATH::Matrix4 _projectionMatrix, SDL_Surface * _screenSurface)
{
	if (currentUI)
		currentUI->render(_projectionMatrix, _screenSurface);
}


void UIManager::handleEvents(const SDL_Event & _event)
{
	UIFactory::getInstance()->swapUI(_event);
	currentUI = UIFactory::getInstance()->loadedUI().get();
	if (currentUI)
		currentUI->handleEvents(_event);
}

UIManager::UIManager()
{
}


UIManager::~UIManager()
{
}
