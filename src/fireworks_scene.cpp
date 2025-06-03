#include "fireworks_scene.h"
#include "raylib.h"
#include "body.h"
#include <cmath>

FireworksScene::FireworksScene(const std::string& name, int width, int height)
    : Scene(name, width, height)
{
}

void FireworksScene::Initialize() {
    m_world.Initialize({ 0, -98.1f }, 1000); // gravity and pool size
}

void FireworksScene::Update() {
	float dt = GetFrameTime();
    m_world.Step(dt);

    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        Vector2 position = GetMousePosition();
        SpawnFirework(position);
    }
}

void FireworksScene::FixedUpdate() {
	// No fixed update logic needed for fireworks
}

void FireworksScene::Draw() {
    m_world.Draw(*this);
}

void FireworksScene::DrawGUI() {
    m_world.Draw(*this);
}

void FireworksScene::SpawnFirework(Vector2 position) {
    int pattern = GetRandomValue(0, 2);
    switch (pattern) {
    case 0: SpawnPatternA(position); break;
    case 1: SpawnPatternB(position); break;
    case 2: SpawnPatternC(position); break;
    }
}

void FireworksScene::SpawnPatternA(Vector2 position) {
    for (int i = 0; i < 30; ++i) {
        float angle = i * (2 * PI / 30);
        Vector2 vel = { cosf(angle) * 100, sinf(angle) * 100 };
        Body* b = m_world.CreateBody(position, 2, RED);
        b->velocity = vel;
        b->damping = 0.98f + GetRandomValue(-2, 2) / 100.0f;  // Slight variation in damping
    }
}

void FireworksScene::SpawnPatternB(Vector2 position) {
    for (int i = 0; i < 20; ++i) {
        Vector2 vel = { GetRandomValue(-100, 100), GetRandomValue(50, 150) };
        Body* b = m_world.CreateBody(position, 2, BLUE);
        b->velocity = vel;
        b->damping = 0.95f;
    }
}

void FireworksScene::SpawnPatternC(Vector2 position) {
    for (int i = 0; i < 40; ++i) {
        float angle = GetRandomValue(0, 360) * DEG2RAD;
        float speed = GetRandomValue(50, 150);
        Vector2 vel = { cosf(angle) * speed, sinf(angle) * speed };
        Body* b = m_world.CreateBody(position, 2, Color{(unsigned char)GetRandomValue(100, 255), (unsigned char)GetRandomValue(100, 255), (unsigned char)GetRandomValue(100, 255), 255 });
        b->velocity = vel;
        b->damping = 0.97f;
    }
}
