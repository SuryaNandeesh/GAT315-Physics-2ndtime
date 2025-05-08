#pragma once
#ifndef POLARSCENE_H
#define POLARSCENE_H

#include <string>
#include "scene.h"         // Base class
#include "raylib.h"        // For Color, Vector2

class PolarScene : public Scene {
public:
    PolarScene(const std::string& title, int width, int height, const Color& background = BLACK);
    ~PolarScene() override;

    void Initialize() override;
    void Update() override;
    void Draw() override;
    void DrawGUI() override;

    void BeginDraw() override;
    void EndDraw() override;

    void DrawGrid(float slices, float thickness, const Color& color);
    void DrawText(const std::string& text, const Vector2& world, int fontSize, Color color);
    void DrawCircle(const Vector2& world, float radius, Color color);
    void DrawLine(const Vector2& v1, const Vector2& v2, float thickness, Color color);
    void DrawPolarCurve();
    enum class CurveType
    {
        Archimedean,
        Cardioid,
        Limacon,
        Rose,
        User
    };

private:
    int m_width;
    int m_height;
    Color m_background{ BLACK };
    CurveType m_currentCurve{ CurveType::Archimedean };

    SceneCamera* m_camera;

};



#endif // POLARSCENE_H
