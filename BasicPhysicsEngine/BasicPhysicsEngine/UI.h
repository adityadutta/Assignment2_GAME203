#ifndef UI_H
#define UI_H
#include<SDL.h>
#include<vector>
#include"MMath.h"
#include<SDL_ttf.h>

class UIElement;
class UILabel;
class UI {
protected:
	std::vector<UIElement*> ui_elements;		//list of elements of the UI
	std::vector<UILabel*> ui_labels;			//list of labels of the UI

	TTF_Font *font;								//font object
	std::string fontName;						//font name for the UI
public:
	virtual bool onCreate() = 0;																			//creates the UI elements and labels
	virtual void onDestroy() = 0;																			//cleaner method to destroy and free memory
	virtual void update(const float time) = 0;																//updates the UI with the given timeStep
	virtual void render(MATH::Matrix4 _projectionMatrix, SDL_Surface * _screenSurface) = 0;					//renders the UI elements and labels
	virtual void handleEvents(const SDL_Event &_event) = 0;													//handles key and mouse inputs in the UI

	virtual void AddElement(UIElement* element) = 0;														//helper method to add UI elements to vecor list
	virtual void AddLabel(UILabel* label) = 0;																//helper method to add UI labels to vector list
};

#endif
