#include "vector_scene.h"
#include "body.h"
#include "raymath.h"
#include "raygui.h"
#include <gravitation.h>

float randomf() {
	return rand() / static_cast<float>(RAND_MAX);
}

void VectorScene::Initialize()
{
	// Initialize the scene
	m_camera = new SceneCamera(Vector2{ static_cast<float>(m_width) / 2, m_height / 2.0f });
	Body* body = new Body(Vector2{ 3, 0 }, Vector2{ 0, 0 }, 0.25f, WHITE);
	m_head = body;
	m_player = body;

	for (int i = 0; i < 10; i++)
	{
		body->next = new Body(Vector2{ randomf() * 5, 2}, Vector2{0, 0}, 0.25f, RED);
		body->next->prev = body;
		body = body->next;
	}

}

void VectorScene::Update() {

	float dt = GetFrameTime();

	//player input
	Vector2 input{ 0, 0 };
	if (IsKeyDown(KEY_A)) input.x += 1;
	if (IsKeyDown(KEY_D)) input.x -= 1;
	if (IsKeyDown(KEY_S)) input.y -= 1;
	if (IsKeyDown(KEY_W)) input.y += 1;
	input = Vector2Normalize(input);
	m_player->velocity = input * 5;

	Body* body = m_head;
	while (body) {

		if (body == m_player) {
			body->Step(dt);
			body = body->next;
			continue;
		}
		Vector2 direction = m_player->position - body->position;
		direction = Vector2Normalize(direction) * 3;
		body->velocity = direction;
		body->Step(dt);
		body = body->next;
	}
}

//void VectorScene::FixedUpdate() {
//	Gravitation::ApplyGravitation(m_world->GetBodies(), 0.15f);
//
//	//aply forces
//	m_world->Step(Scene::Update);
//}


void VectorScene::Draw() {
	m_camera->BeginMode();

	DrawGrid(10, 5, DARKGRAY);

	Body* body = m_head;
	while (body)
	{
		body->Draw(*this);
		body = body->next;
	}
	m_camera->EndMode();
}

void VectorScene::DrawGUI() {
	ClearBackground(GetColor(GuiGetStyle(DEFAULT, BACKGROUND_COLOR)));

	// raygui: controls drawing
	//----------------------------------------------------------------------------------
	if (bodyTypeDropdownBoxEditMode) GuiLock();

	if (WindowBox000Active)
	{
		WindowBox000Active = !GuiWindowBox(Rectangle { 80, 56, 216, 584 }, "SAMPLE TEXT");
		GuiPanel(Rectangle { 104, 88, 144, 328 }, NULL);
		GuiLabel(Rectangle { 112, 96, 120, 24 }, "MASS");
		GuiSlider(Rectangle { 112, 128, 120, 16 }, NULL, NULL, & massSliderValueValue, 0, 100);
		GuiLabel(Rectangle { 112, 160, 120, 24 }, "SIZE");
		GuiSlider(Rectangle { 112, 192, 120, 16 }, NULL, NULL, & sizeSliderValueValue, 0, 100);
		GuiLabel(Rectangle { 112, 224, 120, 24 }, "GRAVITY SCALE");
		GuiSlider(Rectangle { 112, 256, 120, 16 }, NULL, NULL, & gravityScaleSliderValueValue, 0, 100);
		GuiLabel(Rectangle { 112, 288, 120, 24 }, "DAMPING");
		GuiSlider(Rectangle { 112, 320, 120, 16 }, NULL, NULL, & dampingSliderValueValue, 0, 100);
		GuiLine(Rectangle { 88, 424, 184, 16 }, NULL);
		GuiSlider(Rectangle { 104, 616, 120, 16 }, NULL, NULL, & worldGravitySliderValueValue, 0, 100);
		GuiLabel(Rectangle { 104, 584, 120, 24 }, "WORLD GRAVITY");
		GuiSlider(Rectangle { 112, 384, 120, 16 }, NULL, NULL, & restitutionSliderValueValue, 0, 100);
		if (GuiDropdownBox(Rectangle { 104, 448, 144, 24 }, "DYNAMIC;STATIC;KINEMATIC", & bodyTypeDropdownBoxActive, bodyTypeDropdownBoxEditMode)) bodyTypeDropdownBoxEditMode = !bodyTypeDropdownBoxEditMode;
	}
	GuiLabel(Rectangle { 112, 352, 120, 24 }, "RESTITUTION");

	GuiUnlock();
}