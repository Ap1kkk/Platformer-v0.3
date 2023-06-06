#pragma once

#include "IBody.h"

class FixtureManager
{
public:

	static Fixture* CreateFixture(b2FixtureDef& fixtureDef, b2Body* body, EntityId ownerId)
	{
		Fixture* fixture = new Fixture(ownerId);
		FixtureId fixtureId = fixture->GetFixtureId();
		fixtureDef.userData.pointer = fixtureId;
		fixture->SetOwningFixture(body->CreateFixture(&fixtureDef));

		fixtures.emplace(std::make_pair(fixtureId, fixture));

		Debug::LogInfo("Created fixture with id: " + std::to_string(fixtureId), typeid(FixtureManager).name());

		return fixture;
	}

	static Fixture* GetFixture(FixtureId fixtureId)
	{
		auto itr = fixtures.find(fixtureId);
		if (itr != fixtures.end())
		{
			return itr->second;
		}
		else
		{
			Debug::LogError("Can't find fixture\nFixture with id: " + std::to_string(fixtureId) + " not found", typeid(FixtureManager).name());
			return nullptr;
		}
	}

	static void DestroyFixture(FixtureId fixtureId, b2Body* body)
	{
		auto itr = fixtures.find(fixtureId);
		if (itr != fixtures.end())
		{
			//body->DestroyFixture(itr->second->GetOwningFixture());
			AddToDestroyBuffer(itr->second, body);
			fixtures.erase(fixtureId);
			Debug::LogWarning("Deleted fixture with id: " + std::to_string(fixtureId), typeid(FixtureManager).name());
		}
		else
		{
			Debug::LogError("Can't delete fixture\nFixture with id: " + std::to_string(fixtureId) + " not found", typeid(FixtureManager).name());
		}
	}

	static Sensor* CreateSensor(b2FixtureDef& fixtureDef, b2Body* body, EntityId ownerId)
	{
		Sensor* sensor = new Sensor(ownerId);
		FixtureId fixtureId = sensor->GetFixtureId();
		fixtureDef.userData.pointer = fixtureId;
		sensor->SetOwningFixture(body->CreateFixture(&fixtureDef));

		fixtures.emplace(std::make_pair(fixtureId, sensor));

		Debug::LogInfo("Created sensor with fixtureId: " + std::to_string(fixtureId), typeid(FixtureManager).name());

		return sensor;
	}

	static void DestroySensor(Sensor* sensor, b2Body* body)
	{
		auto fixtureId = sensor->GetFixtureId();
		auto itr = fixtures.find(fixtureId);
		if (itr != fixtures.end())
		{
			//body->DestroyFixture(itr->second->GetOwningFixture());
			AddToDestroyBuffer(itr->second, body);
			fixtures.erase(fixtureId);
			Debug::LogWarning("Deleted sensor with fixtureId: " + std::to_string(fixtureId), typeid(FixtureManager).name());
		}
		else
		{
			Debug::LogError("Can't delete sensor\nSensor with id: " + std::to_string(fixtureId) + " not found", typeid(FixtureManager).name());
		}
	}

	static void AddToDestroyBuffer(Fixture* fixture, b2Body* body)
	{
		destroyBuffer.push_back(std::make_pair(fixture, body));
	}

	static void ClearDestroyBuffer()
	{
		for (auto& pair : destroyBuffer)
		{
			if (pair.first->GetUserData() != nullptr)
			{
				pair.first->GetUserData()->componentPtr = nullptr;
				pair.first->GetUserData()->damageble = nullptr;
				pair.first->GetUserData()->entityPtr = nullptr;
			}
			pair.second->DestroyFixture(pair.first->GetOwningFixture());
		}
		destroyBuffer.clear();
	}

private:
	static std::map<FixtureId, Fixture*> fixtures;
	static std::vector<std::pair<Fixture*, b2Body*>> destroyBuffer;
};
