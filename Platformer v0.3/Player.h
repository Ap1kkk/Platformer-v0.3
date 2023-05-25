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

#include "Health.h"
#include "Damageble.h"

class Player : public GameObject, public Damageble
	//, public EventListener
{
public:
	Player();

	void Awake() override;
 
	//void OnEventHappened(EventData& data) override
	//{
	//	Debug::Log("OnEventHappened");
	//}

	void TakeDamage(DamageData* damageData) override
	{
		Debug::Log("--taken damage");
		health->TakeDamage(damageData);
	}

	void OnEntityDied() override
	{
		Debug::Log("player died");
		objectContext.sceneManager->SwitchToScene(GameLevels::MainMenu);
	}

private:
	b2Body* body;
	Camera* camera;
	PlayerMovement* playerMovement;
	AttackSensor* attackSensor;
	JumpSensor* jumpSensor;

	FixtureUserData* userData;

	Health* health;
	sf::Vector2f hpOffset = { 0.f, -100.f };

	Animator* animator;

	Window* window;

	//Filename playerTexture = "hero.png"; PrototypeHero_noSword.png
	Filename playerTexture = "Characters/player.png";

	DrawLayer drawLayer = 100;

	const short FRAME_WIDTH = 100;
	const short FRAME_HEIGHT = 80;

	sf::Vector2f attackSensorOffset = { -50.f, 0.f };
};

