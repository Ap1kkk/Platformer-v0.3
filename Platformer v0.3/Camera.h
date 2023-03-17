#pragma once

#include "Window.h"
#include "TransformComponent.h"
#include "GameObject.h"
#include "EntityManager.h"
#include "Component.h"

class Camera : public Component
{
public:
	Camera() {}

	void Initialize()
	{
		auto gameObject = EntityManager::GetEntityById<GameObject>(ownerId);
		transform = gameObject->GetComponent<TransformComponent>();
	}

	void SetWindow(Window* window)
	{
		this->window = window;
	}

	void LateUpdate(float deltaTime)
	{
		sf::View view = window->GetView();
		const sf::Vector2f& tragetPosition = transform->GetPosition();
		view.setCenter(tragetPosition.x, tragetPosition.y);
		window->SetView(view);
	}

private:
	Window* window;
	TransformComponent* transform;
};

