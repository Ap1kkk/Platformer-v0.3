#include "AttackSensor.h"

void AttackSensor::SetPhysicComponent(PhysicComponent* physicComponent)
{
	this->physicComponent = physicComponent;
}

void AttackSensor::SetOffset(sf::Vector2f offset)
{
	ownerBodyOffset = { offset.x, offset.y };
}

void AttackSensor::Awake()
{
	b2PolygonShape boxShape;
	b2Vec2 size = { 20, 50 };
	boxShape.SetAsBox(size.x, size.y, ownerBodyOffset, 0);

	b2FixtureDef boxFixtureDef;
	boxFixtureDef.shape = &boxShape;
	boxFixtureDef.isSensor = true;
	boxFixtureDef.filter.categoryBits = (1 << ((uint16)CollisionLayers::AttackSensor));
	boxFixtureDef.filter.maskBits = (1 << ((uint16)CollisionLayers::Enemy));

	sensor = physicComponent->AddSensor(boxFixtureDef);

	collisionMask.SetBit((uint16)CollisionLayers::Enemy);
	collisionMask.SetBit((uint16)CollisionLayers::AttackSensor);

	Debug::Log("attack mask");
	Debug::Log(collisionMask.GetMask());
	WorldContactListener::AddHandler(collisionMask, this);
}

void AttackSensor::OnCollisionEnter(b2Contact* contact)
{
	if (contact)
	{
		Debug::Log("Entered attack sensor");
	}
}

void AttackSensor::OnCollisionExit(b2Contact* contact)
{
	if (contact)
	{
		Debug::Log("Leaved attack sensor");
	}
}

void AttackSensor::OnDestroy()
{
	WorldContactListener::DeleteComponentHandler(componentId);
}
