#pragma once

#include "GameState.h"
#include "SharedContext.h"
#include "Debug.h"

class CreatedGameState : public GameState
{
public:
	CreatedGameState(SharedContext context);

	void EnterState() override;
	void Update() override;
	void LeaveState() override;

private:
	SharedContext sharedContext;
};

