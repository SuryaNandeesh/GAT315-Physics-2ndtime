#pragma once
#include "body.h"
#include "spring.h"
#include "contact.h"
#include "raylib.h"
#include <vector>

using bodies_t = std::vector<Body*>;
using springs_t = std::vector<Spring*>;
using contacts_t = std::vector<Contact>;

class World {
public:
    ~World();

    void Initialize(Vector2 gravity = { 0, -9.81f }, size_t poolSize = 30);
    void DestroyAll();

    void Step(float timestep);
    void Draw(Scene& scene);

    //BODY
    Body* CreateBody(const Vector2& position, float size, const Color& color);
    Body* CreateBody(const Vector2& position, float mass, float size, const Color& color);
    Body* CreateBody(Body::Type type, const Vector2& position, float mass, float size, const Color& color);
	bodies_t& GetBodies() { return m_bodies; }

    //Spring
	Spring* CreateSpring(Body* bodyA, Body* bodyB, float restLength, float stiffness, float damping);
    
    inline static Vector2 gravity;
	inline static float gravitation = 0.0f;
	inline static float springStiffnessMultiplier = 1.0f;
    inline static bool simulate = true;

private:
    //std::vector<Body*> m_bodies;
    bodies_t m_bodies;
	springs_t m_springs;
	contacts_t m_contacts;
};
