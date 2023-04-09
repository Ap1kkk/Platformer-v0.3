#pragma once

#include <box2d/box2d.h>

#include "GameObject.h"
#include "Input.h"
#include "Camera.h"
#include "PlayerMovement.h"
#include "AttackSensor.h"
#include "JumpSensor.h"

class Player : public GameObject
{
public:
	Player();

	void Awake() override;
 

private:
	b2Body* body;
	Camera* camera;
	PlayerMovement* playerMovement;
	AttackSensor* attackSensor;
	JumpSensor* jumpSensor;
	Window* window;

	Filename playerTexture = "hero.png";

	DrawLayer drawLayer = 100;
};

