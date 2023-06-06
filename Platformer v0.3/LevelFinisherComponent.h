#pragma once

#include "IComponent.h"

#include "Input.h"
#include "SaveManager.h"

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
		SaveManager::SetIsGameWon();
		objectContext.sceneManager->SwitchToScene(GameLevels::MainMenu);
	}

};

