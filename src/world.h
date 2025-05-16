#pragma once
#include "raylib.h"
#include "body.h"
#include<vector>

class Scene;

using bodies_t = std::vector<Body*>;

class World
{
public:
	~World();

	void Initialize(Vector2 gravity = Vector2{ 0, -9.81f }, size_t poolSize = 30);

	Body* CreateBody(const Vector2& position, float size, const Color& color);
	void Step(float timestep);
	void Draw(const Scene& scene);

	void DestroyAll();

	std::vector<Body*> GetBodies() { return m_bodies; }

	static Vector2 gravity;

private:
	Vector2 m_gravity;
	bodies_t m_bodies;
};