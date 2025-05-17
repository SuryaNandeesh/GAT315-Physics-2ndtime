#pragma once
#include "scene.h"
#include "raylib.h"
#include "raymath.h"

struct Body
{
public:
	enum class Type {
		Static,
		Kinematic,
		Dynamic
	};

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

	Body(const Vector2& position, float size, const Color& color) :
		position{ position },
		velocity{ 0, 0 }, // default to stationary
		size{ size },
		color{ color }
	{
	}
	
	Body(Type type, const Vector2& position, float mass, float size, const Color& color) :
		type{ type },
		position{ position },
		mass{ mass },
		velocity{ 0, 0 }, // default to stationary
		size{ size },
		color{ color }
	{
		inverseMass = (type == Type::Dynamic && mass != 0.0f) ? 1.0f / mass : 0.0f;
	}	

	void Step(float dt);
	void Draw(const Scene& scene);

	void ApplyForce(const Vector2& force);

public:
	Vector2 position{ 0, 0 };
	Vector2 lastPosition;
	Vector2 velocity{ 0, 0 };
	float size;
	Color color;
	float damping = 0.99f;
	float mass{ 1 };
	Vector2 acceleration{ 0, 0 };
	Vector2 force{ 0, 0 };
	float inverseMass{ 1 };
	float gravityScale;

	Type type{ Type::Dynamic };

	Body* next{ nullptr };
	Body* prev{ nullptr };
};