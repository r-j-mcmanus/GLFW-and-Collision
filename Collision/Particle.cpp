
#include "Particle.h"

#define _GravityAcceleration = -9.8f;

Particle::Particle(void)
{
	fMass = 0.0;

	vPosition.x = 0.0;
	vPosition.y = 0.0;
	vPosition.z = 0.0;

	vVelocity.x = 0.0;
	vVelocity.y = 0.0;
	vVelocity.z = 0.0;

	fSpeed = 0.0;

	vForces.x = 0;
	vForces.y = 0;
	vForces.z = 0;

	fRadius = 0.1;

	vGravity.x = 0;
	vGravity.y = fMass * _GravityAcceleration;
}

void Particle::CalcLoads(void)
{
	vForces.x = 0;
	vForces.y = 0;

	if (bCollision)
	{
		vForces += vImpactForces;
	}
	else
	{
		vForces += vGravity;
	}
}

void Particle::UpdateBodyEuler(double dt) :
{
//Could use better but why bother
	Vector a;
	Vector dv;
	Vector ds;

	a = vForces / fMass;

	dv = a * dt;
	vVelocity += dv;

	ds = vVelocity * dt;
	vPosition += ds;

	fSpeed = vVelocity.Magnitude();
}

void Particle::Draw(void)
{

}

///////////////////////////////////////////////////////////////


void UpdateSimulation()
{
	double dt = _TIMESTEP;
	int i;

	if (FrameCounter >= _RENDER_FRAME_COUNT)
	{
		ClearBackBuffer();
	}

	for (auto& unit : units)
	{
		unit.bCollision = CheckForCollisions(&(unit))
		unit.CalcLoads();
		unit.UpdateBodyEuler(dt);

		if (FrameCounter >= _RENDER_FRAME_COUNT)
		{
			unit.draw;
		}

		PutUnitPositionInBounds(unit);
	}
};

void PutUnitPositionInBounds(Particle unit)
{
	//the space is a torus
	if (unit.vPosition.x > _WINWIDTH) unit.vPosition.x = 0;
	if (unit.vPosition.x < 0) unit.vPosition.x = _WINWIDTH;
	if (unit.vPosition.y > _WINHEIGHT) unit.vPosition.y = 0;
	if (unit.vPosition.y < 0) unit.vPosition.y = _WINHEIGHT;
};

bool CheckForCollisions(Particle& particle)
{
	Vector normal;
	Vector relativeVelocity;
	float normalSpeed;
	float J;
	Vector Fi;
	bool hasCollision = false;

	particle.vImpactForces.x = 0;
	particle.vImpactForces.y = 0;


	//Check for collision with obstacles
	float minDeltaPosition; 
	Vector deltaPosition; 
	float separation;

	for(auto& obstacle : Obstacles)
	{
		minDeltaPosition = particle.fRadius + obstacle.fRadius;
		deltaPosition = particle.vPosition - obstacle.vPosition;
		separation = deltaPosition.Magnitude() - minDeltaPosition;


		if(separation <= 0)
		{
			deltaPosition.Normalise();
			normal = deltaPosition;
			relativeVelocity = particle.vVelocity - obstacle.vVelocity;
			normalSpeed = relativeVelocity * normal;

			if(normalSpeed < 0.0)
			{
				J = - normalSpeed * (_RESTITUTION + 1) / ( 1/ (particle->fMass) + 1 / (obstacle->fMass) );
				Fi = normal;
				fi *= J / _TIMESTEP;
				particle.vImpactForces += Fi;

				p.vPosition -= normal * separation;
				hasCollision = true;
			}
		}
	}


	//Check for collision with ground
	if (particle.vPosition.y <= (_GROUND_PLANE + particle->fRadius))
	{
		normal.x = 0;
		normal.y = 1;
		relativeVelocity = particle.vVelocity;
		normalSpeed = relativeVelocity * normal;

		if (normalSpeed < 0.0)
		{
			// _RESTITUTION == elasticity of the floor. 
			J = - normalSpeed * (_RESTITUTION + 1) * particle.fMass;
			Fi = normal * J / _TIMESTEP;

			particle->vImpactForces += Fi;

			float dx = particle->vPreviousPosition.x - particle->vPosition.x;
			float dy = particle->vPreviousPosition.y - particle->vPosition.y;

			particle.vPosition.y = _GROUND_PLANE + particle.fRadius;
			particle.vPosition.x = (_GROUND_PLANE + particle.fRadius) * dx / dy + particle.vPreviousPosition.x;

			hasCollision = true;
		}
	}
	return hasCollision;
};

bool Initialize(void)
{

	GetRandomNumber(0, _WINWIDTH, true);

	for(auto& unit : Units)
	{
		unit.vPosition.x = GetRandomNumber( _WINWIDTH / 2 - _SPAWN_AREA_R * 2, _WINWIDTH / 2 + _SPAWN_AREA_R * 2, false)
		unit.vPosition.x = GetRandomNumber( _WINHEIGHT / 2 - _SPAWN_AREA_R * 2, _WINHEIGHT / 2 + _SPAWN_AREA_R * 2, false)
	}

	for(auto& obstacle : Obstacles)
	{
		obstacle.vPosition.x = GetRandomNumber(

			);
		obstacle.vPosition.x = GetRandomNumber(

			);
		obstacle.fRadius = _OBSTACLE_RADIUS;
		obstacle.fmass = 100;
	}

}