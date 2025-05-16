#include "gravitation.h"
#include "raymath.h"

void ApplyGravitation(bodies_t& bodies, float strength)
{
	for (int i = 0; i < bodies.size(); i++) {
		Body* bodyA = bodies[i];
		for (int j = i + 1; j < bodies.size(); j++)
		{
			Body* bodyB = bodies[j];

            // STEP 1: Find the direction vector from bodyB to bodyA
            // Vector2 direction = bodyA position - bodyB position;
            Vector2 direction = bodyA->position - bodyB->position;

            // STEP 2: Get the distance between the two bodies
            // float distance = length of direction vector;
			float distance = Vector2Length(direction);

            // STEP 3: Clamp the distance to a minimum value to avoid extreme forces
            // distance = max(distance, 1);
			distance = fmax(distance, 1.0f);

            // STEP 4: Calculate gravitational force magnitude using:
            // forceMagnitude = (bodyA mass * bodyB mass / (distance * distance)) * strength;
			float forceMagnitude = (bodyA->mass * bodyB->mass / (distance * distance)) * strength;

            // STEP 5: Normalize the direction vector and scale it by the force magnitude
            // Vector2 forceVector = normalized direction * forceMagnitude;

			Vector2 forceVector = Vector2Scale(Vector2Normalize(direction), forceMagnitude);

            // STEP 6: Apply the force to both bodies (equal and opposite)
            // bodyA.ApplyForce(-forceVector);
            // bodyB.ApplyForce(forceVector);

			bodyA->ApplyForce(Vector2Negate(forceVector));
			bodyB->ApplyForce(forceVector);
		}
	}
}
