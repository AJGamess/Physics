#pragma once
#include "scene.h"

struct Body;

class VectorScene : public Scene
{
public:
	VectorScene(const std::string& title, int width, int height, const Color& background = BLACK) :
		Scene(title, width, height, background)
	{
		//
	}

	// Inherited via Scene
	void Initialize() override;
	void Update() override;
	void FixedUpdate() override;
	void Draw() override;
	void DrawGUI() override;
private:
	Vector2 anchor01 = { 88, 64 };

	bool PhysicsWindowBoxActive = true;
	float GravitySliderValue = 0.0f;
	float MassSliderValue = 0.0f;
	float SizeSliderValue = 0.0f;
	float DampingSliderValue = 0.0f;
	float GravitationalForceSliderValue = 0.0f;
	bool BodyTypeDropdownBoxEditMode = false;
	int BodyTypeDropdownBoxActive = 0;
};