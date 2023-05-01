#pragma once

#include <box2d/box2d.h>

#include "GameObject.h"
#include "Input.h"
#include "Camera.h"
#include "PlayerMovement.h"
#include "AttackSensor.h"
#include "JumpSensor.h"

#include "EventListener.h"

class Player : public GameObject
	//, public EventListener
{
public:
	Player();

	void Awake() override;
 
	//void OnEventHappened(const EventData& data) override
	//{
	//	Debug::Log("OnEventHappened");
	//}

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

