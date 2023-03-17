#pragma once

#include "box2d/box2d.h"
#include "GameObject.h"
#include "Input.h"
#include "Camera.h"

class Player : public GameObject
{
public:
	Player()
	{
		Debug::LogInfo("Created with id: " + std::to_string(entityId), typeid(*this).name());
	}

	void Initialize()
	{
		MakeDrawable(true);
		SetTexture("ship.png");

		MakePhysical();

		b2BodyDef bodyDef;
		bodyDef.type = b2_dynamicBody;
		bodyDef.position = b2Vec2(0, 20);
		physicComponent->SetBodyDef(bodyDef);
		physicComponent->InitializeBody();

		//b2CircleShape circleShape;
		//circleShape.m_p.Set(0, 0);
		//circleShape.m_radius = 15.f;
		b2PolygonShape boxShape;
		b2Vec2 size = GetSpriteBoxHalfSize();
		boxShape.SetAsBox(size.x, size.y);

		b2FixtureDef boxFixtureDef;
		boxFixtureDef.shape = &boxShape;
		boxFixtureDef.density = 1;

		physicComponent->AddFixtureDef(boxFixtureDef);
		body = physicComponent->GetBody();

		camera = AddComponent<Camera>();

		//TODO заменить на вызов Awake у компонента
		camera->Initialize();
	}

	void SetWindow(Window* window)
	{
		this->window = window;
		camera->SetWindow(window);
	}

	void Update(float deltaTime) override
	{

		auto input = Input::GetInputAxes();
		if (Input::IsKeyPressed(Input::Key::Horizontal))
		{
			body->ApplyLinearImpulseToCenter(b2Vec2(input.x * 100.f, 0), true);
		}
		if (Input::IsKeyPressed(Input::Key::Space))
		{
			body->ApplyLinearImpulseToCenter(b2Vec2(0, -500), true);
		}
	}

	void LateUpdate(float deltaTime) override
	{
		SyncronizeDrawable();
		camera->LateUpdate(deltaTime);
	}

private:
	b2Body* body;
	Camera* camera;
	Window* window;
};

