#pragma once

#include <unordered_map>

#include "box2d/box2d.h"
#include "Debug.h"
#include "DataTypes.h"

#include "IEntity.h"
#include "IComponent.h"
#include "Damageble.h"

struct FixtureUserData
{
	IComponent* componentPtr;
	IEntity* entityPtr;
	Damageble* damageble;
};

class Fixture : public b2Fixture
{
public:
	Fixture(EntityId ownerId) : ownerId(ownerId), fixtureId(staticIdCounter++)
	{}
	virtual ~Fixture()
	{
		delete userData;
	}

	FixtureId GetFixtureId() const { return fixtureId; }
	EntityId GetOwnerId() const { return ownerId; }
	b2Fixture* GetOwningFixture() const { return owningFixture; }

	void SetOwningFixture(b2Fixture* owningFixture)
	{
		this->owningFixture = owningFixture;
	}

	void SetUserData(FixtureUserData* userData)
	{
		this->userData = userData;
	}

	FixtureUserData* GetUserData() const
	{
		return userData;
	}

private:
	b2Fixture* owningFixture;

	FixtureUserData* userData;

	const EntityId ownerId;
	const FixtureId fixtureId;
	static FixtureId staticIdCounter;
};

class Sensor : public Fixture
{
public:
	Sensor(EntityId ownerId) : Fixture(ownerId), sensorId(staticIdCounter++) {}

	SensorId GetSensorId() const { return sensorId; }

private:
	const SensorId sensorId;
	static SensorId staticIdCounter;
};

class IBody
{
public:
	IBody() {}
	virtual ~IBody() {}

	inline void SetBodyOwner(EntityId id) { bodyOwnerId = id; }
	inline EntityId GetBodyOwner() const { return bodyOwnerId; }

	b2Body* GetBody() { return body; }
	void SetBody(b2Body* body) { this->body = body; }
	
protected:
	b2Body* body;
	b2BodyDef bodyDef;

	std::unordered_map<FixtureId, Fixture*> fixtures {};

	EntityId bodyOwnerId;
};
