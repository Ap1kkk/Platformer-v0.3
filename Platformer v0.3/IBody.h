#pragma once

#include <vector>

#include "box2d/box2d.h"
#include "Debug.h"
#include "DataTypes.h"

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
	b2FixtureDef fixtureDef;

	//TODO �� ����������� ������� �� ��������
	std::vector<b2FixtureDef> fixtureDefVector{};
	std::vector<b2Fixture*> fixturesVector {};

	EntityId bodyOwnerId;
};
