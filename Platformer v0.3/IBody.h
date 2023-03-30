#pragma once

#include <unordered_map>

#include "box2d/box2d.h"
#include "Debug.h"
#include "DataTypes.h"

class Fixture : public b2Fixture
{
public:
	Fixture(b2Fixture* owningFixture) : owningFixture(owningFixture), fixtureId(staticIdCounter++) 
	{}

	FixtureId GetFixtureId() const { return fixtureId; }
	b2Fixture* GetOwningFixture() const { return owningFixture; }

	//static FixtureId GetStaticIdCounter() { return staticIdCounter; }

private:
	b2Fixture* owningFixture;

	FixtureId fixtureId;
	static FixtureId staticIdCounter;
};

class Sensor : public b2Fixture
{
public:
	Sensor(b2Fixture* owningFixture) : owningFixture(owningFixture), sensorId(staticIdCounter++) {}

	SensorId GetSensorId() const { return sensorId; }
	b2Fixture* GetOwningFixture() const { return owningFixture; }

private:
	b2Fixture* owningFixture;

	SensorId sensorId;
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
	//b2FixtureDef fixtureDef;

	//TODO мб небезопасно хранить по значению
	//std::vector<b2FixtureDef> fixtureDefVector {};
	std::unordered_map<FixtureId, Fixture*> fixtures{};
	//std::vector<b2Fixture*> fixturesVector {};

	EntityId bodyOwnerId;
};
