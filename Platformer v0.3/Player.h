#pragma once

#include <box2d/box2d.h>

#include "GameObject.h"
#include "Input.h"
#include "Camera.h"
#include "PlayerMovement.h"
#include "AttackSensor.h"
#include "JumpSensor.h"

#include "Animation.h"
#include "Animator.h"

#include "IdlePlayerAnimState.h"
#include "RunPlayerAnimState.h"
#include "SprintedPlayerAnimState.h"
#include "JumpFallPlayerAnimState.h"
#include "JumpRaisedPlayerAnimState.h"
#include "AttackPlayerAnimState.h"

class Player : public GameObject
	//, public EventListener
{
public:
	Player();

	void Awake() override;
 
	//void OnEventHappened(EventData& data) override
	//{
	//	Debug::Log("OnEventHappened");
	//}


private:
	b2Body* body;
	Camera* camera;
	PlayerMovement* playerMovement;
	AttackSensor* attackSensor;
	JumpSensor* jumpSensor;

	Animator* animator;

	Window* window;

	//Filename playerTexture = "hero.png"; PrototypeHero_noSword.png
	Filename playerTexture = "PrototypeHero_noSword.png";

	DrawLayer drawLayer = 100;

	const short FRAME_WIDTH = 100;
	const short FRAME_HEIGHT = 80;
};

