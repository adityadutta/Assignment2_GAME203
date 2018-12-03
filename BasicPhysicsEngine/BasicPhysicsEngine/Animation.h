#ifndef ANIMATION_H
#define ANIMATION_H

#include<vector>
#include"gdBody.h"

enum class States{
	WALKING,
	JUMPING
};
class Animation
{
public:
	Animation();
	~Animation();
	std::vector<char*> AnimationsImages;
	inline void setAnim(gdBody& body, States bo) {
		if (bo == States::WALKING) {
			body.SetImage(AnimationsImages[0]);
		}
	}

};
#endif

