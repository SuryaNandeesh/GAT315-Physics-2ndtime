#include "vector_scene.h"
#include "mathutils.h"
#include "body.h"
#include "world.h"
#include "raymath.h"
#include "raygui.h"
#include "gui.h"

void VectorScene::Initialize()
{
	m_camera = new SceneCamera(Vector2{ static_cast<float>(m_width) / 2, static_cast<float>(m_height) / 2 });
	m_world = new World();
	m_world->Initialize();

}

void VectorScene::Update() {

	float dt = GetFrameTime();

	GUI::Update();

	float theta = randf(0, 360);

	if (!GUI::mouseOverGUI && IsMouseButtonPressed(0))
	{
		int pattern = 0;

		Vector2 position = m_camera->ScreenToWorld(GetMousePosition());

		for (int i = 0; i < 100; i++)
		{
			Body* body = m_world->CreateBody(position, 0.05f, ColorFromHSV(randf(360), 1, 1));

			float offset = randf(-180, 180);
			float theta = randf(0, 360);
			float x = cosf((theta + offset) * DEG2RAD);
			float y = sinf((theta + offset) * DEG2RAD);

			body->mass = GUI::massValue;
			body->size = GUI::sizeValue;
			body->gravityScale = GUI::gravityValue;
			body->damping = GUI::dampingValue;
			body->velocity = Vector2{ x, y } *randf(1, 6);
			body->restitution = GUI::restitutionValue;
		}
	}
	//apply forces
	//applycollision
	for (auto body : m_world->GetBodies())
	{
		if (body->position.y < -5)
		{
			body->position.y = -5;
			body->velocity.y *= -body->restitution;
		}
		if (body->position.x < -9)
		{
			body->position.x = -9;
			body->velocity.x *= -body->restitution;
		}
		if (body->position.x > 9)
		{
			body->position.x = 9;
			body->velocity.x *= -body->restitution;
		}

		AABB aabb = body->GetAABB();
		AABB worldAABB = m_camera->GetAABB();

		if ((aabb.min().y) < worldAABB.min().y)
		{
			float overlap = (worldAABB.min().y - aabb.min().y); // calculate how far the body has penetrated beyond the world boundary
			body->position.y += 2 * overlap; // move the body back inside the world bounds
			body->velocity.y *= -body->damping; // multiple by -restituion to scale and flip velocity
		}
		else if ((aabb.max().y) > worldAABB.max().y)
		{
			float overlap = (worldAABB.max().y - aabb.max().y);  // calculate how far the body has penetrated beyond the world boundary
			body->position.y += 2 * overlap; // move the body back inside the world bounds
			body->velocity.y *= -body->damping; // multiple by -restituion to scale and flip velocity
		}

		if ((aabb.min().x) < worldAABB.min().x)
		{
			body->position.x = worldAABB.min().x;
		}
		else if (aabb.max().x > worldAABB.max().x)
		{
			body->position.x = worldAABB.max().x;
		}
	}
}

void VectorScene::FixedUpdate() {
	//apply forces
	m_world->Step(Scene::fixedTimestep);
}

void VectorScene::Draw() {
	m_camera->BeginMode();

	DrawGrid(10, 5, DARKGRAY);
	m_world->Draw(*this);

	m_camera->EndMode();
}

void VectorScene::DrawGUI() {
	GUI::Draw();
}