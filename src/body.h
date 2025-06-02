#pragma once
#include "scene.h"
#include "raylib.h"
#include "raymath.h"

struct Body
{
public:
	enum class Type {
		Dynamic,
		Kinematic,
		Static
	};

	enum class ForceMode {
		Force,
		Impulse,
		Velocity
	};

public:
	Body() = default;
	Body(const Vector2& position, const Vector2& velocity, float mass, float size, const Color& color) :
		position{ position },
		velocity{ velocity },
		mass{ mass },
		size{ size },
		color{ color }
	{
		// Initialize the body with the given parameters
	}

	Body(const Vector2& position, float mass, float size, const Color& color) :
		position{ position },
		mass{ mass },
		size{ size },
		color{ color }
	{
	}
	
	Body(const Vector2& position, float size, const Color& color) :
		position{ position },
		size{ size },
		color{ color }
	{
	}

	Body(Type type, const Vector2& position, float mass, float size, const Color& color) :
		type{ type },
		position{ position },
		mass{ mass },
		size{ size },
		color{ color }
	{
		inverseMass = (type == Type::Dynamic && mass != 0.0f) ? 1.0f / mass : 0.0f;
	}

	void Step(float dt);
	void Draw(const Scene& scene);

	//void ApplyForce(const Vector2& force);
	void ApplyForce(const Vector2& force, ForceMode forcemode = ForceMode::Force);
	void ClearForce() { force = { 0, 0 }; }

public:
	Vector2 position{ 0, 0 };
	Vector2 lastPosition;
	Vector2 velocity{ 0, 0 };
	Vector2 acceleration{ 0, 0 };
	Vector2 force{ 0, 0 };

	float mass{ 1 };
	float inverseMass{ 1 };

	float gravityScale{ 1 };
	float restitution{ 0.5f }; // Bounciness, 0 = no bounce, 1 = full bounce

	float size = 1;
	float damping = 0.99f;

	Color color = WHITE;

	Type type{ Type::Dynamic };

	Body* next{ nullptr };
	Body* prev{ nullptr };
};