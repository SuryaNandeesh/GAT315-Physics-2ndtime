#include "world.h"
#include "body.h"
#include "collision.h"
#include "gui.h"
#include "gravitation.h"
#include "contact.h"

World::~World() {
    DestroyAll();
}

void World::Initialize(Vector2 gravity, size_t poolSize) {
    m_bodies.reserve(poolSize);
}

Body* World::CreateBody(const Vector2& position, float size, const Color& color) {
    Body* body = new Body(position, size, color);
    m_bodies.push_back(body);

    return body;
}

Body* World::CreateBody(const Vector2& position, float mass, float size, const Color& color) {
    Body* body = new Body(position, mass, size, color);
    m_bodies.push_back(body);

    return body;
}

Body* World::CreateBody(Body::Type type, const Vector2& position, float mass, float size, const Color& color) {
    Body* b = new Body(type, position, mass, size, color);
    m_bodies.push_back(b);
    return b;
}

Spring* World::CreateSpring(Body* bodyA, Body* bodyB, float restLength, float stiffness, float damping) {
    Spring* s = new Spring(bodyA, bodyB, restLength, stiffness, damping);
    m_springs.push_back(s);
    return s;
}

void World::Step(float timestep) {

    if (!simulate) return;

    if (gravitation > 0) ApplyGravitation(m_bodies, gravitation);

    for (auto spring : m_springs)
    {
        spring->ApplyForce(springStiffnessMultiplier);
    }

    // body integration
    for (auto body : m_bodies)
    {
        body->Step(timestep);
        body->ClearForce();
    }

    //contact solver
    for (int i = 0; i < 5; i++)
    {
        Collision::CreateContacts(m_bodies, m_contacts);
        Collision::SeparateContacts(m_contacts);
        Collision::ResolveContacts(m_contacts);
        m_contacts.clear();
    }
}

void World::Draw(Scene& scene) {
    for (auto b : m_bodies) {
        b->Draw(scene);
    }
    for (auto s : m_springs) {
        s->Draw(scene);
    }
}

void World::DestroyAll() {
    for (auto body : m_bodies) {
        delete body;
    }

    for (auto spring : m_springs) {
        delete spring;
    }

    m_bodies.clear();
    m_springs.clear();
    m_contacts.clear();
}