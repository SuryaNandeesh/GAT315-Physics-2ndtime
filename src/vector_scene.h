#pragma once
#include "scene.h"

struct Body;

class VectorScene : public Scene
{
public:
	VectorScene(const std::string& title, int width, int height, const Color& background = BLACK);
	~VectorScene();

	void Initialize() override;
	void Update() override;
	void FixedUpdate();
	void Draw() override;
	void DrawGUI() override;

private:
	Body* m_head{ nullptr };
	Body* m_player{ nullptr };

	bool WindowBox000Active = true;
	float massSliderValueValue = 0.0f;
	float sizeSliderValueValue = 0.0f;
	float gravityScaleSliderValueValue = 0.0f;
	float dampingSliderValueValue = 0.0f;
	bool bodyTypeDropdownBoxEditMode = false;
	int bodyTypeDropdownBoxActive = 0;
	float worldGravitySliderValueValue = 0.0f;
	float restitutionSliderValueValue = 0.0f;
};