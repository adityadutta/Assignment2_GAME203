#ifndef SCENE_H
#define SCENE_H

#define GLEW_STATIC
#include<GL\glew.h>

#include<GLFW\glfw3.h>
#include<glm\glm.hpp>
#include<glm\gtc\matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>

class Camera;
class Scene {
public:
	virtual bool onCreate(Camera* _camera) = 0;								//creates the scene elements
	virtual void onDestroy() = 0;								//cleaner method to destroy and free memory
	virtual void update(const float time) = 0;					//updates the scene with the given timeStep
	virtual void render() = 0;									//renders the scene elements and the UI
	virtual void handleEvents() = 0;							//handles key and mouse inputs in the scene
};

#endif
