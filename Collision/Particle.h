#pragma once

class Vector
{
public:
	float x;
	float y;
	float z;

	float Magnitude();
};

class Particle
{
public:
	float fMass;
	Vector vPosition;
	Vector vVelocity;
	float fSpeed;
	Vector vForces;
	float fRadius;
	Vector vGravity;

	Vector vPreviousPosition;
	Vector vImpactForces;
	bool bCollision = false;

	Particle(void);
	void CalcLoads(void);
	void UpdateBodyEuler(double dt);
	void Draw(void);
};