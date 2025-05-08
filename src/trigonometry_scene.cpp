#include "trigonometry_scene.h"
//#include "raymath.h"

void TrigonometryScene::Initialize()
{
	m_camera = new SceneCamera(Vector2{ static_cast<float>(m_width) / 2, m_height / 2.0f });
}

void TrigonometryScene::Update()
{
}

float DegToRad(float degrees)
{
	return degrees * (PI / 180.0f);
}

float RadToDeg(float radians)
{
	return radians * (180/PI);
}

/*
float Vector2Length(const Vector2& v) {
	return sqrtf(v.x * v.x + v.y * v.y);
}

Vector2 Vector2Normalize(const Vector2& v) {
	float l = Vector2Length(v);
	if (l == 0) return { 0, 0 };
	return { v.x / l, v.y / l };
}
*/

void TrigonometryScene::Draw()
{
	m_camera->BeginMode();

	DrawGrid(10, 5, WHITE);
	DrawCircleV(m_camera->WorldToScreen({ 0, 0 }), 10, RED); // 10-pixel radius
	//DrawCircleV(m_camera->WorldToScreen(Vector2{ 0, 0 }), m_camera->WorldToScreen(1), RED);
	//DrawCircle(Vector2{ 0, 0 }, 1, RED);
	float radius = 3;
	float rate = 0.2f;
	float time = (float)GetTime() * rate;

	int steps = 50;
	for (int i = 0; i < steps; i++) {
		float theta = (i / (float)steps); //0 - 1
		float x = cosf(theta) * radius;
		float y = sinf(theta) * radius;
		DrawCircle(Vector2{ x, y }, 0.25, DARKGREEN);
	}

	for (float x = -10.0f; x < 10.0f; x += 0.2f) {
		float theta = (x / 20) * (2 * PI); // 0-1
		float c = cosf(theta) * radius;
		float s = sinf(theta) * radius;

		DrawCircle(Vector2{ c, s }, 0.25, BLUE);
		DrawCircle(Vector2{ x, s }, 0.25, ORANGE);
	}

	float theta = time;
	float x = cosf(theta) * radius;
	float y = sinf(theta) * radius;

	float angle = atan2f(y, x);
	//for getting an angle from a position

	m_camera->EndMode();
}

void TrigonometryScene::DrawGUI()
{
}
