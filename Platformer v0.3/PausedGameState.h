#pragma once

#include "GameState.h"
#include "SharedContext.h"
#include "Debug.h"

class PausedGameState : public GameState
{
public:
	PausedGameState(SharedContext context);

	void EnterState() override;
	void Update() override;
	void LeaveState() override;

private:
	SharedContext sharedContext;
};

