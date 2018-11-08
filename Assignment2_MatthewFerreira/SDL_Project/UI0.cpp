#include "UI0.h"
#include <SDL.h>
UI0::UI0(SDL_Window* sdlWindow_) {
	window = sdlWindow_;
	healthBar1Image = nullptr;
	healthBar2Image = nullptr;
}

UI0::~UI0() {}

bool UI0::OnCreate() {
	int w, h;
	SDL_GetWindowSize(window, &w, &h);
	projectionMatrix = MMath::viewportNDC(w, h) * MMath::orthographic(0.0f, 14.0f, 0.0f, 7.0f, 0.0f, 1.0f);
	// Load and the position the images
	healthBar1Image = SDL_LoadBMP("healthbarFG1.bmp");
	if (healthBar1Image == nullptr) {
		return false;
	}	
	healthBar1Pos.Load(0.0f, 6.5f, 0.0f);
	healthBar2Image = SDL_LoadBMP("healthbarFG2.bmp");
	if (healthBar2Image == nullptr) {
		return false;
	}
	healthBar2Pos.Load(9.5f, 6.5f, 0.0f);
	return true;
}

void UI0::OnDestroy() {}

void UI0::Update(const float time) {}

void UI0::Render(SDL_Surface *screenSurface) {

	Vec3 screenCoords1 = projectionMatrix * healthBar1Pos;
	Vec3 screenCoords2 = projectionMatrix * healthBar2Pos;

	healthBar1Rect.h = healthBar1Image->h;
	healthBar1Rect.w = healthBar1Image->w;
	healthBar1Rect.x = screenCoords1.x; /// implicit type conversions BAD - probably causes a compiler warning
	healthBar1Rect.y = screenCoords1.y; /// implicit type conversions BAD - probably causes a compiler warning

	healthBar2Rect.h = healthBar2Image->h;
	healthBar2Rect.w = healthBar2Image->w;
	healthBar2Rect.x = screenCoords2.x; /// implicit type conversions BAD - probably causes a compiler warning
	healthBar2Rect.y = screenCoords2.y; /// implicit type conversions BAD - probably causes a compiler warning
	
	SDL_BlitSurface(healthBar1Image, nullptr, screenSurface, &healthBar1Rect);
	SDL_BlitSurface(healthBar2Image, nullptr, screenSurface, &healthBar2Rect);

}
