#pragma once

#include "DataTypes.h"

class IAnimationState
{
public:
	virtual ~IAnimationState() {}

	virtual void Update() = 0;

	virtual void OnStateEnter() = 0;
	virtual void OnStateExit() = 0;

	virtual void OnNonCyclicAnimEnded() {}
	void SetOwnerId(EntityId ownerId) { this->ownerId = ownerId; }

protected:
	EntityId ownerId;
};

