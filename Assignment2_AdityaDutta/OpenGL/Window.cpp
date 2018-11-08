#include "Window.h"
#include<iostream>

Window::Window(int width_, int height_) {
	window = nullptr;
	width = width_;
	height = height_;
}

bool Window::onCreate() {
	if (!glfwInit() < 0) {
		std::cout << "Failed to initialize GLFW" << std::endl;
		glfwTerminate();

		return GL_FALSE;
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	 window = glfwCreateWindow(width, height, "A3Engine v0.1", nullptr, nullptr);

	glfwGetFramebufferSize(window, &SCREEN_WIDTH, &SCREEN_HEIGHT);

	if (window == nullptr) {
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();

		return GL_FALSE;
	}

	glfwMakeContextCurrent(window);

	// tell GLFW to capture our mouse
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	glewExperimental = GL_TRUE;

	if (glewInit() != GLEW_OK) {
		std::cout << "Failed to initialize GLFW" << std::endl;

		return EXIT_FAILURE;
	}

	glViewport(0, 0, width, height);

	glEnable(GL_DEPTH_TEST);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	return true;
}

void Window::onDestroy() {
	glfwTerminate();
}

Window::~Window() {}

GLFWwindow* Window::GetWindow() {
	return window;
}

