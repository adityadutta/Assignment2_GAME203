#include "DynamicScene.h"

#include <fstream>
#include <iostream>
#include <SDL.h>


DynamicScene::DynamicScene(SDL_Window* sdlWindow_) {
	window = sdlWindow_;	
	// Set up Map
	myMap.insert(make_pair("Object1", Object1));
	myMap.insert(make_pair("Object2", Object2));
	// Set Image and Position to null and (0, 0, 0)
	myMap["Object1"].SetImage(nullptr);
	myMap["Object1"].SetPos(Vec3(0, 0, 0));
	myMap["Object2"].SetImage(nullptr);
	myMap["Object2"].SetPos(Vec3(0, 0, 0));
}

DynamicScene::~DynamicScene() {}

bool DynamicScene::OnCreate() {
	int w, h;
	SDL_GetWindowSize(window, &w, &h);
	projectionMatrix = MMath::viewportNDC(w, h) * MMath::orthographic(0.0f, 14.0f, 0.0f, 7.0f, 0.0f, 1.0f);

	// Open the file (Files are "Object1.txt" and "Object2.txt")
	ifstream file;
	file.open("Object1.txt");
	
	// Variable to get parts of the file
	string fileName1;
	int pointX1;
	int pointY1;
	int pointZ1;

	string fileName2;
	int pointX2;
	int pointY2;
	int pointZ2;

	if (file.is_open()) {
		while (file >> fileName1 >> pointX1 >> pointY1 >> pointZ1 >> fileName2 >> pointX2 >> pointY2 >> pointZ2) {
			// Convert file name to const char *
			string * fileName1Pointer = &fileName1;
			const char * fileName1Char = fileName1Pointer->c_str();
			// Add image and pos to object 1
			myMap["Object1"].SetImage(SDL_LoadBMP(fileName1Char));
			myMap["Object1"].SetPos(Vec3(pointX1, pointY1, pointZ1));
			
			// Convert file name to const char *
			string * fileName2Pointer = &fileName2;
			const char * fileName2Char = fileName2Pointer->c_str();
			// Add image and pos to object 2
			myMap["Object2"].SetImage(SDL_LoadBMP(fileName2Char));
			myMap["Object2"].SetPos(Vec3(pointX2, pointY2, pointZ2));
		}
		// Close file
		file.close();
	}
	return true;
}

void DynamicScene::OnDestroy() {}

void DynamicScene::Update(const float time) {}

void DynamicScene::Render() {
	
	Vec3 screenCoords1 = projectionMatrix * myMap["Object1"].pos;
	Vec3 screenCoords2 = projectionMatrix * myMap["Object2"].pos;

	myMap["Object1"].rect.h = myMap["Object1"].image->h;
	myMap["Object1"].rect.w = myMap["Object1"].image->w;
	myMap["Object1"].rect.x = screenCoords1.x; /// implicit type conversions BAD - probably causes a compiler warning
	myMap["Object1"].rect.y = screenCoords1.y; /// implicit type conversions BAD - probably causes a compiler warning

	myMap["Object2"].rect.h = myMap["Object2"].image->h;
	myMap["Object2"].rect.w = myMap["Object2"].image->w;
	myMap["Object2"].rect.x = screenCoords2.x; /// implicit type conversions BAD - probably causes a compiler warning
	myMap["Object2"].rect.y = screenCoords2.y; /// implicit type conversions BAD - probably causes a compiler warning

	SDL_Surface *screenSurface = SDL_GetWindowSurface(window);
	SDL_FillRect(screenSurface, nullptr, SDL_MapRGB(screenSurface->format, 0xff, 0xff, 0xff));
	SDL_BlitSurface(myMap["Object1"].image, nullptr, screenSurface, &myMap["Object1"].rect);
	SDL_BlitSurface(myMap["Object2"].image, nullptr, screenSurface, &myMap["Object2"].rect);

	SDL_UpdateWindowSurface(window);
}

void DynamicScene::HandleEvents(const SDL_Event& event) {}

