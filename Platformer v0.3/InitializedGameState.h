#pragma once

#include "GameState.h"

#include "SharedContext.h"
#include "SceneManager.h"

#include "FirstScene.h"
#include "PauseScene.h"
#include "MainScene.h"

#include "ShopLevel.h"

#include "FirstLevel.h"
#include "SecondLevel.h"
#include "ThirdLevel.h"
#include "FourthLevel.h"


#include "EventSystem.h"
#include "EventListener.h"
#include "IEvent.h"

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

