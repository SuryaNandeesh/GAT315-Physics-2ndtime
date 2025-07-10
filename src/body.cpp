#include "body.h"
#include "integrator.h"
#include "raymath.h"
#include <world.h>

void Body::Step(float dt) {
	if (type != Type::Dynamic) return;

	// Apply gravity and forces
	force += (World::gravity * gravityScale) * mass;
	acceleration = force * inverseMass;
	
	// Use semi-implicit Euler integration
	velocity += acceleration * dt;
	position += velocity * dt;
	velocity *= 1.0f / (1.0f + (damping * dt));
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