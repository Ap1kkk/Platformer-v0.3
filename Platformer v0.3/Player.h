#pragma once

#include <box2d/box2d.h>

#include "GameObject.h"
#include "Input.h"
#include "Camera.h"
#include "PlayerMovement.h"
#include "JumpSensor.h"

class Player : public GameObject
{
public:
	Player();

	void Awake() override;

	void Update() override;

private:
	b2Body* body;
	Camera* camera;
	PlayerMovement* playerMovement;
	JumpSensor* jumpSensor;
	Window* window;
};

