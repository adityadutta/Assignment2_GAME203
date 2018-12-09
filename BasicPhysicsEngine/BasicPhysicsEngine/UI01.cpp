#include "UI01.h"
#include"UIElement.h"
#include"UILabel.h"
#include"MMath.h"
#include<memory>
#include<string>

using namespace MATH;

UI01::UI01() {
}

bool UI01::onCreate() {
	TTF_Init();
	AddElement(new UIElement("UI1_elements/playerStats.png", Vec3(18.0f, -30.0f, 0.0f)));

	fontName = "Fonts/BebasNeue-Regular";
	font = TTF_OpenFont(fontName.c_str(), 30);
	SDL_Color color = { 255, 255, 255 };

	//timer init
	clock = new UILabel(" ", Vec3(-26.0f, -21.25f, 0.0f), color, 26);
	AddLabel(clock);

	//Ammo stuff init
	currentAmmo = 30;
	maxAmmo = 90;
	ammoStats = new UILabel(" ", Vec3(22.0f, -34.0f, 0.0f), color, 42);
	AddLabel(ammoStats);

	//coins
	AddElement(new UIElement("UI1_elements/coin.png", Vec3(-28.0f, 35.0f, 0.0f)));

	coins = 0;
	playerStats = new UILabel(" ", Vec3(-25.0f, 35.5f, 0.0f), color, 36);
	AddLabel(playerStats);

	AddLabel(new UILabel("FPS User Interface", Vec3(-29.0f, 51.0f, 0.0f), color, 26));

	for (auto label : ui_labels) {
		label->SetFont(fontName);
	}

	for (auto element : ui_elements) {
		if (element = nullptr) {
			onDestroy();
			return false;

		}

	}

	for (auto label : ui_labels) {
		if (label = nullptr) {
			onDestroy();
			return false;

		}

	}

	return true;
}

void UI01::onDestroy() {


	for (auto element : ui_elements) {
		if (element) {
			delete element;
			element = nullptr;
		}
	}

	for (auto label : ui_labels) {
		if (label) {
			delete label;
			label = nullptr;
		}
	}

	TTF_CloseFont(font);

	TTF_Quit();

}

void UI01::update(const float time) {

	//timer stuff
	std::string minutes = std::to_string((int)time / 60);
	std::string seconds = std::to_string((int)time % 60);

	std::string timerText = minutes + ":" + seconds;
	clock->text = timerText;

	//ammo stuff
	std::string ammoText = std::to_string(currentAmmo) + " / " + std::to_string(maxAmmo);
	ammoStats->text = ammoText;

	//health stuff
	std::string coinText = " x " + std::to_string(coins);
	playerStats->text = coinText;
}

void UI01::render(Matrix4 _projectionMatrix, SDL_Surface * _screenSurface) {

	SDL_Rect _imageRectangle;
	for (auto element : ui_elements) {
		Vec3 screenCoords = _projectionMatrix * element->position;

		_imageRectangle.h = element->getImage()->h;
		_imageRectangle.w = element->getImage()->w;
		_imageRectangle.x = screenCoords.x; /// implicit type conversions BAD - probably causes a compiler warning
		_imageRectangle.y = screenCoords.y; /// implicit type conversions BAD - probably causes a compiler warning
		SDL_BlitSurface(element->getImage(), nullptr, _screenSurface, &_imageRectangle);
	}

	SDL_Rect text_pos;
	for (auto label : ui_labels) {
		Vec3 textCoords = _projectionMatrix * label->position;

		TTF_CloseFont(font);
		font = TTF_OpenFont(label->fontName.c_str(), label->fontSize);
		if (font == nullptr) {
			font = TTF_OpenFont("Fonts/BebasNeue-Regular.ttf", label->fontSize);
		}

		text_pos.x = textCoords.x; /// implicit type conversions BAD - probably causes a compiler warning
		text_pos.y = textCoords.y; /// implicit type conversions BAD - probably causes a compiler warning
		SDL_Surface *surface = TTF_RenderText_Solid(font, label->text.c_str(), label->color);

		SDL_BlitSurface(surface, nullptr, _screenSurface, &text_pos);
		SDL_FreeSurface(surface);
	}
}


void UI01::handleEvents(const SDL_Event &_event) {

	
}

void UI01::AddElement(UIElement* element) {
	ui_elements.push_back(element);
}

void UI01::AddLabel(UILabel * label) {
	ui_labels.push_back(label);
}

void UI01::SetCoins(int _coins)
{
	coins = _coins;
}