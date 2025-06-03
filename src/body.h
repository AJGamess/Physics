#pragma once
#include "raylib.h"
#include "scene.h"
#include "aabb.h"
struct Body
{
public:
	enum class Type 
	{
		Dynamic,
		Kinematic,
		Static
	};

	enum class ForceMode 
	{
		Force,
		Impulse,
		Velocity
	};
public:
	Body() = default;	
	Body(const Vector2& position, const Vector2& velocity, float size, const Color& color) :
		position{ position },
		velocity{ velocity },
		size{ size },
		color{ color }
	{}
	Body(const Vector2& position, float size, const Color& color) :
		position{ position },
		size{ size },
		color{ color }
	{
	}
	Body(Type type, const Vector2& position, float mass, float size, const Color& color):
		type{ type },
		position{ position },
		mass{ mass },
		size{ size },
		color{ color }
	{
		invMass = (type == Type::Dynamic && mass != 0) ? 1 / mass : 0;
	}

	void Step(float dt);
	void Draw(const Scene& scene);

	void ApplyForce(const Vector2& force, ForceMode forceMode = ForceMode::Force);

	AABB GetAABB() const { return AABB{ position, { size * 2, size * 2 } }; }

	void ClearForce()
	{
		force = Vector2{ 0, 0 };
	}
public:

	Vector2 position{0};
	Vector2 velocity{0};
	Vector2 force{0};
	Vector2 acceleration{0};

	float mass{ 1 };
	float invMass{ 1 };

	float gravityScale{1};
	float restitution{ 1 };

	float size;
	float damping{ 0.1f };
	Color color = WHITE;

	Type type{ Type::Dynamic };

	Body* next{nullptr};
	Body* prev{nullptr};
};