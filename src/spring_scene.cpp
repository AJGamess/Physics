#include "spring_scene.h"
#include "gui.h"
#include "body.h"
#include "raymath.h"
#include "mathutils.h"
#include "raygui.h"
#include "world.h"
#include "gravitation.h"


void SpringScene::Initialize()
{
	m_camera = new SceneCamera(Vector2{ static_cast<float>(m_width) / 2, static_cast<float>(m_height) / 2 });
	m_world = new World();
	m_world->Initialize();
	Body* body = new Body(Vector2{ 3,0 }, Vector2{ 0 }, 0.25f, WHITE);
}

void SpringScene::Update()
{
	float dt = GetFrameTime();
	GUI::Update();

	if (IsKeyPressed(KEY_SPACE)) {
		World::simulate = !World::simulate;
	}

	if (!GUI::mouseOverGUI) {
		if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) || IsMouseButtonDown(MOUSE_LEFT_BUTTON) && IsKeyDown(KEY_LEFT_CONTROL)) {
			Vector2 position = m_camera->ScreenToWorld(GetMousePosition());
			Body::Type type = (Body::Type)GUI::bodyTypeActive;
			Body* body = m_world->CreateBody(type, position, GUI::massValue, GUI::sizeValue, ColorFromHSV(randomf(360), 1, 1));

			body->restitution = GUI::restitutionValue;
			body->gravityScale = GUI::gravityScaleValue;
			body->damping = GUI::dampingValue;

			body->ApplyForce(randomOnUnitCircle() * 10, Body::ForceMode::Velocity);
		}

		//select body
		if (IsMouseButtonPressed(MOUSE_RIGHT_BUTTON)) {
			Vector2 position = m_camera->ScreenToWorld(GetMousePosition());
			m_selected = GUI::GetBodyIntersect(position, m_world->GetBodies(), *m_camera);
		}
		if (m_selected) {
			if (IsMouseButtonDown(MOUSE_RIGHT_BUTTON) && IsKeyDown(KEY_LEFT_CONTROL)) {
				if (m_selected->type == Body::Type::Dynamic)
				{
					Vector2 position = m_camera->ScreenToWorld(GetMousePosition());
					Spring::ApplyForce(position, *m_selected, 0.2f, 15.0f);
				}
			}
			else if (IsMouseButtonDown(MOUSE_RIGHT_BUTTON)) {
				Vector2 position = m_camera->ScreenToWorld(GetMousePosition());
				m_connected = GUI::GetBodyIntersect(position, m_world->GetBodies(), *m_camera);
			}
			else {
				if (m_selected && m_connected) {
					float distance = Vector2Distance(m_selected->position, m_connected->position);
					m_world->CreateSpring(m_selected, m_connected, distance, GUI::stiffnessValue, GUI::springDampingValue);
				}
				m_connected = nullptr;
				m_selected = nullptr;
			}
		}
	}

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

	for (auto body : m_world->GetBodies())
	{
		AABB aabb = body->GetAABB();
		AABB worldAABB = m_camera->GetAABB();

		if ((aabb.min().y) < worldAABB.min().y)
		{
			float overlap = (worldAABB.min().y - aabb.min().y); // calculate how far the body has penetrated beyond the world boundary
			body->position.y += 2 * overlap; // move the body back inside the world bounds
			body->velocity.y *= -body->restitution; // multiple by -restituion to scale and flip velocity
		}
		else if ((aabb.max().y) > worldAABB.max().y)
		{
			float overlap = (worldAABB.max().y - aabb.max().y);  // calculate how far the body has penetrated beyond the world boundary
			body->position.y += 2 * overlap; // move the body back inside the world bounds
			body->velocity.y *= -body->restitution; // multiple by -restituion to scale and flip velocity
		}

		if ((aabb.min().x) < worldAABB.min().x)
		{
			//<update x>
			float overlap = (worldAABB.min().x - aabb.min().x); // calculate how far the body has penetrated beyond the world boundary
			body->position.x += 2 * overlap; // move the body back inside the world bounds
			body->velocity.x *= -body->restitution; // multiple by -restituion to scale and flip velocity

		}
		else if (aabb.max().x > worldAABB.max().x)
		{
			//<update x>
			float overlap = (worldAABB.max().x - aabb.max().x); // calculate how far the body has penetrated beyond the world boundary
			body->position.x += 2 * overlap; // move the body back inside the world bounds
			body->velocity.x *= -body->restitution; // multiple by -restituion to scale and flip velocity

		}
	}
}

void SpringScene::FixedUpdate()
{


	//apply forces
	m_world->Step(Scene::fixedTimeStep);

}

void SpringScene::Draw()
{
	m_camera->BeginMode();

	DrawGrid(10, 5, DARKGRAY);
	m_world->Draw(*this);
	if (m_selected) {
		DrawCircleLines(m_selected->position, m_selected->size, YELLOW, 5);
		if (m_connected) {
			DrawCircleLines(m_connected->position, m_connected->size, YELLOW, 5);
			DrawLine(m_selected->position, m_connected->position, 3, GREEN);
		}
		else
		{
			DrawLine(m_selected->position, m_camera->ScreenToWorld(GetMousePosition()), 3, RED);
		}
	}

	m_camera->EndMode();
}

void SpringScene::DrawGUI()
{
	GUI::Draw();
}
