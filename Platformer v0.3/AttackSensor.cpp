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
	boxFixtureDef.filter.categoryBits = (1 << ((uint16)CollisionLayers::AttackSensorLeft));
	boxFixtureDef.filter.maskBits = (1 << ((uint16)CollisionLayers::Enemy));

	sensor = physicComponent->AddSensor(boxFixtureDef);

	userData = new FixtureUserData;
	userData->componentPtr = this;
	sensor->SetUserData(userData);


	collisionMask.SetBit((uint16)CollisionLayers::Enemy);
	collisionMask.SetBit((uint16)CollisionLayers::AttackSensorLeft);

	//Debug::Log("attack mask");
	//Debug::Log(collisionMask.GetMask());
	WorldContactListener::AddHandler(collisionMask, this);

	SubscribeOnEvent<OnPlayerTurnedFaceEvent>();

}

void AttackSensor::OnCollisionEnter(b2Contact* contact)
{
	if (contact)
	{
		Debug::Log("Entered attack sensor");

		auto fixtureA = static_cast<Fixture*>(contact->GetFixtureA());
		auto fixtureB = static_cast<Fixture*>(contact->GetFixtureB());

		//Debug::Log(fixtureA->GetUserData().pointer);
		//Debug::Log(fixtureB->GetUserData().pointer);

		auto fix1 = FixtureManager::GetFixture(contact->GetFixtureA()->GetUserData().pointer);
		auto fix2 = FixtureManager::GetFixture(contact->GetFixtureB()->GetUserData().pointer);

		auto sensor = static_cast<AttackSensor*>(fix1->GetUserData()->componentPtr);
		auto enemy = static_cast<Damageble*>(fix2->GetUserData()->damageble);

		Debug::Log(sensor->GetComponentId());

		auto damageData = new DamageData;
		damageData->value = 50;

		enemy->TakeDamage(damageData);
		delete damageData;
		//Debug::Log(fix2->GetUserData()->test);
	}
}

void AttackSensor::OnCollisionExit(b2Contact* contact)
{
	if (contact)
	{
		Debug::Log("Leaved attack sensor");

		auto fixtureA = static_cast<Fixture*>(contact->GetFixtureA());
		auto fixtureB = static_cast<Fixture*>(contact->GetFixtureB());

		if (fixtureB == NULL)
		{
			int i;
		}
		//Debug::Log(fixtureA->GetUserData().pointer);
		//Debug::Log(fixtureB->GetUserData().pointer);

		auto fix1 = FixtureManager::GetFixture(contact->GetFixtureA()->GetUserData().pointer);
		auto fix2 = FixtureManager::GetFixture(contact->GetFixtureB()->GetUserData().pointer);

		if (fix1 != nullptr && fix2 != nullptr)
		{
			auto sensor = static_cast<AttackSensor*>(fix1->GetUserData()->componentPtr);
			auto enemy = static_cast<Damageble*>(fix2->GetUserData()->damageble);

			Debug::Log(sensor->GetComponentId());
		}
	}
}

void AttackSensor::OnDestroy()
{
	UnsubscribeFromEvent<OnPlayerTurnedFaceEvent>();
	WorldContactListener::DeleteComponentHandler(componentId);
}
