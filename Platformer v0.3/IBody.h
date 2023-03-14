#pragma once

#include "box2d/box2d.h"
#include "Debug.h"
#include "DataTypes.h"

class IBody
{
public:
	IBody() {}
	virtual ~IBody()
	{
		//Debug::LogWarning("Destructor", typeid(*this).name());
	}

	inline void SetBodyOwner(EntityId id) { bodyOwnerId = id; }
	inline EntityId GetBodyOwner() const { return bodyOwnerId; }

	b2Body* GetBody() { return body; }
	void SetBody(b2Body* body) { this->body = body; }
	
protected:
	b2Body* body;
	b2BodyDef bodyDef;
	b2FixtureDef fixtureDef;

	EntityId bodyOwnerId;
};

