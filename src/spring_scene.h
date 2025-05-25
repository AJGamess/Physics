#pragma once
#include "scene.h"

struct Body;

class SpringScene : public Scene
{
public:
	SpringScene(const std::string& title, int width, int height, const Color& background = BLACK) :
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
	Body* m_selected{ nullptr };
	Body* m_connected{ nullptr };
};