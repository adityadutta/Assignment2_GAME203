#ifndef COLLIDER_H
#define COLLIDER_H
#include"Vector.h"
#include"Body.h"
class Collider
{
public:
	Collider();
	~Collider();
	static bool CollisionCheck(const Body &body1, const Body &body2);
	static bool CollisionCheck(const Body &body1, const Body &body2, float _radius);
	static bool checkCollision(SDL_Rect a, SDL_Rect b);
	static void HandleCollision(Body &body1, Body &body2, float _cor);
	static void HandleMovingCollision(Body &body1, Body &body2, float _cor);
};
#endif // !COLLIDER_H