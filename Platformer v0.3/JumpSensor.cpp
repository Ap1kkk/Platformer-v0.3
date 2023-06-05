#include "JumpSensor.h"

void JumpSensor::SetPhysicComponent(PhysicComponent* physicComponent)
{
	this->physicComponent = physicComponent;
}

void JumpSensor::SetOffset(sf::Vector2f offset)
{
	ownerBodyOffset = { offset.x, offset.y };
}

void JumpSensor::Awake()
{
	b2PolygonShape boxShape;
	boxShape.SetAsBox(size.x, size.y, ownerBodyOffset, 0);

	b2FixtureDef boxFixtureDef;
	boxFixtureDef.shape = &boxShape;
	boxFixtureDef.isSensor = true;
	boxFixtureDef.filter.categoryBits = (1 << ((uint16)CollisionLayers::JumpSensor));
	boxFixtureDef.filter.maskBits = (1 << ((uint16)CollisionLayers::Ground)) | (1 << ((uint16)CollisionLayers::Default)) | (1 << ((uint16)CollisionLayers::Enemy)) | (1 << ((uint16)CollisionLayers::SmallObstacle));

	Debug::Log(boxFixtureDef.filter.categoryBits);
	Debug::Log(boxFixtureDef.filter.maskBits);

	sensor = physicComponent->AddSensor(boxFixtureDef);

	collisionMask.SetBit((uint16)CollisionLayers::Ground);
	collisionMask.SetBit((uint16)CollisionLayers::JumpSensor);
	collisionMask.SetBit((uint16)CollisionLayers::SmallObstacle);
	WorldContactListener::AddHandler(collisionMask, this);
}

void JumpSensor::OnCollisionEnter(b2Contact* contact)
{
	auto fix1 = FixtureManager::GetFixture((FixtureId)contact->GetFixtureA()->GetUserData().pointer);
	auto fix2 = FixtureManager::GetFixture((FixtureId)contact->GetFixtureB()->GetUserData().pointer);

	if (fix1 != nullptr && fix2 != nullptr) 
	{
		if(fix1->GetFixtureId() == sensor->GetFixtureId() || fix2->GetFixtureId() == sensor->GetFixtureId())
		{
			Debug::Log("Entered Collision");
			EnterCollision();
			EventData data(EventType::OnPlayerLanded);
			Event::Invoke(data);
		}
	}
}

void JumpSensor::OnCollisionExit(b2Contact* contact)
{
	auto fix1 = FixtureManager::GetFixture((FixtureId)contact->GetFixtureA()->GetUserData().pointer);
	auto fix2 = FixtureManager::GetFixture((FixtureId)contact->GetFixtureB()->GetUserData().pointer);

	if (fix1 != nullptr && fix2 != nullptr)
	{
		if (fix1->GetFixtureId() == sensor->GetFixtureId() || fix2->GetFixtureId() == sensor->GetFixtureId())
		{
			Debug::Log("Leaved Collision");
			LeaveCollision();
		}
	}
}

void JumpSensor::OnDestroy()
{
	WorldContactListener::DeleteComponentHandler(componentId);
}
