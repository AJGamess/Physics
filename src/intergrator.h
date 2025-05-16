#pragma once
#include "body.h"
#include "raymath.h"

inline void ExplictIntergrator(Body& body, float timestep) 
{
	body.position += body.velocity * timestep;
	body.velocity += body.acceleration * timestep;
	body.velocity *= 1.0f / (1.0f + (body.damping * timestep));

}

inline void SemiExplictIntergrator(Body& body, float timestep)
{
	body.velocity += body.acceleration * timestep;
	body.position += body.velocity * timestep;
	body.velocity *= 1.0f / (1.0f + (body.damping * timestep));

}
