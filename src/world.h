#pragma once
#include<vector>
#include "raylib.h"
struct Body;
class Scene;

class World
{
public:
	~World();

	void Initialize(Vector2 gravity = Vector2{ 0, -9.81f }, size_t poolSize = 30);

	Body* CreateBody(const Vector2& position, float size, const Color& color);
	void Step(float timestep);
	void Draw(const Scene& scene);

	void DestroyAll();
private:
	Vector2 m_gravity;
	std::vector<Body*> m_bodies;
};