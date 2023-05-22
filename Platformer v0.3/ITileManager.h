#pragma once

#include "DataTypes.h"

class ITileManager
{
public:
	virtual void DestroyTile(EntityId entityId) = 0;
};