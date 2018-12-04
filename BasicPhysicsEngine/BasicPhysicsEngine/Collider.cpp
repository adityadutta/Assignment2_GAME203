#include "Collider.h"
#include"Vector.h"


Collider::Collider()
{
}


Collider::~Collider()
{
}

bool Collider::CollisionCheck(const Body &body1, const Body &body2, float _radius)
{
	
	if (Vec3::Distance(body1.position, Vec3(body2.position.x + 10.0f, body2.position.y - 2.0f, body2.position.z)) <  _radius) {
		return true;
	}
	return false;
}

bool Collider::CollisionCheck(const Body &body1, const Body &body2)
{
	if ( Vec3::Distance(body1.position, body2.position) < 3.8f) {
		return true;
	}
	return false;
}

bool Collider::checkCollision(SDL_Rect a, SDL_Rect b)
{
	//The sides of the rectangles
	int leftA, leftB;
	int rightA, rightB;
	int topA, topB;
	int bottomA, bottomB;

	//Calculate the sides of rect A
	leftA = a.x;
	rightA = a.x + a.w;
	topA = a.y;
	bottomA = a.y + a.h;

	//Calculate the sides of rect B
	leftB = b.x;
	rightB = b.x + b.w;
	topB = b.y;
	bottomB = b.y + b.h;
	//If any of the sides from A are outside of B
	if (bottomA <= topB)
	{
		return false;
	}

	if (topA >= bottomB)
	{
		return false;
	}

	if (rightA <= leftB)
	{
		return false;
	}

	if (leftA >= rightB)
	{
		return false;
	}

	//If none of the sides from A are outside B
	return true;
}
void Collider::HandleCollision(Body &body1, Body &body2, float _cor)
{
		Vec3 normal = (body2.position - body1.position).Normalize();

		Vec3 projection = (-body1.linearVelocity.Dot(normal)) * normal;

		body1.linearVelocity += 2 * projection * _cor;
}
void Collider::HandleMovingCollision(Body &body1, Body &body2, float _cor)
{
	Vec3 normal = (body2.position - body1.position).Normalize();

	float initVelocity1 = body1.linearVelocity.Dot(normal);
	float initVelocity2 = body2.linearVelocity.Dot(normal);

	float finVelocity1 = (((body1.getMass() - _cor * body2.getMass()) * initVelocity1) + ((1.0f + _cor) * body2.getMass() * initVelocity2)) / (body1.getMass() + body2.getMass());
	float finVelocity2 = (((body2.getMass() - _cor * body1.getMass()) * initVelocity2) + ((1.0f + _cor) * body1.getMass() * initVelocity1)) / (body1.getMass() + body2.getMass());

	body1.linearVelocity = ((finVelocity1 - initVelocity1) * normal);
	body2.linearVelocity = ((finVelocity2 - initVelocity2) * normal);
}