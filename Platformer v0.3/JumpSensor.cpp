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
	b2Vec2 size = { 10, 6 };
	boxShape.SetAsBox(size.x, size.y, ownerBodyOffset, 0);

	b2FixtureDef boxFixtureDef;
	boxFixtureDef.shape = &boxShape;
	boxFixtureDef.isSensor = true;
	boxFixtureDef.filter.categoryBits = (1 << ((uint16)CollisionLayers::JumpSensor));
	boxFixtureDef.filter.maskBits = (1 << ((uint16)CollisionLayers::Ground)) | (1 << ((uint16)CollisionLayers::Default)) | (1 << ((uint16)CollisionLayers::Enemy)) | (1 << ((uint16)CollisionLayers::SmallObstacle));

	Debug::Log(boxFixtureDef.filter.categoryBits);
	Debug::Log(boxFixtureDef.filter.maskBits);

	//TODO добавить маску слоев коллизий

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
	}
}

void JumpSensor::OnCollisionExit(b2Contact* contact)
{
	if (contact)
	{
		Debug::Log("Leaved Collision");
		LeaveCollision();
	}
}

void JumpSensor::OnDestroy()
{
	WorldContactListener::DeleteComponentHandler(componentId);
}
