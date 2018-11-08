#ifndef SCENE_H
#define SCENE_H
#include <memory>

class Scene {
public:
	virtual bool OnCreate() = 0;
	virtual void OnDestroy() = 0;
	virtual void Update(const float time, int checkScence) = 0;
	virtual void Render() = 0;
	virtual void CheckKey(int chechUI_) = 0;
};

#endif
