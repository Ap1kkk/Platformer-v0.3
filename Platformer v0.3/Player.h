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

#include "SaveManager.h"

class Player : public GameObject, public Damageble
	//, public EventListener
{
public:
	Player();
	~Player()
	{
		Entity::UnsubscribeFromEvent(EventType::OnPlayerDataRequest);
	}

	void Awake() override;
 
	void OnEventHappened(EventData& eventData) override
	{
		if (eventData.eventType == EventType::OnPlayerDataRequest)
		{
			EventData data(EventType::OnPlayerDataCallback);
	
			auto userData = new PlayerDataRequestData;
			userData->position = sf::Vector2f{ body->GetPosition().x, body->GetPosition().y};
			userData->healthPoints = health->GetHealthPoints();

			data.userData = userData;

			Event::Invoke(data);

			delete userData;
		}
		if (eventData.eventType == EventType::OnEntityDiedEvent)
		{
			Damageble::OnEventHappened(eventData);
		}
	}

	void SetHealthPoints(int healthPoints)
	{
		initialHealthPoints = healthPoints;
	}

	void TakeDamage(DamageData* damageData) override
	{
		Debug::Log("--taken damage");
		health->TakeDamage(damageData);
	}

	void OnEntityDied() override
	{
		Debug::Log("player died");
		SaveManager::SetIsGameOver();
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

	const short FRAME_WIDTH = 105;
	const short FRAME_HEIGHT = 110;

	sf::Vector2f attackSensorOffset = { -50.f, 0.f };

	int initialHealthPoints = -1;
};

