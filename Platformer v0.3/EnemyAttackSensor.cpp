#include "EnemyAttackSensor.h"


void EnemyAttackSensor::SetPhysicComponent(PhysicComponent* physicComponent)
{
	this->physicComponent = physicComponent;
}

void EnemyAttackSensor::SetOffset(sf::Vector2f offset)
{
	ownerBodyOffsetLeft = { offset.x, offset.y };
	ownerBodyOffsetRight = { -offset.x, offset.y };
}

void EnemyAttackSensor::Awake()
{
	{
		b2PolygonShape boxShape;
		boxShape.SetAsBox(sizeLeft.x, sizeLeft.y, ownerBodyOffsetLeft, 0);

		b2FixtureDef boxFixtureDef;
		boxFixtureDef.shape = &boxShape;
		boxFixtureDef.isSensor = true;
		boxFixtureDef.filter.categoryBits = (1 << ((uint16)CollisionLayers::EnemyAttackSensor));
		boxFixtureDef.filter.maskBits = (1 << ((uint16)CollisionLayers::Player));

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
		boxFixtureDef.filter.categoryBits = (1 << ((uint16)CollisionLayers::EnemyAttackSensor));
		boxFixtureDef.filter.maskBits = (1 << ((uint16)CollisionLayers::Player));

		sensorRight = physicComponent->AddSensor(boxFixtureDef);

		userData = new FixtureUserData;
		userData->componentPtr = this;
		sensorRight->SetUserData(userData);
	}

	collisionMask.SetBit((uint16)CollisionLayers::Player);
	collisionMask.SetBit((uint16)CollisionLayers::EnemyAttackSensor);

	//Debug::Log("attack mask");
	//Debug::Log(collisionMask.GetMask());
	WorldContactListener::AddHandler(collisionMask, this);

}

void EnemyAttackSensor::OnCollisionEnter(b2Contact* contact)
{
	if (contact)
	{
		//Debug::Log("Entered enemy attack sensor");

		auto fix1 = FixtureManager::GetFixture(contact->GetFixtureA()->GetUserData().pointer);
		auto fix2 = FixtureManager::GetFixture(contact->GetFixtureB()->GetUserData().pointer);

		auto player = static_cast<Damageble*>(fix1->GetUserData()->damageble);
		auto sensor = static_cast<EnemyAttackSensor*>(fix2->GetUserData()->componentPtr);

		//TODO добавить проверку на принадлежность именно этому энеми
		if (fix1 != nullptr && fix2 != nullptr)
		{
			if (fix2->GetFixtureId() == sensorLeft->GetFixtureId() || fix2->GetFixtureId() == sensorRight->GetFixtureId())
			{
				playerToAttack = player;
				isTriggeredToAttack = true;
				isFirstAttack = true;
			}
		}
	}
}

void EnemyAttackSensor::OnCollisionExit(b2Contact* contact)
{
	if (contact)
	{
		//Debug::Log("Leaved enemy attack sensor");

		auto fix1 = FixtureManager::GetFixture(contact->GetFixtureA()->GetUserData().pointer);
		auto fix2 = FixtureManager::GetFixture(contact->GetFixtureB()->GetUserData().pointer);

		if (fix1 != nullptr && fix2 != nullptr)
		{
			if (fix2->GetFixtureId() == sensorLeft->GetFixtureId() || fix2->GetFixtureId() == sensorRight->GetFixtureId())
			{
				playerToAttack = nullptr;
				isTriggeredToAttack = false;
				isFirstAttack = false;
			}
		}
	}
}

void EnemyAttackSensor::OnDestroy()
{

	WorldContactListener::DeleteComponentHandler(componentId);
}
