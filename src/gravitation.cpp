#include "gravitation.h"
#include "raymath.h"
#include "body.h"

void ApplyGravitation(bodies_t& bodies, float strength)
{
	for (int i = 0; i < bodies.size(); i++) {
		Body* bodyA = bodies[i];
		for (int j = i + 1; j < bodies.size(); j++) {
			Body* bodyB = bodies[j];

			//find the direction vector from bodyB to bodyA
			Vector2 direction = bodyA->position - bodyB->position;

			// Get the distance between the two bodies
			float distance = Vector2Length(direction);

			//clamp the distance to a minimum value to avoid extreme forces
			distance = fmaxf(distance, 1.0f);

			//Calculate gravitational force magnitude using:
			float forceMagnitude = ((bodyA->mass * bodyB->mass) / (distance * distance)) * strength;

			//Normalize the direction vector and scale it by the force magnitude
			Vector2 forceVector = Vector2Normalize(direction) * forceMagnitude;

			//Apply the force to both bodies (equal and opposite)
			bodyA->ApplyForce(Vector2Negate(forceVector));
			bodyB->ApplyForce(forceVector);
		}
	}
}