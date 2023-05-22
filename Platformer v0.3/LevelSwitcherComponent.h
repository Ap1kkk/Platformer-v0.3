#pragma once

#include "IComponent.h"

#include "Input.h"

class LevelSwitcherComponent : public IComponent
{
public:

	void Update() override
	{
		if (Input::IsKeyDown(Input::Key::E))
		{
			SwitchLevel(levelToSwitch);
		}
	}

	void SwitchLevel(GameLevels nextLevel)
	{
		objectContext.sceneManager->SwitchToScene((short)nextLevel);
	}

	void SetLevelToSwitch(GameLevels levelToSwitch)
	{
		this->levelToSwitch = levelToSwitch;
	}

private:
	GameLevels levelToSwitch;
};

