#include "world.h"
#include "body.h"

Vector2 World::gravity = { 0, -9.81f };

World::~World() {

}

void World::Initialize(Vector2 gravity, size_t poolSize) {
    World::gravity = gravity;
    m_bodies.reserve(poolSize);
}

Body* World::CreateBody(const Vector2& position, float size, const Color& color) {
    Body* b = new Body(position, size, color);
    m_bodies.push_back(b);
    return b;
}

void World::Step(float timestep) {
    for (Body* b : m_bodies) {
        b->Step(timestep);
    }
}

void World::Draw(const Scene& scene) {
    for (Body* b : m_bodies) {
        b->Draw(scene);
    }
}

void World::DestroyAll() {
    for (Body* b : m_bodies) delete b;
    m_bodies.clear();
}