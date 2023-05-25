#include "AttackSensor.h"

void AttackSensor::SetPhysicComponent(PhysicComponent* physicComponent)
{
	this->physicComponent = physicComponent;
}

void AttackSensor::SetOffset(sf::Vector2f offset)
{
	ownerBodyOffsetLeft = { offset.x, offset.y };
	ownerBodyOffsetRight = { -offset.x, offset.y };
}

void AttackSensor::Awake()
{
	{
		b2PolygonShape boxShape;
		boxShape.SetAsBox(sizeLeft.x, sizeLeft.y, ownerBodyOffsetLeft, 0);

		b2FixtureDef boxFixtureDef;
		boxFixtureDef.shape = &boxShape;
		boxFixtureDef.isSensor = true;
		boxFixtureDef.filter.categoryBits = (1 << ((uint16)CollisionLayers::AttackSensor));
		boxFixtureDef.filter.maskBits = (1 << ((uint16)CollisionLayers::Enemy));

		sensorLeft = physicComponent->AddSensor(boxFixtureDef);

		userData = new FixtureUserData;
		userData->componentPtr = this;
		sensorLeft->SetUserData(userData);
	}

	{
		b2PolygonShape boxShape;
		boxShape.SetAsBox(sizeRight.x, sizeRight.y, ownerBodyOffsetRight, 0);

		b2FixtureDef boxFixtureDef;
		boxFixtureDef.shape = &boxShape;
		boxFixtureDef.isSensor = true;
		boxFixtureDef.filter.categoryBits = (1 << ((uint16)CollisionLayers::AttackSensor));
		boxFixtureDef.filter.maskBits = (1 << ((uint16)CollisionLayers::Enemy));

		sensorRight = physicComponent->AddSensor(boxFixtureDef);

		userData = new FixtureUserData;
		userData->componentPtr = this;
		sensorRight->SetUserData(userData);
	}

	collisionMask.SetBit((uint16)CollisionLayers::Enemy);
	collisionMask.SetBit((uint16)CollisionLayers::AttackSensor);

	//Debug::Log("attack mask");
	//Debug::Log(collisionMask.GetMask());
	WorldContactListener::AddHandler(collisionMask, this);


	SubscribeOnEvent(EventType::OnPlayerTurnedFaceEvent);
	SubscribeOnEvent(EventType::OnEntityDiedEvent);
}

void AttackSensor::OnCollisionEnter(b2Contact* contact)
{
	if (contact)
	{
		Debug::Log("Entered attack sensor");

		auto fix1 = FixtureManager::GetFixture(contact->GetFixtureA()->GetUserData().pointer);
		auto fix2 = FixtureManager::GetFixture(contact->GetFixtureB()->GetUserData().pointer);

		auto sensor = static_cast<AttackSensor*>(fix1->GetUserData()->componentPtr);
		auto enemy = static_cast<Damageble*>(fix2->GetUserData()->damageble);

		if (fix1->GetFixtureId() == sensorLeft->GetFixtureId())
		{
			AddToAttackBufferLeft(enemy->GetDamagebleOwnerId(), enemy);
		}
		else if(fix1->GetFixtureId() == sensorRight->GetFixtureId())
		{
			AddToAttackBufferRight(enemy->GetDamagebleOwnerId(), enemy);
		}
	}
}

void AttackSensor::OnCollisionExit(b2Contact* contact)
{
	if (contact)
	{
		Debug::Log("Leaved attack sensor");

		auto fix1 = FixtureManager::GetFixture(contact->GetFixtureA()->GetUserData().pointer);
		auto fix2 = FixtureManager::GetFixture(contact->GetFixtureB()->GetUserData().pointer);

		if (fix1 != nullptr && fix2 != nullptr)
		{
			auto sensor = static_cast<AttackSensor*>(fix1->GetUserData()->componentPtr);
			auto enemy = static_cast<Damageble*>(fix2->GetUserData()->damageble);

			if (fix1->GetFixtureId() == sensorLeft->GetFixtureId())
			{
				RemoveFromAttackBufferLeft(enemy->GetDamagebleOwnerId());
			}
			else
			{
				RemoveFromAttackBufferRight(enemy->GetDamagebleOwnerId());
			}
		}
	}
}

void AttackSensor::OnDestroy()
{
	UnsubscribeFromEvent(EventType::OnPlayerTurnedFaceEvent);
	UnsubscribeFromEvent(EventType::OnEntityDiedEvent);
	WorldContactListener::DeleteComponentHandler(componentId);
}
