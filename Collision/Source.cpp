
#include <iostream>
#include "Particle.h"

const float _RENDER_FRAME_COUNT = 0.1f;
const int _MAX_NUM_UNITS = 3;
const float _GROUND_PLANE = 0.0f;
const float _RESTITUTION = 1.0f;
const float _TIMESTEP = 0.1f;
const int FrameCounter = 0;
const int _NUM_OBSTACLES = 5;

Particle Units[_MAX_NUM_UNITS];
Particle Obstacles[_MAX_NUM_UNITS];

int main()
{
	std::cout << "Hello" << std::endl;

	auto point = MyPoint();

	std::cout << "mass " << point.getPosition() << std::endl;
	std::cout << "velocity " << *point.getVelocity() << std::endl;
	std::cout << "Hello " << *point.getMass() << std::endl;

	return 0;
};
