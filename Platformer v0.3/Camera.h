#pragma once

#include "Window.h"
#include "TransformComponent.h"
#include "GameObject.h"
#include "EntityManager.h"
#include "IComponent.h"

class Camera : public IComponent
{
public:
	Camera() {}

	void Awake() override;

	void LateUpdate() override;

private:
	Window* window;
	TransformComponent* transform;
};

