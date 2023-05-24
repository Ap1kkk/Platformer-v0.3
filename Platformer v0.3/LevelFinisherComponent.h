#pragma once

#include "IComponent.h"

#include "Input.h"

class LevelFinisherComponent : public IComponent
{
public:

	void Update() override
	{
		if (Input::IsKeyDown(Input::Key::E))
		{
			FinishLevel();
		}
	}

	void FinishLevel()
	{
		objectContext.sceneManager->SwitchToScene(GameLevels::FirstScene);
	}

};

