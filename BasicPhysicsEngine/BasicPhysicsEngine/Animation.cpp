#include "Animation.h"



Animation::Animation()
{
	frame = 0;

	AnimationsImages.push_back("MarioBigRun1.png");
	AnimationsImages.push_back("MarioBigIdle.png");
	AnimationsImages.push_back("MarioBigJump.png");

	
	// flipedImages	
	AnimationsImagesFliped.push_back("Fliped_MarioBigRun1.png");
	AnimationsImagesFliped.push_back("Fliped_MarioBigIdle.png");
	AnimationsImagesFliped.push_back("Fliped_MarioBigJump.png");

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
