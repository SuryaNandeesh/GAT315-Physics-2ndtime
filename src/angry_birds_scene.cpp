#include "angry_birds_scene.h"
#include "world.h"
#include "raylib.h"
#include <cmath>

AngryBirdsScene::AngryBirdsScene(const std::string& title, int width, int height)
    : Scene(title, width, height, SKYBLUE)
{
    m_world = nullptr;
    m_slingshot = nullptr;
    m_currentBird = nullptr;
    m_isDragging = false;
    m_dragStart = Vector2{0.0f, 0.0f};
    m_dragEnd = Vector2{0.0f, 0.0f};
    m_score = 0.0f;
    m_birdDelayTimer = 0.0f;
    m_birdsRemaining = MAX_BIRDS;
    m_gameWon = false;
    
    // Initialize camera
    m_camera = new SceneCamera(Vector2{static_cast<float>(width) / 2.0f, static_cast<float>(height) / 2.0f});
}

AngryBirdsScene::~AngryBirdsScene()
{
    if (m_world)
    {
        m_world->DestroyAll();
    }

    // Clean up all bodies
    for (auto* bird : m_birds)
    {
        delete bird;
    }
    m_birds.clear();

    for (auto* structure : m_structures)
    {
        delete structure;
    }
    m_structures.clear();

    if (m_slingshot)
    {
        delete m_slingshot;
    }
}

void AngryBirdsScene::Initialize()
{
    // Initialize world with strong gravity for better arcs
    m_world = std::make_unique<World>();
    m_world->Initialize(Vector2{ 0.0f, 50.0f });
    
    // Reset game state
    m_score = 0.0f;
    m_isDragging = false;
    m_dragStart = Vector2{0.0f, 0.0f};
    m_dragEnd = Vector2{0.0f, 0.0f};
    m_birdDelayTimer = 0.0f;
    m_birdsRemaining = MAX_BIRDS;
    m_gameWon = false;
    m_currentBird = nullptr;
    
    // Create game elements
    CreateSlingshot();
    CreateStructures();
    SpawnNewBird();
}

void AngryBirdsScene::CreateSlingshot()
{
    // Create slingshot base (static body)
    m_slingshot = m_world->CreateBody(Body::Type::Static, Vector2{ 200.0f, 500.0f }, 1.0f, 10.0f, BROWN);

    // Create initial bird
    m_currentBird = m_world->CreateBody(Body::Type::Dynamic, Vector2{ 200.0f, 400.0f }, 1.0f, 10.0f, RED);
    m_currentBird->restitution = 0.6f; // Make birds bouncy
    m_currentBird->gravityScale = 0.0f; // Keep gravity off until launched
    m_currentBird->damping = 0.0f; // Remove damping
    m_birds.push_back(m_currentBird);
}

void AngryBirdsScene::CreateStructures()
{
    // Create some basic structures (boxes and circles)
    float baseX = 800.0f;
    float baseY = 500.0f;

    // Base platform (static)
    Body* platform = m_world->CreateBody(Body::Type::Static, Vector2{ baseX, baseY + 50.0f }, 1.0f, 100.0f, GREEN);
    m_structures.push_back(platform);

    // Create a more complex structure
    // Bottom row
    for (int i = 0; i < 3; i++)
    {
        Body* box = m_world->CreateBody(Body::Type::Dynamic, Vector2{ baseX - 40.0f + i * 40.0f, baseY }, 1.0f, 20.0f, GREEN);
        box->restitution = 0.3f;
        box->gravityScale = 1.0f;
        box->damping = 0.0f; // Remove damping
        m_structures.push_back(box);
    }

    // Middle row
    for (int i = 0; i < 2; i++)
    {
        Body* box = m_world->CreateBody(Body::Type::Dynamic, Vector2{ baseX - 20.0f + i * 40.0f, baseY - 40.0f }, 1.0f, 20.0f, GREEN);
        box->restitution = 0.3f;
        box->gravityScale = 1.0f;
        box->damping = 0.0f; // Remove damping
        m_structures.push_back(box);
    }

    // Top piece
    Body* top = m_world->CreateBody(Body::Type::Dynamic, Vector2{ baseX, baseY - 80.0f }, 1.0f, 20.0f, GREEN);
    top->restitution = 0.3f;
    top->gravityScale = 1.0f;
    top->damping = 0.0f; // Remove damping
    m_structures.push_back(top);
}

void AngryBirdsScene::SpawnNewBird()
{
    if (m_birdsRemaining <= 0) return;

    m_currentBird = m_world->CreateBody(Body::Type::Dynamic, Vector2{ 200.0f, 400.0f }, 1.0f, 10.0f, RED);
    m_currentBird->restitution = 0.6f;
    m_currentBird->gravityScale = 0.0f; // Keep gravity off until launched
    m_currentBird->damping = 0.0f;
    m_birds.push_back(m_currentBird);
}

void AngryBirdsScene::Update()
{
    m_world->Step(fixedTimestep);

    // Check win condition
    if (!m_gameWon && CheckWinCondition())
    {
        m_gameWon = true;
    }

    // If game is won, don't process further updates
    if (m_gameWon)
    {
        return;
    }

    // Update bird delay timer
    if (m_birdDelayTimer > 0.0f)
    {
        m_birdDelayTimer -= GetFrameTime();
    }

    // Handle bird dragging and launching
    if (m_currentBird && m_currentBird->type == Body::Type::Dynamic && m_birdsRemaining > 0)
    {
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
            Vector2 mousePos = GetMousePosition();
            if (CheckCollisionPointCircle(mousePos, m_currentBird->position, m_currentBird->size))
            {
                m_isDragging = true;
                m_dragStart = m_currentBird->position;
                m_dragEnd = mousePos;
            }
        }
        else if (IsMouseButtonDown(MOUSE_LEFT_BUTTON) && m_isDragging)
        {
            m_dragEnd = GetMousePosition();
            Vector2 dragVector = Vector2Subtract(m_dragStart, m_dragEnd);
            float dragDistance = Vector2Length(dragVector);
            
            // Limit drag distance
            if (dragDistance > 300.0f)
            {
                dragVector = Vector2Scale(Vector2Normalize(dragVector), 300.0f);
                m_dragEnd = Vector2Subtract(m_dragStart, dragVector);
            }
            
            m_currentBird->position = m_dragEnd;
        }
        else if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON) && m_isDragging)
        {
            LaunchBird();
            m_isDragging = false;
            m_birdDelayTimer = BIRD_DELAY;  // Start delay timer
        }
    }

    // Check for off-screen birds and remove them
    for (auto it = m_birds.begin(); it != m_birds.end();)
    {
        Body* bird = *it;
        if (bird->position.x < -100.0f || bird->position.x > m_width + 100.0f ||
            bird->position.y < -100.0f || bird->position.y > m_height + 100.0f)
        {
            delete bird;
            it = m_birds.erase(it);
        }
        else
        {
            ++it;
        }
    }

    // Only attempt to spawn a new bird if:
    // 1. We have no birds
    // 2. The delay timer has fully expired
    // 3. We have birds remaining
    if (m_birds.empty() && m_birdDelayTimer <= 0.0f && m_birdsRemaining > 0)
    {
        SpawnNewBird();
    }

    CheckCollisions();
}

void AngryBirdsScene::FixedUpdate()
{
    // Physics updates are handled in Update()
}

void AngryBirdsScene::LaunchBird()
{
    if (!m_currentBird || m_birdsRemaining <= 0) return;

    Vector2 launchVelocity = Vector2Subtract(m_dragStart, m_dragEnd);
    launchVelocity = Vector2Scale(launchVelocity, 2.0f); // Increased launch power for better arc
    m_currentBird->velocity = launchVelocity;
    m_currentBird->gravityScale = 1.0f; // Enable gravity
    m_currentBird->damping = 0.0f;
    m_currentBird = nullptr; // Clear current bird pointer
    m_birdsRemaining--;
}

void AngryBirdsScene::CheckCollisions()
{
    // Check for collisions between birds and structures
    for (auto* bird : m_birds)
    {
        for (auto* structure : m_structures)
        {
            AABB birdAABB = bird->GetAABB();
            AABB structureAABB = structure->GetAABB();
            
            Vector2 birdMin = birdAABB.min();
            Vector2 birdMax = birdAABB.max();
            Vector2 structureMin = structureAABB.min();
            Vector2 structureMax = structureAABB.max();

            if (birdMin.x < structureMax.x &&
                birdMax.x > structureMin.x &&
                birdMin.y < structureMax.y &&
                birdMax.y > structureMin.y)
            {
                // Calculate collision depth
                float depthX = std::min(birdMax.x - structureMin.x, structureMax.x - birdMin.x);
                float depthY = std::min(birdMax.y - structureMin.y, structureMax.y - birdMin.y);
                float depth = std::min(depthX, depthY);

                // Add score based on impact velocity and collision depth
                float impactSpeed = Vector2Length(bird->velocity);
                m_score += static_cast<int>(impactSpeed * depth * 0.1f);
                
                // Apply impulse to the structure
                if (structure->type == Body::Type::Dynamic)
                {
                    Vector2 impulse = Vector2Scale(bird->velocity, 0.5f);
                    structure->ApplyForce(impulse, Body::ForceMode::Impulse);
                }
            }
        }
    }
}

void AngryBirdsScene::ResetGame()
{
    if (m_world)
    {
        m_world->DestroyAll();
    }

    // Clear existing bodies
    for (auto* bird : m_birds)
    {
        delete bird;
    }
    m_birds.clear();

    for (auto* structure : m_structures)
    {
        delete structure;
    }
    m_structures.clear();

    if (m_slingshot)
    {
        delete m_slingshot;
    }

    // Reset game state
    m_score = 0.0f;
    m_isDragging = false;
    m_birdDelayTimer = 0.0f;
    m_currentBird = nullptr;
    m_birdsRemaining = MAX_BIRDS;
    m_gameWon = false;

    // Recreate game elements
    CreateSlingshot();
    CreateStructures();
    SpawnNewBird();
}

void AngryBirdsScene::DrawGUI()
{
    // Draw birds remaining
    std::string birdsText = "Birds Remaining: " + std::to_string(m_birdsRemaining);
    DrawText(birdsText, Vector2{10.0f, 10.0f}, 20, BLACK);
    
    if (m_birdsRemaining <= 0 && m_birds.empty())
    {
        const char* gameOverText = "GAME OVER";
        DrawText(std::string(gameOverText), Vector2{static_cast<float>(m_width/2 - 100), static_cast<float>(m_height/2)}, 40, RED);
    }
}

void AngryBirdsScene::BeginDraw()
{
    BeginDrawing();
    ClearBackground(SKYBLUE);  // Clear with sky blue background
}

void AngryBirdsScene::Draw()
{
    // Draw structures
    for (auto* structure : m_structures)
    {
        Vector2 halfSize = Vector2{ structure->size * 0.5f, structure->size * 0.5f };
        Vector2 topLeft = Vector2Subtract(structure->position, halfSize);
        DrawRectangleV(topLeft, Vector2{ structure->size, structure->size }, structure->color);
    }

    // Draw birds
    for (auto* bird : m_birds)
    {
        DrawCircleV(bird->position, bird->size, bird->color);
    }

    // Draw slingshot
    if (m_slingshot)
    {
        Vector2 halfSize = Vector2{ m_slingshot->size * 0.5f, m_slingshot->size * 0.5f };
        Vector2 topLeft = Vector2Subtract(m_slingshot->position, halfSize);
        DrawRectangleV(topLeft, Vector2{ m_slingshot->size, m_slingshot->size }, m_slingshot->color);
    }

    // Draw trajectory line when dragging
    if (m_isDragging && m_currentBird)
    {
        Vector2 launchVelocity = Vector2Scale(Vector2Subtract(m_dragStart, m_dragEnd), 2.0f);
        Vector2 currentPos = m_currentBird->position;
        Vector2 velocity = launchVelocity;
        float dt = 0.1f;  // Time step for prediction
        
        // Draw trajectory points
        for (int i = 0; i < 60; i++)
        {
            // Apply gravity to velocity
            velocity = Vector2Add(velocity, Vector2Scale(World::gravity, dt));
            
            // Update position
            Vector2 nextPos = Vector2Add(currentPos, Vector2Scale(velocity, dt));
            
            // Draw line segment
            DrawLineV(currentPos, nextPos, RED);
            
            // Update for next iteration
            currentPos = nextPos;
        }
    }

    // Draw win screen if game is won
    if (m_gameWon)
    {
        DrawWinScreen();
    }
}

bool AngryBirdsScene::CheckWinCondition()
{
    // Check if all structures are off screen
    for (auto* structure : m_structures)
    {
        if (structure->position.x >= -100.0f && structure->position.x <= m_width + 100.0f &&
            structure->position.y >= -100.0f && structure->position.y <= m_height + 100.0f)
        {
            return false;
        }
    }
    return true;
}

void AngryBirdsScene::DrawWinScreen()
{
    // Draw semi-transparent overlay
    DrawRectangle(0, 0, m_width, m_height, ColorAlpha(BLACK, 0.5f));
    
    // Draw win text
    const char* winText = "YOU WIN!";
    DrawText(std::string(winText), Vector2{static_cast<float>(m_width/2 - 100), static_cast<float>(m_height/2)}, 40, YELLOW);
    
    // Draw restart instruction
    const char* restartText = "Press R to restart";
    DrawText(std::string(restartText), Vector2{static_cast<float>(m_width/2 - 100), static_cast<float>(m_height/2 + 50)}, 20, WHITE);
} 