#include "trigonometry.h"

void TrigonometryScene::Initialize()
{
	m_camera = new SceneCamera(Vector2{static_cast<float>(m_width)/2, static_cast<float>(m_height)/2});
}

void TrigonometryScene::Update()
{
}

void TrigonometryScene::Draw()
{
	m_camera->BeginMode();
	DrawCircle(100, 100, 100, RED);
	m_camera->EndMode();
}

void TrigonometryScene::DrawGUI()
{
}
