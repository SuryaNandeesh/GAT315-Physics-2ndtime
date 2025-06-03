#include "body.h"
#include "integrator.h"
#include "raymath.h"
#include <world.h>

void Body::Step(float dt) {
	// Update the position based on velocity and time step
	//position = Vector2Add(position, Vector2Scale(velocity, dt));

	if (type != Type::Dynamic) return;

	force += (World::gravity * gravityScale)* mass;  // Reset acceleration to gravity
	acceleration = (force * inverseMass);
	velocity += acceleration * dt;

	position += velocity * dt;
	velocity *= 1.0f / (1.0f + (damping * dt));
	velocity += World::gravity * dt;

	SemiImplicitIntegrator(*this, dt);
}

void Body::Draw(const Scene& scene)
{
	// Draw the particle trail if it's not the first frame
	//if (lastPosition.x != 0 && lastPosition.y != 0) {
	//	DrawLineV(lastPosition, position, color);  // Draw a line from the last position to the current one
	//}
	// Draw the particle itself
	scene.DrawCircle(position, size, color);  // Draw a circle at the current position
	//DrawCircleV(position, size, color);  // Draw a circle for the firework particle
}

void Body::ApplyForce(const Vector2& force, ForceMode forceMode) {
	switch (forceMode) {
	case Body::ForceMode::Force:
		this->force += force;
		break;
	case Body::ForceMode::Impulse:
		this->velocity += force * inverseMass;
		break;
	case Body::ForceMode::Velocity:
		this->velocity += force;
		break;
	default:
		break;
	}

}