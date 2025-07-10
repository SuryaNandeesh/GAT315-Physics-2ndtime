#pragma once
#include "scene.h"
#include "world.h"
#include "body.h"
#include "raylib.h"
#include <vector>
#include <memory>

class AngryBirdsScene : public Scene
{
public:
    AngryBirdsScene(const std::string& title, int width, int height);
    ~AngryBirdsScene();

    void Initialize() override;
    void Update() override;
    void FixedUpdate() override;
    void BeginDraw() override;
    void Draw() override;
    void DrawGUI() override;
    void ResetGame();

private:
    void CreateSlingshot();
    void CreateStructures();
    void LaunchBird();
    void CheckCollisions();
    void SpawnNewBird();
    bool CheckWinCondition();
    void DrawWinScreen();

    std::unique_ptr<World> m_world;
    std::vector<Body*> m_birds;
    std::vector<Body*> m_structures;
    Body* m_slingshot;
    Body* m_currentBird;
    bool m_isDragging;
    Vector2 m_dragStart;
    Vector2 m_dragEnd;
    float m_score;
    float m_birdDelayTimer;
    int m_birdsRemaining;
    bool m_gameWon;
    const float BIRD_DELAY = 5.0f;
    const int MAX_BIRDS = 3;
}; 