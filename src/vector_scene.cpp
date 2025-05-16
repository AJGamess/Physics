#include "vector_scene.h"
#include "body.h"
#include "raymath.h"
#include "mathutils.h"
#include "raygui.h"
#include "world.h"
#include "gravitation.h"

// Uncomment only one of these at a time
#define FIREWORK_BURST
//#define FIREWORK_RING
//#define FIREWORK_CONE


void VectorScene::Initialize()
{
	m_camera = new SceneCamera(Vector2{ static_cast<float>(m_width) / 2, static_cast<float>(m_height) / 2 });
	m_world = new World();
	m_world->Initialize();
	Body* body = new Body(Vector2{ 3,0 }, Vector2{ 0 }, 0.25f, WHITE);
}

void VectorScene::Update()
{
	float dt = GetFrameTime();

	if (IsMouseButtonPressed(0)) {
		Vector2 position = m_camera->ScreenToWorld(GetMousePosition());

#ifdef FIREWORK_BURST
		for (int i = 0; i < 100; i++) {
			Body* body = m_world->CreateBody(position, 0.05f, ColorFromHSV(randomf(360), 1, 1));
			float theta = randomf(0, 2 * PI);
			Vector2 dir = { cosf(theta), sinf(theta) };
			body->velocity = dir * randomf(1, 6);
			body->restitution = randomf(0.5f, 1.0f);
		}
#endif

#ifdef FIREWORK_RING
		int count = 100;
		for (int i = 0; i < count; i++) {
			float angle = (2 * PI / count) * i;
			Vector2 dir = { cosf(angle), sinf(angle) };
			Body* body = m_world->CreateBody(position, 0.05f, ColorFromHSV(randomf(360), 1, 1));
			body->velocity = dir * randomf(2, 5);
			body->restitution = randomf(0.5f, 1.0f);
		}
#endif

#ifdef FIREWORK_CONE
		int count = 100;
		float baseAngle = -PI / 2;
		float spread = PI / 4;
		for (int i = 0; i < count; i++) {
			float angle = baseAngle + randomf(-spread / 2, spread / 2);
			Vector2 dir = { cosf(angle), sinf(angle) };
			Body* body = m_world->CreateBody(position, 0.05f, ColorFromHSV(randomf(360), 1, 1));
			body->velocity = dir * randomf(2, 6);
		}
#endif
	}

#ifdef Chase
	/*
	//player control
	Vector2 input{ 0 };
	if (IsKeyDown(KEY_W)) input.y += 1;
	if (IsKeyDown(KEY_S)) input.y -= 1;
	if (IsKeyDown(KEY_A)) input.x -= 1;
	if (IsKeyDown(KEY_D)) input.x += 1;
	input = Vector2Normalize(input) * 2;
	m_player->velocity = input;

	Body* body = m_head;
	while (body) {
		if (body == m_player) {
			body->Step(dt);
			body = body->next;
			continue;
		}

		Vector2 direction = m_player->position - body-> position;
		direction = Vector2Normalize(direction) * 1;
		body->velocity = direction;

		body->Step(dt);
		body = body->next;

	}
	*/
#endif

	//apply collison
	for (auto body : m_world->GetBodies()) {
		if (body->position.y < -5)
		{
			body->position.y = -5;
			body->velocity.y *= -body->restitution;

		}
		if (body->position.x < -9) {
			body->position.x = -9;
			body->velocity.x *= -body->restitution;
		}
		if (body->position.x > 9)
		{
			body->position.x = 9;
			body->velocity.x *= -body->restitution;
		}
	}
}

void VectorScene::FixedUpdate()
{
	ApplyGravitation(m_world->GetBodies(), 0.15f);

	//apply forces
	m_world->Step(Scene::fixedTimeStep);

}

void VectorScene::Draw()
{
	m_camera->BeginMode();
	DrawGrid(10, 5, DARKGRAY);
#ifdef ChaseDraw
	/*
	Body* body = m_head;
	while (body) {
		body->Draw(*this);
		body = body->next;

	}
	*/
#endif // Chase

	m_world->Draw(*this);


	m_camera->EndMode();
}

void VectorScene::DrawGUI()
{
	if (PhysicsWindowBoxActive)
	{
		PhysicsWindowBoxActive = !GuiWindowBox(Rectangle { anchor01.x + 0, anchor01.y + 0, 176, 368 }, "Phsyics");
		GuiLabel(Rectangle { anchor01.x + 32, anchor01.y + 24, 120, 24 }, "Physics Controller");
		GuiLine(Rectangle { anchor01.x + 0, anchor01.y + 40, 176, 12 }, NULL);
		GuiSlider(Rectangle { anchor01.x + 48, anchor01.y + 56, 120, 16 }, "Gravity", NULL, & World::gravity.y, -20, 20);
		GuiSlider(Rectangle {anchor01.x + 48, anchor01.y + 90, 120, 16 }, "Mass", NULL, & MassSliderValue, 0, 100);
		GuiSlider(Rectangle { anchor01.x + 48, anchor01.y + 120, 120, 16 }, "Size", NULL, & SizeSliderValue, 0.1f, 5.0f);
		GuiSlider(Rectangle { anchor01.x + 48, anchor01.y + 152, 120, 16 }, "Damping", NULL, & DampingSliderValue, 0, 100);
		GuiSlider(Rectangle { anchor01.x + 48, anchor01.y + 184, 120, 16 }, "Force", NULL, & GravitationalForceSliderValue, 0, 100);
		GuiLabel(Rectangle { anchor01.x + 7, anchor01.y + 216, 56, 24 }, "Body Type");
		if (GuiDropdownBox(Rectangle { anchor01.x + 72, anchor01.y + 216, 96, 24 }, "Dynamic;Static;Kinematic", & BodyTypeDropdownBoxActive, BodyTypeDropdownBoxEditMode)) BodyTypeDropdownBoxEditMode = !BodyTypeDropdownBoxEditMode;
	}
}
