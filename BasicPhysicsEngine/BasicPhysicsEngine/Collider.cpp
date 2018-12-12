#include "Collider.h"
#include "Body.h"
#include"MMAth.h"
#include"Vector.h"

using namespace A3Engine;
using namespace MATH;


bool Collider::CollisionCheck(const Body &body1, const Body &body2, float _radius)
{
	
	if (Vec3::Distance(body1.position, Vec3(body2.position.x + 10.0f, body2.position.y - 2.0f, body2.position.z)) <  _radius) {
		return true;
	}
	return false;
}

bool Collider::CollisionCheck(const Body &body1, const Body &body2)
{
	if ( Vec3::Distance(body1.position, body2.position) < 31.8f) {
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
	if (topA >= bottomB)
	{
		return false;
	}
	
	if (bottomA <= topB)
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

void Collider::HandleCollision(Body &body1, Body &body2) {
	if (checkCollision(body1.collider, body2.collider)) {
		//The sides of the rectangles
		int leftA, leftB;
		int rightA, rightB;
		int topA, topB;
		int bottomA, bottomB;

		//Calculate the sides of rect A
		leftA = body1.collider.x;
		rightA = body1.collider.x + body1.collider.w;
		topA = body1.collider.y;
		bottomA = body1.collider.y + body1.collider.h;

		//Calculate the sides of rect B
		leftB = body2.collider.x;
		rightB = body2.collider.x + body2.collider.w;
		topB = body2.collider.y;
		bottomB = body2.collider.y + body2.collider.h;

		//bool collidedFromLeft(Object otherObj)
		if (rightA < leftB) {
			body1.linearVelocity.x = -body1.linearVelocity.x;
		}
		else if (leftA >= rightB) {
			body1.linearVelocity.x = -body1.linearVelocity.x;
		}
		else if (bottomA < topB) {
			body1.linearVelocity.y = -body1.linearVelocity.x;
		}
		else if (topA >= bottomB) {
			body1.linearVelocity.y = -body1.linearVelocity.x;
		}
	}
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

//GJK stuff
bool Collider::GJKCollided(Body & body1, Body & body2)
{
	int iter_count = 0;
	int index = 0;
	Vec3 a, b, c, d, ao, ab, ac, abperp, acperp, simplex[3];

	Vec3 position1 = Collider::averagePoint(body1.vertices);
	Vec3 position2 = Collider::averagePoint(body2.vertices);

	d = position2 - position1;

	// if initial direction is zero – set it to any arbitrary axis
	if (d == VECTOR3_ZERO)
		d.x = 1.0f;

	// set the first support as initial point of the new simplex
	a = simplex[0] = Collider::support(body1.vertices, body2.vertices, d);

	if (a.Dot(d) <= 0)
		return false; // no collision

	d = a.Negate(); // The next search direction is always towards the origin, so the next search direction is negate(a)

	while (1) {
		iter_count++;

		a = simplex[++index] = Collider::support(body1.vertices, body2.vertices, d);

		if (a.Dot(d) <= 0.0f)
			return false; // no collision

		ao = a.Negate(); // from point A to Origin is just negative A

		// simplex has 2 points (a line segment, not a triangle yet)
		if (index < 2) {
			b = simplex[0];
			ab = b - a; // from point A to B
			d = Collider::tripleProduct(ab, ao, ab); // normal to AB towards Origin
			if (d.LengthSquared() == 0)
				d = a.Cross(b);
			continue; // skip to next iteration
		}

		b = simplex[1];
		c = simplex[0];
		ab = b - a; // from point A to B
		ac = c - a; // from point A to C

		//acperp = tripleProduct(ab, ac, ac);
		acperp = Collider::tripleProduct(ab, ac, ac);

		if (acperp.Dot(ao) >= 0.0f) {

			d = acperp; // new direction is normal to AC towards Origin

		}
		else {

			abperp = Collider::tripleProduct(ac, ab, ab);

			if (abperp.Dot(ao) < 0)
				return true; // collision

			simplex[0] = simplex[1]; // swap first element (point C)

			d = abperp; // new direction is normal to AB towards Origin
		}

		simplex[1] = simplex[2]; // swap element in the middle (point B)
		--index;
	}


	return false;
}

void Collider::GJKHandleCollision(Body & body1, Body & body2)
{
	if (GJKCollided(body1, body2)) {
		Collider::CalcContactPoints(body1, body2);
	}
}

void Collider::CalcContactPoints(Body & body1, Body & body2)
{
	std::vector<Vec3> translatedVertices1;
	std::vector<Vec3> translatedVertices2;

	int iter_count = 0;
	Vec3 a, b, c, d, ao, ab, ac, bc, bo, a1, a2, b1, b2, c1, c2, closeP1, closeP2, simplex[3];
	Vec3 origin = VECTOR3_ZERO;
	float t, tolerance = 0.1f;

	Vec3 centerPosition1 = Collider::averagePoint(body1.vertices);
	Vec3 centerPosition2 = Collider::averagePoint(body2.vertices);

	//First body
	Vec3 originToP1 = origin - centerPosition1;
	Vec3 p1ToOrigin = centerPosition1 - origin;

	Matrix4 matPos1 = MMath::translate(p1ToOrigin) * MMath::scale(Vec3(0.75f, 0.75f, 1.0f)) * MMath::translate(originToP1);

	for (auto vertex : body1.vertices) {
		Vec3 transVert = matPos1 * vertex;
		transVert.z = 1.0f;
		translatedVertices1.push_back(transVert);
	}

	//second body
	Vec3 originToP2 = origin - centerPosition2;
	Vec3 p2ToOrigin = centerPosition2 - origin;

	Matrix4 matPos2 = MMath::translate(p2ToOrigin) * MMath::scale(Vec3(0.75f, 0.75f, 1.0f)) * MMath::translate(originToP2);

	for (auto vertex : body2.vertices) {
		Vec3 transVert = matPos2 * vertex;
		transVert.z = 1.0f;
		translatedVertices2.push_back(transVert);
	}

	Vec3 position1 = Collider::averagePoint(translatedVertices1);
	Vec3 position2 = Collider::averagePoint(translatedVertices2);

	d = position2 - position1;

	// if initial direction is zero – set it to any arbitrary axis
	if (d == VECTOR3_ZERO)
		d.x = 1.0f;

	// set the first support as initial point of the new simplex
	a = simplex[0] = Collider::support(translatedVertices1, translatedVertices2, d);

	Vec3 p1a = Collider::getFarthestPointInDirection(translatedVertices1, d);
	a1 = p1a;
	Vec3 p1b = Collider::getFarthestPointInDirection(translatedVertices2, d.Negate());
	b1 = p1b;

	d = d.Negate(); // The next search direction is always towards the origin, so the next search direction is negate(a)

	b = simplex[1] = Collider::support(translatedVertices1, translatedVertices2, d);

	Vec3 p2a = Collider::getFarthestPointInDirection(translatedVertices1, d);
	a2 = p2a;
	Vec3 p2b = Collider::getFarthestPointInDirection(translatedVertices2, d.Negate());
	b2 = p2b;

	d = Collider::ClosestPointToOrigin(simplex[0], simplex[1]);

	while (true) {
		d = d.Negate();

		// check if d is the zero vector
		if (d == VECTOR3_ZERO) {
			// then the origin is on the Minkowski Difference
			// I consider this touching/collision
			break;
		}
		// obtain a new Minkowski Difference point along
		// the new direction
		c = Collider::support(translatedVertices1, translatedVertices2, d);
		//std::cout << "C" << iter_count << "\n" << c.toString() << "\n";

		if (iter_count > 2) {
			closeP1 = simplex[0];
			closeP2 = simplex[1];
			break;
		}

		// is the point we obtained making progress
		// towards the goal (to get the closest points
		// to the origin)
		float dc = c.Dot(d);
		// you can use a or b here it doesn't matter
		// since they will be equally distant from
		// the origin
		float da = simplex[0].Dot(d);
		// tolerance is how accurate you want to be
		if (dc - da < tolerance) {

			//distance = d.Mag();
			closeP1 = simplex[0];
			closeP2 = simplex[1];
			break;
		}

		Vec3 p1 = Collider::ClosestPointToOrigin(simplex[0], c);
		Vec3 p2 = Collider::ClosestPointToOrigin(c, simplex[1]);

		if (p1.Mag() < p2.Mag()) {
			simplex[1] = c;
			a2 = Collider::getFarthestPointInDirection(translatedVertices1, d);
			b2 = Collider::getFarthestPointInDirection(translatedVertices2, d.Negate());
			d = p1;
		}
		else {
			simplex[0] = c;
			a1 = Collider::getFarthestPointInDirection(translatedVertices1, d);
			b1 = Collider::getFarthestPointInDirection(translatedVertices2, d.Negate());
			d = p2;
		}

		iter_count++;
	}

	Vec3 line = closeP2 - closeP1;

	float lambda1 = simplex[1].Dot(line) / line.LengthSquared();

	float lambda2 = 1.0f - lambda1;

	Vec3 aClosest = (lambda1 * a1) + (lambda2 * a2);

	Vec3 bClosest = (lambda1 * b1) + (lambda2 * b2);

	Vec3 contactNormal = (bClosest - aClosest) / ((bClosest - aClosest).Mag());

	Matrix4 invMatPos1 = MMath::inverse(matPos1);
	Vec3 contactPointA = invMatPos1 * aClosest;

	Matrix4 invMatPos2 = MMath::inverse(matPos2);
	Vec3 contactPointB = invMatPos2 * bClosest;

	//Collision Response
	float _cor = 1.0f;

	float vr = contactNormal.Dot(body1.linearVelocity - body2.linearVelocity);

	Vec3 r1 = contactPointA - centerPosition1;
	Vec3 r2 = contactPointB - centerPosition2;

	float masses = (1 / body1.getMass()) + (1 / body2.getMass());
	float nr1 = contactNormal.Dot((r1.Cross(contactNormal) / body1.getRotationalInertia()).Cross(r1));
	float nr2 = contactNormal.Dot((r2.Cross(contactNormal) / body2.getRotationalInertia()).Cross(r2));
	float j = (-vr * (_cor + 1.0f)) / (masses + nr1 + nr2);

	body1.linearVelocity += (j * contactNormal) / body1.getMass();
	body2.linearVelocity += (-j * contactNormal) / body2.getMass();

	//𝜔1𝑖 + (𝑟1×(𝐽∗𝑛)) / 𝐼1
	body1.angularVelocity += r1.Cross(j * contactNormal) / body1.getRotationalInertia();
	body2.angularVelocity += r2.Cross(-j * contactNormal) / body2.getRotationalInertia();
}

Vec3 A3Engine::Collider::ClosestPointToOrigin(Vec3 point1, Vec3 point2)
{
	Vec3 origin;
	Vec3 ab = point2 - point1;
	Vec3 ao = origin - point1;

	float t = (ao.Dot(ab)) / ab.LengthSquared();

	Vec3 q = point1 + (ab * t);

	return q;
}
