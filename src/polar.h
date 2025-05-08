#pragma once
#include "scene.h"
#include <raymath.h>
struct Polar
{
public:
	Polar() = default;
	Polar(float angle, float radius) :
		angle{ angle },
		radius{ radius }
	{
	}

	Polar(const Vector2& v) :
		angle{ atan2f(v.y, v.x) },  //!!get angle from Vector2 !!},
		radius{ Vector2Length(v) } //!!get vector length !!}
	{
	}

	Polar& operator = (const Vector2& v)
	{
		angle = atan2f(v.x, v.y);   //!!get angle from Vector2 !!;
		radius = Vector2Length(v); //!!get vector length !!;

		return *this;
	}

	operator Vector2() const
	{
		Vector2 v;
		v.x = static_cast<float>(cos(angle) * radius);  //!!get x position using cos(angle)* radius !!;
		v.y = static_cast<float>(sin(angle) * radius);  //!!get y position using sin(angle)* radius !!;

		return v;
	}

public:
	float angle{ 0 };
	float radius{ 0 };
};