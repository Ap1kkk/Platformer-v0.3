#pragma once

#include "EventData.h"

enum class FaceDirection
{
	Left = -1,
	Right = 1
};

struct PlayerTurnedFaceData : public UserEventData
{
	FaceDirection direction;
};