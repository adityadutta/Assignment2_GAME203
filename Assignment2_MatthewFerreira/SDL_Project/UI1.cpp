#include "UI1.h"
#include <SDL.h>
UI1::UI1(SDL_Window* sdlWindow_) {
	window = sdlWindow_;
	healthBarImage = nullptr;
}

UI1::~UI1() {}

bool UI1::OnCreate() {
	int w, h;
	SDL_GetWindowSize(window, &w, &h);
	projectionMatrix = MMath::viewportNDC(w, h) * MMath::orthographic(0.0f, 14.0f, 0.0f, 7.0f, 0.0f, 1.0f);
	// Load and position the image
	healthBarImage = SDL_LoadBMP("healthbarRPG.bmp");
	if (healthBarImage == nullptr) {
		return false;
	}
	healthBarPos.Load(-0.5, 7.5f, 0.0f);
	return true;
}

void UI1::OnDestroy() {}

void UI1::Update(const float time) {}

void UI1::Render(SDL_Surface *screenSurface) {

	Vec3 screenCoords = projectionMatrix * healthBarPos;

	healthBarRect.h = healthBarImage->h;
	healthBarRect.w = healthBarImage->w;
	healthBarRect.x = screenCoords.x; /// implicit type conversions BAD - probably causes a compiler warning
	healthBarRect.y = screenCoords.y; /// implicit type conversions BAD - probably causes a compiler warning

	SDL_BlitSurface(healthBarImage, nullptr, screenSurface, &healthBarRect);
}
