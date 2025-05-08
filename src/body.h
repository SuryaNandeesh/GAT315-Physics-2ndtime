#pragma once
#include "scene.h"
#include "raylib.h"
#include "raymath.h"

struct Body
{
public:
	Body() = default;
	Body(const Vector2& position, const Vector2& velocity, float size, const Color& color) :
		position{ position },
		velocity{ velocity },
		size{ size },
		color{ color }
	{
		// Initialize the body with the given parameters
	}

	void Step(float dt);
	void Draw(const Scene& scene);

public:
	Vector2 position;
	Vector2 velocity;
	float size;
	Color color;

	Body* next{ nullptr };
	Body* prev{ nullptr };
};