#include "body.h"
#include "raymath.h"
#include "intergrator.h"
#include "world.h"

void Body::Step(float dt)
{
	if (type != Type::Dynamic) return;

	//Apply gravity
	force += (World::gravity * gravityScale) * mass;
	//compute acceleration
	acceleration = (force * invMass);

	SemiExplictIntergrator(*this, dt);

}

void Body::Draw(const Scene& scene)
{
	scene.DrawCircle(position, size, color);
}

void Body::ApplyForce(const Vector2& force)
{
	this->force += force;
}
