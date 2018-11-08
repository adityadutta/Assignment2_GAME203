#include "Body.h"

Body::Body(char* _modelName, double _mass, float _rotationalInertia)
{
	mass = _mass;
	rotationalInertia = _rotationalInertia;
	position.SetZero();
	linearVelocity.SetZero();
	acceleration.SetZero();
	angle = 0.0f;
	angularVelocity = 0.0f;
	angularVelocity = 0.0f;
}

//constructor to pass values in the class
Body::Body(char* _modelName, double _mass, float _rotationalInertia, Vec3 _position, Vec3 _linearVelocity, Vec3 _acceleration, float _angle, float _angularVelocity, float _angularAcceleration, Vec3 _modelScale)
{
	mass = _mass;
	rotationalInertia = _rotationalInertia;
	position = _position;
	linearVelocity = _linearVelocity;
	acceleration = _acceleration;
	angle = _angle;
	angularVelocity = _angularVelocity;
	angularAcceleration = _angularAcceleration;

	modelScale = _modelScale;
}
void Body::Update(double timeStep)
{
	//Update position from velocity times timeStep
	//position = position(init) + linearVelocity * time + 0.5 * acceleration * time ^2
	position += (linearVelocity * timeStep) + (acceleration * 0.5 * timeStep * timeStep);

	//Update velocity from acceleration times timeStep
	//linearVelocity = linearVelocity(init) + acceleration * time;
	linearVelocity += acceleration * timeStep;
	

}

void Body::UpdateOrientation(double timeStep)
{
	//angle = angle(i) + angularVel * t + 0.5 * angularAcc * t^2
	angle += (angularVelocity * timeStep) + (angularAcceleration * 0.5 * timeStep * timeStep);

	//angularVelocity = angularVelocity(init) + angularAcceleration * time;
	angularVelocity += angularAcceleration * timeStep;

}

void Body::ApplyTorque(float _torque)
{ 
	//Apply torque
	//a = t/I;
	angularAcceleration = _torque / rotationalInertia;
}

void Body::ApplyForceToCentre(const Vec3& force)
{ 
	//Vec3 temp(force);
	float fx = (force.x * cos(angle)) - (force.y * sin(angle));
	float fy = (force.y * cos(angle)) + (force.x * sin(angle));

	//set force in the body
	this->force.Set(fx, fy, 0.0f);

	//a = f/m
	acceleration = this->force / mass;
}

Vec3 Body::getFarthestPointInDirection(const Vec3 & d)
{
	Vec3 farthestPoint;
	int index = 0;
	float maxProduct = d.Dot(vertices[0]);
	for (int i = 1; i < vertices.size(); i++) {
		float product = d.Dot(vertices[i]);
		if (product > maxProduct) {
			maxProduct = product;
			index = i;
		}
	}
	farthestPoint = vertices[index];
	return farthestPoint;
}

void Body::addVertex(const Vec3 _vertex)
{
	vertices.push_back(_vertex);
}

double Body::getMass() {
	return mass;
}

// Processes input received from any keyboard-like input system. Accepts input parameter in the form of camera defined ENUM (to abstract it from windowing systems)
void Body::ProcessKeyboard(BODY::Player_Movement _direction, float _deltaTime)
{
	Vec3 velocity = linearVelocity * _deltaTime;
	if (_direction == BODY::FORWARD)
		position += VECTOR3_FORWARD * _deltaTime;
	if (_direction == BODY::BACKWARD)
		position += VECTOR3_BACK * _deltaTime;
	if (_direction == BODY::LEFT)
		position += VECTOR3_LEFT * _deltaTime;
	if (_direction == BODY::RIGHT)
		position += VECTOR3_RIGHT * _deltaTime;
}

Body::~Body()
{

}
