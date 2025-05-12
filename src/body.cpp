#include "body.h"
#include "raymath.h"
void Body::Step(float dt)
{
	position += velocity * dt;
	velocity *= 1.0f / (1.0f + (damping * dt));
}

void Body::Draw(const Scene& scene)
{
	scene.DrawCircle(position, size, color);
}
