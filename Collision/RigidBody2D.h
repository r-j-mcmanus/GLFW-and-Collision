class RigidBody2D()
{
public:
	float fMass;
	float fInertia;
	float fInertiaInversel

	Vector vPosition;
	Vector vVelocity;
	Vector vVelocityBody;
	Vector vAngularVelocity;

	float fSpeed;
	float fOrientation;

	Vector vForces; 
	Vector vMoment; 

	float ThrustForce; 
	Vector PThrust, SThrust;

	float fWideth; 
	float fLength; 
	float fHeight; 

	Vector CD;
	Vector CT; 
	Vector CPT; 
	Vector CST;

	float ProjectedArea; 

	RigidBody2D(void);
	void CalcLoads(void);
	void UpdateBodyEuler(double dt);
	void ModulateThrust(bool up); 
}