#pragma once

#include "IComponent.h"
#include "IBody.h"
#include "PhysicSystem.h"
#include "TransformComponent.h"
#include "Debug.h"

#include "FixtureManager.h"
/// <summary>
/// Responsible for physics part of an object
/// Contains physic body of an object
/// </summary>
class PhysicComponent : public IComponent, public IBody
{
public:
	PhysicComponent();
	~PhysicComponent() {}
	
	/// <summary>
	/// Represents physic body position
	/// </summary>
	/// <returns>Vector2f with position x and y coord </returns>
	sf::Vector2f GetBodyPosition();
	
	/// <summary>
	/// Represents physic body angle in radians
	/// </summary>
	/// <returns>Body's angle</returns>
	float GetBodyAngle();

	/// <summary>
	/// Returns a pointer to a physic body of an object
	/// </summary>
	/// <returns></returns>
	b2Body* GetBody();

	/// <summary>
	/// Sets the pointer to owner's TransformComponent
	/// </summary>
	void Initialize(TransformComponent* transform);

	/// <summary>
	/// Make the box2d system create the body
	/// </summary>
	void InitializeBody();

	void SetBodyDef(b2BodyDef newBodyDef);

	//TODO переработать
	Fixture* AddFixture(b2FixtureDef& newFixtureDef);

	/// <summary>
	/// Make the box2d system destroy a body fixture
	/// </summary>
	/// <param name="exitingFixture"></param>
	void DeleteFixture(FixtureId fixtureId);

	Sensor* AddSensor(b2FixtureDef& newFixtureDef)
	{
		auto sensor = FixtureManager::CreateSensor(newFixtureDef, body, ownerId);
		auto newSensorId = sensor->GetSensorId();
		sensors.emplace(std::make_pair(newSensorId, sensor));

		Debug::LogInfo("Added sensor with SensorId: " + std::to_string(newSensorId), typeid(*this).name());

		return sensor;
	}

	void RemoveSensor(SensorId sensorId)
	{
		auto itr = sensors.find(sensorId);
		if (itr != sensors.end())
		{
			FixtureManager::DestroySensor(itr->second, body);
			sensors.erase(itr);
		}
		else
		{
			Debug::LogWarning("Can't remove sensor with SensorId: " + std::to_string(sensorId) + "\nSensor not found", typeid(*this).name());
		}
	}


	//TODO доработать и узнать про динамическое изменение типа тела
	void SetBodyType(b2BodyType type);

	void LateUpdate() override;

	void OnDestroy() override;

private:
	sf::Vector2f bodyPosition;
	float bodyAngle;
	TransformComponent* ownerTransform;

	std::unordered_map<SensorId, Sensor*> sensors;
};

