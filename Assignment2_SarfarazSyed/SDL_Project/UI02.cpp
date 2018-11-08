//#include "UI02.h"
//
//
//
//
//UI02::UI02() {
//
//}
//
//bool UI02::onCreate() {
//
//	uiBodies.push_back ( new Body("RPGMap.png", Vec3(26.5f, 35.0f, 0.0f)));
//	uiBodies.push_back ( new Body("Health.png", Vec3(-3.0f, -15.0f, 0.0f)));
//	uiBodies.push_back ( new Body("RpgCharacter.png", Vec3(29.0f, 17.5f, 0.0f)));
//
//
//	for (auto Body : uiBodies) {
//		if (Body == nullptr) {
//			return false;
//		}
//	}
//	return true;
//}
//
//void UI02::onDestroy() {
//	IMG_Quit();
//	for(auto Body: uiBodies) {
//		if (Body) {
//			delete Body;
//			Body = nullptr;
//		}
//	}
//}
//
//void UI02::update(const float time) {
//
//}
//
//bool UI02::getCloseWindow() {
//	return closeWindow;
//}
//
////std::vector<Body*>  UI02::render() {
////
////	return uiBodies;
////}
//
//void UI02::render(SDL_Window *window) {
//
//	SDL_Rect imageRectangle;
//	int w, h;
//	IMG_Init(IMG_INIT_PNG);
//	SDL_GetWindowSize(window, &w, &h);
//	projectionMatrix = MMath::viewportNDC(w, h) * MMath::orthographic(-20.0f, 35.0f, -20.0f, 35.0f, 0.0f, 1.0f);
//	SDL_Surface *screenSurface = SDL_GetWindowSurface(window);
//
//
//	for (auto Body : uiBodies) {
//		Vec3 screenCoords = projectionMatrix * Body->pos;
//
//		imageRectangle.h = Body->getImage()->h;
//		imageRectangle.w = Body->getImage()->w;
//		imageRectangle.x = screenCoords.x; /// implicit type conversions BAD - probably causes a compiler warning
//		imageRectangle.y = screenCoords.y; /// implicit type conversions BAD - probably causes a compiler warning			
//		SDL_BlitSurface(Body->getImage(), nullptr, screenSurface, &imageRectangle);
//
//	}
//}
//
//UI02::~UI02()
//{
//}
