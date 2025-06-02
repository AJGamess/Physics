#pragma once
#include "world.h"


struct Collision
{
	static void CreateContacts(const bodies_t& bodies, contacts_t& contacts);
	static void SeparateContacts(contacts_t& contacts);
	static bool Intersects(Body* bodyA, Body* bodyB);
};
