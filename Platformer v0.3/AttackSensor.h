#pragma once

#include "IComponent.h"
#include "ISensor.h"

#include "PhysicComponent.h"
#include "WorldContactListener.h"
#include "Bitmask.h"

#include "Debug.h"

#include "Input.h"

#include "Damageble.h"

#include "EventListener.h"
#include "OnPlayerTurnedFaceEvent.h"
#include "PlayerTurnedFaceData.h"

#include "FixtureManager.h"

class AttackSensor : public IComponent, public ISensor, public EventListener
{
public:
	AttackSensor() {}

	void SetPhysicComponent(PhysicComponent* physicComponent);

	void SetOffset(sf::Vector2f offset);

	void Awake() override;

	void Update()
	{
		if (Input::IsKeyDown(Input::Key::LMouseButton))
		{
			Debug::Log("lmb click");
		}
	}

	void OnCollisionEnter(b2Contact* contact) override;
	void OnCollisionExit(b2Contact* contact) override;

	void OnDestroy() override;

	void OnEventHappened(EventData& eventData) override
	{
		if (eventData.eventType == OnPlayerTurnedFaceEvent::GetType())
		{
			PlayerTurnedFaceData* data = static_cast<PlayerTurnedFaceData*>(eventData.userData);
			Debug::Log(std::to_string((short)data->direction));
		}
	}

private:
	b2Body* body;
	b2Vec2 ownerBodyOffset;
	Sensor* sensor;
	PhysicComponent* physicComponent;
	Bitmask collisionMask;

	bool isEnabledToJump;
	FixtureUserData* userData;
};

