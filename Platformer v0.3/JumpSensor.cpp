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
	if (contact)
	{
		Debug::Log("Entered Collision");
		EnterCollision();
		EventData data(EventType::OnPlayerLanded);
		Event::Invoke(data);
		//Debug::Log("### enter " + std::to_string(intersectsCount));
		//Debug::Log(contact->GetFixtureA()->GetFilterData().categoryBits);
		//Debug::Log(contact->GetFixtureA()->GetFilterData().maskBits);
		//Debug::Log(contact->GetFixtureB()->GetFilterData().categoryBits);
		//Debug::Log(contact->GetFixtureB()->GetFilterData().maskBits);
	}
}

void JumpSensor::OnCollisionExit(b2Contact* contact)
{
	if (contact)
	{
		Debug::Log("Leaved Collision");
		LeaveCollision();
		//Debug::Log("### leave " + std::to_string(intersectsCount));
		//Debug::Log(contact->GetFixtureA()->GetFilterData().categoryBits);
		//Debug::Log(contact->GetFixtureA()->GetFilterData().maskBits);
		//Debug::Log(contact->GetFixtureB()->GetFilterData().categoryBits);
		//Debug::Log(contact->GetFixtureB()->GetFilterData().maskBits);
	}
}

void JumpSensor::OnDestroy()
{
	WorldContactListener::DeleteComponentHandler(componentId);
}
