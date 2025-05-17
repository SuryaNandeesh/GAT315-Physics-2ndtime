#pragma once
#include <vector>
#include "raylib.h"
#include "body.h"

using bodies_t = std::vector<Body*>;

class World {
public:
    ~World();

    void Initialize(Vector2 gravity = { 0, -9.81f }, size_t poolSize = 30);
    Body* CreateBody(const Vector2& position, float size, const Color& color);
    void Step(float timestep);
    void Draw(const Scene& scene);
    void DestroyAll();

	bodies_t& GetBodies() { return m_bodies; }

    static Vector2 gravity;

private:
    //std::vector<Body*> m_bodies;
    bodies_t m_bodies;
};
