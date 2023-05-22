#pragma once

#include "GameState.h"
#include "Time.h"
#include "SharedContext.h"
#include "Debug.h"

class RunnedGameState : public GameState
{
public:
	RunnedGameState(SharedContext context);

	void EnterState() override;
	void Update() override;
	void LeaveState() override;

private:
	SharedContext sharedContext;

};

