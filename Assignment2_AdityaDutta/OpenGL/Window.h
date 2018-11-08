#ifndef WINDOW_H
#define WINDOW_H
#pragma once

#define GLEW_STATIC
#include<GL\glew.h>

#include<GLFW\glfw3.h>

#include<stdio.h>
#include<string>

class Window {
private:
	GLFWwindow* window;
	
	GLint width, height;
public:
	GLint SCREEN_WIDTH, SCREEN_HEIGHT;

	Window(int width_, int height_);
	~Window();
	bool onCreate();
	void onDestroy();
	GLFWwindow* GetWindow();
};
#endif // !WINDOW_H