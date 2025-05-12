#pragma once
#include "raylib.h"
#include "scene.h"
struct Body
{
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

	void Step(float dt);
	void Draw(const Scene& scene);

	Vector2 position{0};
	Vector2 velocity{0};

	float size;
	float damping{ 0.1f };
	Color color = WHITE;

	Body* next{nullptr};
	Body* prev{nullptr};
};