#include "spring.h"
#include "body.h"
#include "raymath.h"


void Spring::ApplyForce(float damping, float kMultiplier)
{
	//direction = bodyA <---- bodyB
	Vector2 direction = bodyA->position - bodyB->position;
	float lengthSqr = Vector2LengthSqr(direction);
	if (lengthSqr <= EPSILON) return; // Avoid division by zero

	//calculate spring force
	float length = sqrt(lengthSqr);
	float displacement = length - restLength; // current length - resting length (>0 = stretched, < 0 = compressed)
	
	// Hooke's Law: F = -kx, where k is the spring constant and x is the displacement from the rest length
	float forceMagnitude = -(k * kMultiplier) * displacement;

	//normalize direction and calc spring force vector
	Vector2 ndirection = direction/length;
	Vector2 force = ndirection * forceMagnitude;

	//damp spring force to prevent oscillation
	Vector2 dv = bodyA->velocity - bodyB->velocity;
	float dampFactor = Vector2DotProduct(dv, ndirection) * damping;
	Vector2 dampingForce = ndirection * dampFactor;

	force -= dampingForce;

	//apply spring force
	bodyA->ApplyForce(force);
	bodyB->ApplyForce(Vector2Negate(force));
}

void Spring::ApplyForce(const Vector2& position, Body& body, float restLength, float k) {

	//direction = bodyA <---- bodyB
	Vector2 direction = position - body.position;
	float lengthSquared = Vector2LengthSqr(direction);

	if (lengthSquared < EPSILON) return;

	// spring displacenment
	float length = sqrtf(lengthSquared);
	float displacement = length - restLength;  // Stretching if > 0, compressed if < 0

	// apply Hooke's Law: F = -k * x
	float forceMagnitude = -k * displacement;

	// norm direction calc spring force vector
	Vector2 normalizedDirection = direction / length;
	Vector2 springForce = normalizedDirection * forceMagnitude;

	Vector2 totalForce = springForce;

	// op forces to body
	body.ApplyForce(Vector2Negate(totalForce));
}

void Spring::Draw(Scene& scene)
{
	scene.DrawLine(bodyA->position, bodyB->position, 2.0f, WHITE);
}
