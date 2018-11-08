#ifndef BODY_H
#define BODY_H

#include"Vector.h"
#include<vector>
//#include"Model.h"

namespace BODY {
	enum Player_Movement {
		FORWARD,
		BACKWARD,
		LEFT,
		RIGHT
	};
}

using namespace MATH;
class Model;
class Body
{
	double mass;								//variable to hold the value of mass
	float rotationalInertia;					//variable to hold rotational inertia
public:
	Vec3 position;								//variable to hold the value of position
	Vec3 linearVelocity;						//variable to hold the value of velocity
	Vec3 acceleration;							//variable to hold the value of acceleration
	Vec3 force;

	Model* model;
	Vec3 modelScale;

	float angle;
	float angularVelocity;						//variable to hold the value of angular velocity
	float angularAcceleration;					//variable to hold the value of angular acceleration

	std::vector<Vec3> vertices;

	Body(char* _modelName, double _mass, float _rotationalInertia);
	Body(char* _modelName, double _mass, float _rotationalInertia, Vec3 _position, Vec3 _linearVelocity, Vec3 _acceleration, float _angle, float _angularVelocity, float _angularAcceleration, Vec3 _modelScale);
	void Update(double timeStep);
	void UpdateOrientation(double timeStep);
	void ApplyTorque(float _torque);
	void ApplyForceToCentre(const Vec3& force);   // update acceleration using a = F/m

	Vec3 getFarthestPointInDirection(const Vec3& d);
	void addVertex(const Vec3 _vertex);

	double getMass();

	void ProcessKeyboard(BODY::Player_Movement _direction, float _deltaTime);

	~Body();

};
#endif //!BODY_H