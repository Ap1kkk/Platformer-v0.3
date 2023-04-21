#pragma once

#include "Window.h"
#include "IEventSystem.h"

struct ObjectContext
{
	Window* window;
	IEventSystem* eventSystem;
};