#include "gravitation.h"

void ApplyGravitation(bodies_t& bodies, float strength) {
	for (int i = 0; i < bodies.size(); i++) {
		Body* bodyA = bodies[i];
		for (int j = 0; j < bodies.size(); j++) {
			Body* bodyB = bodies[j];
			if (bodyA == bodyB) continue;  // Skip self-interaction
		}
	}
}