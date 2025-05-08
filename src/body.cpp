#include "body.h"
#include "raymath.h"

void Body::Step(float dt) {
	// Update the position based on velocity and time step
	position = Vector2Add(position, Vector2Scale(velocity, dt));

}

void Body::Draw(const Scene& scene)
{
}
