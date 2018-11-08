#include "Scene0.h"
#include <SDL.h>
Scene0::Scene0(SDL_Window* sdlWindow_){
	window = sdlWindow_;
	jetSkiImage = nullptr;
}

Scene0::~Scene0(){}

bool Scene0::OnCreate() {
	int w, h;
	SDL_GetWindowSize(window,&w,&h);
	projectionMatrix = MMath::viewportNDC(w,h) * MMath::orthographic(0.0f, 14.0f, 0.0f, 7.0f, 0.0f, 1.0f) ;
	jetSkiImage = SDL_LoadBMP("jetski.bmp");
	if (jetSkiImage == nullptr) {
		return false;
	}
	jetSkiPos.Load(0.0f, 1.5f, 0.0f);
	ui = new UI0(window);
	ui->OnCreate();
	return true;
}

void Scene0::OnDestroy() {}

void Scene0::Update(const float time) {}

void Scene0::Render() {

	Vec3 screenCoords = projectionMatrix * jetSkiPos;

	jetSkiRect.h = jetSkiImage->h;
	jetSkiRect.w = jetSkiImage->w;
	jetSkiRect.x = screenCoords.x; /// implicit type conversions BAD - probably causes a compiler warning
	jetSkiRect.y = screenCoords.y; /// implicit type conversions BAD - probably causes a compiler warning
	
	SDL_Surface *screenSurface = SDL_GetWindowSurface(window);
	SDL_FillRect(screenSurface, nullptr, SDL_MapRGB(screenSurface->format, 0xff, 0xff, 0xff));
	SDL_BlitSurface(jetSkiImage, nullptr, screenSurface, &jetSkiRect);
	//Render the UI
	ui->Render(screenSurface);
	SDL_UpdateWindowSurface(window);
}

void Scene0::HandleEvents(const SDL_Event& event) {
	switch (event.type) {
	case SDL_KEYDOWN:
		if (event.key.keysym.sym == SDLK_1) {
			//Delete current UI and load UI0
			delete ui;
			ui = nullptr;
			ui = new UI0(window);
			ui->OnCreate();
		}
		if (event.key.keysym.sym == SDLK_2) {
			//Delete current UI and load UI1
			delete ui;
			ui = nullptr;
			ui = new UI1(window);
			ui->OnCreate();
		}
	}
}
