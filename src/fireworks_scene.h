#pragma once
#include "scene.h"
#include "world.h"

class FireworksScene : public Scene {
public:
    FireworksScene(const std::string& name, int width, int height);
    void Initialize() override;
    void Update() override;
    void Draw() override;
    void DrawGUI() override;

private:
    World m_world;
    void SpawnFirework(Vector2 position);
    void SpawnPatternA(Vector2 position);
    void SpawnPatternB(Vector2 position);
    void SpawnPatternC(Vector2 position);
};
