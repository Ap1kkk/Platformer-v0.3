#pragma once

#include "EventData.h"

struct EnemyDamagedData : public UserEventData
{
	ChunkSpawnId chunkSpawnId;
	int hpAfterDamage;
};