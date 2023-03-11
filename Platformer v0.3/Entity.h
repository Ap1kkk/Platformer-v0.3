#pragma once

#include <string>

#include "SFML/Graphics.hpp"
#include "box2d/box2d.h"

#include "AssetAllocator.h"

#include "Debug.h"

typedef unsigned int EntityID;

class Entity : public sf::Sprite
{
public:
	sf::Vector2f velocity;

	Entity(b2World* world);

	virtual void Load(std::string filename, bool dynamic);

	virtual void Update(float deltaTime);

	bool CheckCollision(Entity* entity);

	virtual void Collision(Entity* entity);

	unsigned int GetId() const;

	int GroupID();

	int Active();

	void Destroy();
	b2Body* body;

	~Entity();
protected:
	int active;
	int groupId;
	b2World* world;
	b2BodyDef* bodyDef;
	b2PolygonShape* shape;
	b2FixtureDef* fixtureDef;
private:
	sf::Texture* texture;
	std::pair<sf::Vector2f, sf::Vector2u> drawableCollider;

	EntityID entityId;
	static EntityID idCounter;
};

