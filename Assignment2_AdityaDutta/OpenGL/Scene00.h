#ifndef SCENE00_H
#define SCENE00_H

#include "Scene.h"
#include<memory>
#include<vector>

class Shader;
class Body;
class Camera;
class Model;
class Scene00 : public Scene {
private:

	GLFWwindow *window;

	std::unique_ptr<Body> plane;
	std::unique_ptr<Body> nano;

	// timing
	float deltaTime = 0.0f;	// time between current frame and last frame
	float lastFrame = 0.0f;


	Shader* lightingShader;

	Camera* sceneCamera;

	Model* nanoModel;
	Model* planeModel;
	Model* treeModel;

	std::vector<Body*> trees1;
	std::vector<Body*> trees2;

public:
	Scene00(GLFWwindow* _window);
	bool onCreate(Camera* _camera);
	void onDestroy();
	void update(const float time);
	void render();
	void handleEvents();
};

#endif

