#ifndef ANIMATION_H
#define ANIMATION_H

#include <vector>
#include "Body.h"

enum class States {
	WALKING,
	JUMPING
};
class Animation
{
public:
	Animation();
	~Animation();
	std::vector<char*> AnimationsImages;
	void setAnim(Body& body, States bo);
	float frame;
};
#endif
