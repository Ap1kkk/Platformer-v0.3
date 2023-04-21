#pragma once

#include "GameState.h"

#include "SharedContext.h"
#include "SceneManager.h"
#include "FirstScene.h"
#include "PauseScene.h"

#include "OnEntityDestroyedEvent.h"
#include "EventSystem.h"
#include "EventListener.h"

#include "Debug.h"

class InitializedGameState : public GameState
{
public:
	InitializedGameState(SharedContext context);

	void EnterState() override;

	void Update() override;
	void LeaveState() override;

private:
	SharedContext sharedContext;

};

