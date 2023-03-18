#pragma once

#include "IComponent.h"
#include "IBody.h"
#include "PhysicSystem.h"
#include "TransformComponent.h"
#include "Debug.h"

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

	//TODO доработать
	void AddFixtureDef(b2FixtureDef newFixtureDef);

	/// <summary>
	/// Make the box2d system destroy a body fixture
	/// </summary>
	/// <param name="exitingFixture"></param>
	void DeleteFixtureDef(b2Fixture* exitingFixture);

	//TODO доработать и узнать про динамическое изменение типа тела
	void SetBodyType(b2BodyType type);

	void EarlyUpdate() override;
	void Update() override;
	void LateUpdate() override;

	void OnDestroy() override;

private:
	sf::Vector2f bodyPosition; 
	TransformComponent* ownerTransform;
};

