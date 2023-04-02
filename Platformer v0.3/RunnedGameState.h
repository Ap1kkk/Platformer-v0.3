#pragma once

#include "GameState.h"
#include "Time.h"
#include "SharedContext.h"
#include "Debug.h"

class RunnedGameState : public GameState
{
public:
	RunnedGameState(SharedContext context) : sharedContext(context)
	{
		SetStateType(GameStateType::Runned);
	}

	void EnterState() override
	{
		//TODO перенести логику создания всех сцен
		Debug::Log("Entered Runned state");

	}
	void Update() override
	{
		//Debug::Log("Updating Runned state");
		sharedContext.sceneManager->ProcessNotAwoken();
		sharedContext.sceneManager->CaptureEvents();

		sharedContext.physicSystem->Update(Time::FixedDeltaTime(), 6, 2);

		sharedContext.sceneManager->EarlyUpdate();
		sharedContext.sceneManager->Update();
		sharedContext.sceneManager->LateUpdate();
		sharedContext.sceneManager->UpdateUI();
	}
	void LeaveState() override
	{
		Debug::Log("Leaving Runned state");
	}

private:
	SharedContext sharedContext;

};

