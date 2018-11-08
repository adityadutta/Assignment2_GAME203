#include "Scene00.h"
#include"Body.h"
#include"Camera.h"
#include"Model.h"
#include"Shader.h"

Scene00::Scene00(GLFWwindow* _window) {

	window = _window;
}

bool Scene00::onCreate(Camera* _camera) {
	sceneCamera = _camera;

	lightingShader = new Shader("res/shaders/lighting.vs", "res/shaders/lighting.frag");
	if (lightingShader == nullptr) {
		onDestroy();
		return false;
	}

	lightingShader->use();
	lightingShader->setInt("material.diffuse", 0);
	lightingShader->setInt("material.specular", 1);

	// load models
	// -----------
	nanoModel = new Model("res/models/nanosuit/nanosuit.obj");
	planeModel = new Model("res/models/ground/plane.obj");
	treeModel = new Model("res/models/trees/tree2/Tree.obj");

	plane = std::unique_ptr<Body>(new Body("res/models/plane/plane.obj", 1.0f, 1.0f, VECTOR3_FORWARD, VECTOR3_ZERO, VECTOR3_ZERO, 0.0f, 0.0f, 0.0f, Vec3(0.2f, 0.2f, 0.2f)));
	plane->model = planeModel;
	if (plane == nullptr) {
		onDestroy();
		return false;
	}


	nano = std::unique_ptr<Body>(new Body("res/models/nanosuit/nanosuit.obj", 1.0f, 1.0f, VECTOR3_LEFT * 2.0f, VECTOR3_ZERO, VECTOR3_ZERO, 0.0f, 0.0f, 0.0f, Vec3(0.2f, 0.2f, 0.2f)));
	nano->model = nanoModel;
	if (nano == nullptr) {
		onDestroy();
		return false;
	}

	//tree positions for first kind of tree
	glm::vec3 treePositions1[] = {
				glm::vec3(0.0f,  0.0f,  0.0f),
				glm::vec3(2.0f,  0.0f, -15.0f),
				glm::vec3(-1.5f, 0.0f, -2.5f),
				glm::vec3(-3.8f, 0.0f, -12.3f),
				glm::vec3(2.4f, 0.0f, -3.5f),
				glm::vec3(-1.7f, 0.0f, -7.5f),
				glm::vec3(1.3f, 0.0f, -2.5f),
				glm::vec3(1.5f,  0.0f, -2.5f),
				glm::vec3(1.5f,  0.0f, -1.5f),
				glm::vec3(-1.3f,  0.0f, -1.5f)
	};

	for (int i = 0; i < 10; i++) {
		trees1.push_back(new Body("res/models/trees/tree2/Tree.obj", 1.0f, 1.0f, Vec3(treePositions1[i].x, treePositions1[i].y, treePositions1[i].z), VECTOR3_ZERO, VECTOR3_ZERO, 0.0f, 0.0f, 0.0f, Vec3(1.0f, 1.0f, 1.0f)));
	}
	for (auto tree : trees1) {
		tree->model = treeModel;
	}

	//tree positions for second kind of tree
	glm::vec3 treePositions2[] = {
				glm::vec3(1.0f,  0.0f,  0.0f),
				glm::vec3(2.0f,  0.0f, -1.0f),
				glm::vec3(-1.5f, 0.0f, -3.5f),
				glm::vec3(-2.8f, 0.0f, -12.3f),
				glm::vec3(2.4f, 0.0f, -1.5f),
				glm::vec3(-1.7f, 0.0f, -5.5f),
				glm::vec3(-3.3f, 0.0f, -2.5f),
				glm::vec3(2.5f,  0.0f, -2.5f),
				glm::vec3(1.5f,  0.0f, 4.5f),
				glm::vec3(-4.3f,  0.0f, -2.5f)
	};

	for (int i = 0; i < 10; i++) {
		trees2.push_back(new Body("res/models/trees/tree2/Tree.obj", 1.0f, 1.0f, Vec3(treePositions2[i].x, treePositions2[i].y, treePositions2[i].z), VECTOR3_ZERO, VECTOR3_ZERO, 0.0f, 0.0f, 0.0f, Vec3(0.5f, 0.5f, 0.5f)));
	}
	for (auto tree : trees2) {
		tree->model = treeModel;
	}

	return true;
}

void Scene00::onDestroy() {
	for (auto tree : trees1) {
		if (tree) {
			delete tree;
		}
	}

	for (auto tree : trees2) {
		if (tree) {
			delete tree;
		}
	}

	if (nanoModel) {
		delete nanoModel;
	}
	if (planeModel) { 
		delete planeModel;
	}
	if (treeModel) {
		delete treeModel;
	}
	if (lightingShader) {
		delete lightingShader;
	}
}

void Scene00::update(const float time) {

}

void Scene00::render() {
	glClearColor(0.1f, 0.2f, 0.7f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	// create transformations
	int SCREEN_WIDTH, SCREEN_HEIGHT;
	glfwGetFramebufferSize(window, &SCREEN_WIDTH, &SCREEN_HEIGHT);
	glm::mat4 projection = glm::perspective(sceneCamera->GetZoom(), (GLfloat)SCREEN_WIDTH / (GLfloat)SCREEN_HEIGHT, 0.1f, 100.0f);
	glm::mat4 view = sceneCamera->GetViewMatrix();

	glm::vec3 lightPos(0.0f, 0.0f, 3.0f);
	// be sure to activate shader when setting uniforms/drawing objects
	lightingShader->use();
	lightingShader->setVec3("light.position", sceneCamera->GetPosition());
	lightingShader->setVec3("light.direction", sceneCamera->GetFront());
	lightingShader->setVec3("viewPos", sceneCamera->GetPosition());

	lightingShader->setMat4("projection", projection);
	lightingShader->setMat4("view", view);

	// light properties
	lightingShader->setVec3("light.ambient", 1.0f, 1.0f, 1.0f);
	lightingShader->setVec3("light.diffuse", 0.5f, 0.5f, 0.5f);
	lightingShader->setVec3("light.specular", 1.0f, 1.0f, 1.0f);

	lightingShader->setFloat("light.constant", 1.0f);
	lightingShader->setFloat("light.linear", 0.09f);
	lightingShader->setFloat("light.quadratic", 0.032f);


	// material properties
	lightingShader->setFloat("material.shininess", 64.0f);

	// world transformation
	glm::mat4 model(1.0f);
	model = glm::translate(model, glm::vec3(1.0f, 0.0f, 1.0f));;
	lightingShader->setMat4("model", model);

	// render the plane model
	model = glm::translate(model, glm::vec3(plane->position.x, plane->position.y, plane->position.z)); // translate it down so it's at the center of the scene
	model = glm::scale(model, glm::vec3(plane->modelScale.x, plane->modelScale.y, plane->modelScale.z));	// it's a bit too big for our scene, so scale it down
	lightingShader->setMat4("model", model);
	plane->model->Draw(*lightingShader);

	// render the nanosuit model
	model = glm::mat4(1.0f);
	model = glm::translate(model, glm::vec3(nano->position.x, nano->position.y, nano->position.z)); // translate it down so it's at the center of the scene
	model = glm::scale(model, glm::vec3(nano->modelScale.x, nano->modelScale.y, nano->modelScale.z));	// it's a bit too big for our scene, so scale it down
	lightingShader->setMat4("model", model);
	nano->model->Draw(*lightingShader);

	//tree1
	for (auto tree : trees1) {
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(tree->position.x, tree->position.y, tree->position.z)); // translate it down so it's at the center of the scene
		model = glm::scale(model, glm::vec3(tree->modelScale.x, tree->modelScale.y, tree->modelScale.z));	// it's a bit too big for our scene, so scale it down
		lightingShader->setMat4("model", model);

		tree->model->Draw(*lightingShader);
	}
	//tree2
	for (auto tree : trees2) {
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(tree->position.x, tree->position.y, tree->position.z)); // translate it down so it's at the center of the scene
		model = glm::scale(model, glm::vec3(tree->modelScale.x, tree->modelScale.y, tree->modelScale.z));	// it's a bit too big for our scene, so scale it down
		lightingShader->setMat4("model", model);

		tree->model->Draw(*lightingShader);
	}

	glfwSwapBuffers(window);
}

void Scene00::handleEvents() {

}
