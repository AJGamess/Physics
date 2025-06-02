#include "spring.h"
#include "body.h"
#include "raymath.h"


void Spring::ApplyForce(float kMultiplier)
{
    // direction = bodyA <——— bodyB
    Vector2 direction = bodyA->position - bodyB->position;
    float lengthSqr = Vector2LengthSqr(direction);
    if (lengthSqr <= EPSILON) return;

    // calculate spring force
    float length = sqrtf(lengthSqr);
    float displacement = length - restLength; // current length - resting length (>0 stretched, <0 compressed)
    float forceMagnitude = -(k * kMultiplier) * displacement; // f = -kx <- Hooke's Law

    Vector2 ndirection = direction / length;
    Vector2 force = ndirection * forceMagnitude;

    // damp spring force to prevent oscillation
    Vector2 dV = bodyA->velocity - bodyB->velocity;
    float dampFactor = Vector2DotProduct(dV, ndirection) * damping;
    Vector2 dampingForce = ndirection * dampFactor;

    force -= dampingForce;

    // apply spring force
    bodyA->ApplyForce(force);
    bodyB->ApplyForce(Vector2Negate(force));
}

void Spring::ApplyForce(const Vector2& position, Body& body, float restLength, float k)
{
    // direction = position <——— bodyB
    Vector2 direction = position - body.position;
    float lengthSqr = Vector2LengthSqr(direction);
    if (lengthSqr <= EPSILON) return;

    // calculate spring force
    float length = sqrtf(lengthSqr);
    float displacement = length - restLength; // current length - resting length (>0 stretched, <0 compressed)
    float forceMagnitude = -k * displacement; // f = -kx <- Hooke's Law

    Vector2 ndirection = direction / length;
    Vector2 force = ndirection * forceMagnitude;

    body.ApplyForce(Vector2Negate(force));
}

void Spring::Draw(const Scene& scene)
{
	scene.DrawLine(bodyA->position, bodyB->position, 3, WHITE);
}
