#include "scene.h"
#include "polar.h"
#include "polarscene.h"
#include "rlgl.h"
#include <vector>

PolarScene::PolarScene(const std::string& title, int width, int height, const Color& background): Scene(title, width, height), // Call base class constructor here!
	m_width{ width },
	m_height{ height },
	m_background{ background }
{}

PolarScene::~PolarScene()
{
    delete m_camera;
}

void PolarScene::Initialize()
{
    Vector2 offset = { m_width / 2.0f, m_height / 2.0f };
    m_camera = new SceneCamera(offset);

    m_camera->SetPPU(1000);
    m_camera->SetSize(100.0f);
    m_camera->GetCamera().target = { 0.0f, 0.0f };
    m_currentCurve = CurveType::Archimedean;
}

void PolarScene::Update()
{
    if (IsKeyPressed(KEY_ONE))  m_currentCurve = CurveType::Archimedean;
    if (IsKeyPressed(KEY_TWO))  m_currentCurve = CurveType::Cardioid;
    if (IsKeyPressed(KEY_THREE)) m_currentCurve = CurveType::Limacon;
    if (IsKeyPressed(KEY_FOUR))  m_currentCurve = CurveType::Rose;
    if (IsKeyPressed(KEY_FIVE))  m_currentCurve = CurveType::User;
}


void PolarScene::Draw()
{
    if (!m_camera) {
        TraceLog(LOG_ERROR, "Camera is null!");
        return;
    }

	BeginDraw();

    m_camera->BeginMode();

	DrawGrid(10.0f, 1.0f, DARKGRAY);
    DrawPolarCurve();

    m_camera->EndMode();

	EndDraw();
}

void PolarScene::DrawGUI()
{
	// GUI elements (if any)
}

void PolarScene::BeginDraw()
{
	BeginDrawing();
	ClearBackground(m_background);
}

void PolarScene::EndDraw()
{
	EndDrawing();
}

void PolarScene::DrawGrid(float slices, float thickness, const Color& color)
{
	for (float i = -slices; i <= slices; i++)
	{
		DrawLineEx(m_camera->WorldToScreen(Vector2{ -slices, i }), m_camera->WorldToScreen(Vector2{ slices, i }), thickness, color);
		DrawLineEx(m_camera->WorldToScreen(Vector2{ i, -slices }), m_camera->WorldToScreen(Vector2{ i, slices }), thickness, color);
	}
}

void PolarScene::DrawText(const std::string& text, const Vector2& world, int fontSize, Color color)
{
	Vector2 screen = m_camera->WorldToScreen(world);

	rlPushMatrix();
	rlTranslatef(screen.x, screen.y, 0);
	rlScalef(1, -1, 1);  // flip back so text is upright
	::DrawText(text.c_str(), 0, 0, fontSize, color);
	rlPopMatrix();
}

void PolarScene::DrawCircle(const Vector2& world, float radius, Color color)
{
	DrawCircleV(m_camera->WorldToScreen(world), m_camera->WorldToScreen(radius), color);
}

void PolarScene::DrawLine(const Vector2& v1, const Vector2& v2, float thickness, Color color)
{
	DrawLineEx(m_camera->WorldToScreen(v1), m_camera->WorldToScreen(v2), thickness, color);
}

void PolarScene::DrawPolarCurve()
{
    constexpr float pi = 3.1415926535f;
    constexpr float step = 0.01f; // Smaller step = smoother curve

    std::vector<Vector2> points;

    for (float theta = 0; theta < 2 * pi * 8; theta += step) // Go several loops for spirals or petals
    {
        float r = 0;

        switch (m_currentCurve)
        {
        case CurveType::Archimedean: {
            float a = 0.0f;
            float b = 10.0f;
            r = a + b * theta;
            break;
        }
        case CurveType::Cardioid: {
            float a = 50.0f;
            r = a * (1 + cosf(theta));
            break;
        }
        case CurveType::Limacon: {
            float a = 40.0f, b = 60.0f;
            r = a + b * cosf(theta);
            break;
        }
        case CurveType::Rose: {
            float a = 75.0f;
            int k = 4;
            r = a * sinf(k * theta);
            break;
        }
        case CurveType::User: {
            // A variation of a spiral with cosine distortion
            r = 10 * theta + 30 * sinf(5 * theta);
            break;
        }
        }

        // Polar to Cartesian conversion
        float x = r * cosf(theta);
        float y = r * sinf(theta);

        Vector2 world = { x, y };
        points.push_back(world);
    }

    // Draw connected points
    for (size_t i = 1; i < points.size(); ++i)
    {
        unsigned char r = static_cast<unsigned char>(((i + 10) * 10) % 255);
        unsigned char g = 0;
        unsigned char b = static_cast<unsigned char>(255 - (i % 255));
        unsigned char a = 255;

        Color color = Color{ r, g, b, a };
        DrawLine(points[i - 1], points[i], 200.0f, color);  // current thickness = 25
    }
}