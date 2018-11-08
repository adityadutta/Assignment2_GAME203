#include<memory>

#include"GameManager.h"

int main(int arg, char* argc[]) {

	std::unique_ptr<GameManager> gm = std::unique_ptr<GameManager>(new GameManager());
	if (gm->onCreate()) {
		gm->Run();
	}

	return EXIT_SUCCESS;
}