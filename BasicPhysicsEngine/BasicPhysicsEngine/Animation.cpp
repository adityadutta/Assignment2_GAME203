#include "Animation.h"



Animation::Animation()
{
	frame = 0;

	AnimationsImages.push_back("Sprites/Mario/MarioBigRun1.png");
	AnimationsImages.push_back("Sprites/Mario/MarioBigIdle.png");
	AnimationsImages.push_back("Sprites/Mario/MarioBigJump.png");

	// flipedImages	
	AnimationsImagesFliped.push_back("Sprites/Mario/MarioBigRun1F.png");
	AnimationsImagesFliped.push_back("Sprites/Mario/MarioBigIdleF.png");
	AnimationsImagesFliped.push_back("Sprites/Mario/MarioBigJumpF.png");

}

void Animation::setAnim(Body& body, States bo) {

	if (bo == States::WALKING) {
		body.SetImage(AnimationsImages[frame]);		
		frame++;
		if (frame == 2) {
			frame = 0;
		}
	}
	if (bo == States::JUMPING) {
		body.SetImage(AnimationsImages[2]);
	}
}

void Animation::setAnimFliped(Body& body, States bo) {

	if (bo == States::WALKING) {
		body.SetImage(AnimationsImagesFliped[frame]);
		frame++;
		if (frame == 2) {
			frame = 0;
		}
	}
	if (bo == States::JUMPING) {
		body.SetImage(AnimationsImagesFliped[2]);
	}
}


Animation::~Animation()
{
}
