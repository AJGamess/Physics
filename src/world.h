#pragma once
#include "raylib.h"
#include "body.h"
#include "spring.h"
#include<vector>

class Scene;

using bodies_t = std::vector<Body*>;
using springs_t = std::vector<Spring*>;

class World
{
public:
	~World();

	void Initialize(Vector2 gravity = Vector2{ 0, -9.81f }, size_t poolSize = 30);

	Body* CreateBody(const Vector2& position, float size, const Color& color);
	Body* CreateBody(Body::Type type, const Vector2& position,  float mass, float size, const Color& color);
	void Step(float timestep);
	void Draw(const Scene& scene);

	void DestroyAll();

	std::vector<Body*> GetBodies() { return m_bodies; }

	Spring* CreateSpring(Body* bodyA, Body* bodyB, float restLength, float stiffness, float damping);

	inline static Vector2 gravity{ 0, -9.81f};
	inline static float gravitation = 0;
	inline static float springStiffnessMultiplier = 0;
	inline static bool simulate = false;

private:
	Vector2 m_gravity;
	bodies_t m_bodies;
	springs_t m_springs;
};

inline void f() {}