#pragma once

#include "Window.h"
#include "IEventSystem.h"
#include "ISceneManager.h"

struct ObjectContext
{
	Window* window;
	IEventSystem* eventSystem;
	ISceneManager* sceneManager;
};