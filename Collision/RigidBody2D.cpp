
#include "RigidBody2D.h"

const float _THRUSTFORCE = 10;

RigidBody2D::RigidBody2D(void)
{
	fMAss = 100;
	fInertia = 500;
	fInertaInverse = 1/fInertia;
	vPosition.x = 0;
	vPosition.y = 0;
	fWidth = 10;
	fLength = 20;
	fHeight = 5; 
	fOrientation = 0; 

	DragCenter.x = - 0.25 * fLength;
	DragCenter.y = 0.0f;
	DragCenter.x = 0.0f;

	ThrustCenter.x = - 0.25 * fLength;
	ThrustCenter.y = 0.0f;
	ThrustCenter.x = 0.0f;

	PortThrustCenter.x = 0.5 * fLength;
	PortThrustCenter.y = -0.5 * fWidth;
	PortThrustCenter.x = 0.0f;

	StarboardThrustCenter.x = 0.5 * fLength;
	StarboardThrustCenter.y = -0.5 * fWidth;
	StarboardThrustCenter.x = 0.0f;

	ProjectedArea = (fLength + fWidth) / 2 * fHeight;
	ThrustForce = _THRUSTFORCE;
};

void RigidBody2D::CalcLoads(void)
{
	Vector totalForce; 
	Vector totalMoment; 
	Vector Thrust; 

	vForce.x = 0.0f; 
	vForce.y = 0.0f; 
	vForce.z = 0.0f; 

	vMoment.x = 0.0f;
	vMoment.y = 0.0f;
	vMoment.z = 0.0f;

	totalForce.x = 0.0f;
	totalForce.y = 0.0f;
	totalForce.z = 0.0f;

	totalMoment.x = 0.0f;
	totalMoment.y = 0.0f;
	totalMoment.z = 0.0f;

	Thrust.x = 1.0f;
	Thrust.y = 0.0f;
	Thrust.z = 0.0f;

	Thrust *= ThrustForce;

	Vector vLocalVelocity;
	float fLocalSpeed; 
	Vector vDragVector; 
	float tmp; 
	Vector vResultant; 
	Vector vtmp; 
}

void RigidBody2D::UpdateBodyEuler(double dt)
{
	Vector a;
	Vector dv;
	Vector ds;

	float angularAcceliration; 
	float dAngularVelocity;
	float dAngle;

	CalcLoads();

	a = vForces / fMass;

	dv = a * dt; 
	vVelocity += dv; 

	ds = vVelocity * dt; 
	vPosition += ds; 

	angularAcceliration = vMoment.z / fInertia;
	dAngularVelocity = angularAcceliration * dt;

	vAngularVelocity.z += dAngularVelocity;

	dAngle = RadToDeg(vAngularVelocity.z * dt);
	fOrientation += dAngle;

	fSpeed = vVelocity.Magnitude();
	vVelocityBody = VRotate2D(-fOrientation, vVelocity);
}