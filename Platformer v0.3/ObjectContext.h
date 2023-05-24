#pragma once

#include "Window.h"
#include "IEventSystem.h"
#include "ISceneManager.h"
#include "IGameStateMachine.h"

struct ObjectContext
{
	Window* window;
	IEventSystem* eventSystem;
	ISceneManager* sceneManager;
	IGameStateMachine* gameStateMachine;
};