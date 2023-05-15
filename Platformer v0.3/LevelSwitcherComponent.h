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

	void SwitchLevel(SceneId nextLevel)
	{
		objectContext.sceneManager->SwitchToScene(nextLevel);
	}

	void SetLevelToSwitch(SceneId levelToSwitch)
	{
		this->levelToSwitch = levelToSwitch;
	}

private:
	SceneId levelToSwitch;
};

