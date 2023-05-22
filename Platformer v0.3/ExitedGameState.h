#pragma once

#include "GameState.h"
#include "SharedContext.h"
#include "Debug.h"

class ExitedGameState : public GameState
{
public:
	ExitedGameState(SharedContext context);

	void EnterState() override;
	void Update() override;
	void LeaveState() override;

private:
	SharedContext sharedContext;
};

