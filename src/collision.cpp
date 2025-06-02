#include "collision.h"
#include "raymath.h"
#include "mathutils.h"
#include "contact.h"

void Collision::CreateContacts(const bodies_t& bodies, contacts_t& contacts)
{
	for (int i = 0; i < bodies.size(); i++)
	{
		Body* bodyA = bodies[i];
		for (int j = i + 1; j < bodies.size(); j++)
		{
			Body* bodyB = bodies[j];
			if (bodyA->type != Body::Type::Dynamic && bodyB->type != Body::Type::Dynamic) continue;

			if (Intersects(bodyA, bodyB))
			{
				Contact* contact = new Contact{};
				contact->bodyA = bodyA;
				contact->bodyB = bodyB;

				//<direction vector from bodyB to bodyA>;
				Vector2 direction = bodyA->position - bodyB->position;
				//<get Vector2 Length Squared of direction>;
				float distanceSqr = Vector2LengthSqr(direction);
				if (distanceSqr <= EPSILON)
				{
					direction = Vector2{ randomf(-0.05f, 0.05f), randomf(-0.05f, 0.05f) };
					distanceSqr = Vector2LengthSqr(direction);
				}

				//<get distance from squared distance>;
				float distance = sqrtf(distanceSqr);
				//get size of bodyA and bodyB
				float radius = bodyA->size + bodyB->size;
				//<calculate penetration depth, see note above>;
				contact->depth = (radius - distance);
				//<normalize direction, can use normalize function or direction / distance>;
				contact->normal = direction / distance;
				//<get average restitution of both bodies>;
				contact->restitution = (bodyA->restitution + bodyB->restitution) * 0.5f;

				contacts.push_back(contact);
			}
		}
	}
}

void Collision::SeparateContacts(contacts_t& contacts)
{
	for (auto contact : contacts)
	{
		//<add inverse mass of both contact bodies>;
		float totalInverseMass = (contact->bodyA->invMass + contact->bodyB->invMass);
		Vector2 separation = contact->normal * (contact->depth / totalInverseMass);
		//<contact bodyA position + (separation * contact bodyA inverse mass)>;
		contact->bodyA->position = contact->bodyA->position + (separation * contact->bodyA->invMass);
		//<contact bodyB position - (separation * contact bodyB inverse mass)>;
		contact->bodyB->position = contact->bodyB->position - (separation * contact->bodyB->invMass);
	}
}

bool Collision::Intersects(Body* bodyA, Body* bodyB)
{
	//<get distance between bodyA and bodyB, use Vector2Distance>
	float distance = Vector2Distance(bodyA->position, bodyB->position);
	//<add size of bodyA and BodyB>
	float radius = bodyA->size + bodyB->size;

	return (distance <= radius);
}