#include "GameManager.h"
#include "Window.h"
#include "Timer.h"
#include"Scene00.h"
#include"Camera.h"

//GLOBAL STUFF
Camera camera(glm::vec3(0.0f, 2.0f, 3.0f));

void KeyCallback(GLFWwindow *_window, int _key, int _scancode, int _action, int _mode);
void ScrollCallback(GLFWwindow *_window, double _xOffset, double _yOffset);
void MouseCallback(GLFWwindow *_window, double _xPos, double _yPos);
void processInput();

GLfloat lastX = 1280.0f / 2.0;
GLfloat lastY = 720.0f / 2.0f;
bool keys[1024];
bool firstMouse = true;

float deltaTime = 0.0f;

GameManager::GameManager() {
	timer = nullptr;
	isRunning = true;
	currentScene = nullptr;
}


/// In this onCreate() method, fuction, subroutine, whatever the word, 
bool GameManager::onCreate() {
	const int SCREEN_WIDTH = 1280;
	const int SCREEN_HEIGHT = 720;
	window = new Window(SCREEN_WIDTH, SCREEN_HEIGHT);
	if (window == nullptr) {
		onDestroy();
		return false;
	}
	if (window->onCreate() == false) {
		onDestroy();
		return false;
	}

	timer = new Timer();
	if (timer == nullptr) {
		onDestroy();
		return false;
	}

	currentScene = new Scene00(window->GetWindow());
	if (currentScene == nullptr) {
		onDestroy();
		return false;
	}

	if (currentScene->onCreate(&camera) == false) {
		onDestroy();
		return false;
	}

	//setting callbacks
	glfwSetKeyCallback(window->GetWindow(), KeyCallback);
	glfwSetCursorPosCallback(window->GetWindow(), MouseCallback);
	glfwSetScrollCallback(window->GetWindow(), ScrollCallback);

	return true;
}

/// Here's the whole game
void GameManager::Run() {

	timer->Start();

	while (isRunning) {
		deltaTime = timer->GetDeltaTime();
		processInput();

		timer->UpdateFrameTicks();
		currentScene->render();

		if (keys[GLFW_KEY_ESCAPE]) {
			onDestroy();
			isRunning = false;
			glfwSetWindowShouldClose(window->GetWindow(), true);
		}

		glfwPollEvents();
	}


}


GameManager::~GameManager() {}

void GameManager::onDestroy() {
	if (timer) delete timer;
	if (currentScene) {
		currentScene->onDestroy();
		delete currentScene;
	}
	if (window) {
		window->onDestroy();
		delete window;
	}
}

void processInput() {
	if (keys[GLFW_KEY_W])
		camera.ProcessKeyboard(CAMERA::FORWARD, deltaTime);
	if (keys[GLFW_KEY_S])
		camera.ProcessKeyboard(CAMERA::BACKWARD, deltaTime);
	if (keys[GLFW_KEY_A])
		camera.ProcessKeyboard(CAMERA::LEFT, deltaTime);
	if (keys[GLFW_KEY_D])
		camera.ProcessKeyboard(CAMERA::RIGHT, deltaTime);
}


// glfw: whenever there is a key pressed, this callback is called
// -------------------------------------------------------
void KeyCallback(GLFWwindow *_window, int _key, int _scancode, int _action, int _mode) {
	/*if (_key == GLFW_KEY_ESCAPE && _action == GLFW_PRESS) {
		glfwSetWindowShouldClose(_window, true);
	}*/

	if (_key >= 0 && _key < 1024) {
		if (_action == GLFW_PRESS) {
			keys[_key] = true;
		}
		else if (_action == GLFW_RELEASE) {
			keys[_key] = false;
		}
	}
}

// glfw: whenever the mouse moves, this callback is called
// -------------------------------------------------------
void MouseCallback(GLFWwindow* _window, double _xPos, double _yPos) {
	if (firstMouse)
	{
		lastX = _xPos;
		lastY = _yPos;
		firstMouse = false;
	}

	float xoffset = _xPos - lastX;
	float yoffset = lastY - _yPos; // reversed since y-coordinates go from bottom to top

	lastX = _xPos;
	lastY = _yPos;

	camera.ProcessMouseMovement(xoffset, yoffset);
}


// glfw: whenever the mouse scroll wheel scrolls, this callback is called
// ----------------------------------------------------------------------
void ScrollCallback(GLFWwindow* _window, double _xOffset, double _yOffset) {
	camera.ProcessMouseScroll(_yOffset);
}