#pragma once

#include "UIButton.h"
#include "Debug.h"

#include "SaveManager.h"

class SaveAndExitButton : public UIButton
{
public:

	void Awake() override
	{
		Initialize();
		AddSpriteComponent(drawLayer);
		AddTextComponent(drawLayer);

		SetTexture(buttonTexture);
		//drawableTextComponent->SetFont(AssetAllocator::GetFont(AssetAllocator::GetPath() + fontFilename));
		//drawableTextComponent->SetText(buttonText);
		//drawableTextComponent->SetTextSize(textSize);
		//drawableTextComponent->SetFillColor(textColor);
		//drawableTextComponent->SetPositionOffset(textOffset);
		SetUIPosition(position);

		spriteBounds = drawableSpriteComponent->GetSpriteBounds();
		spriteBounds.left += position.x;
		spriteBounds.top += position.y;
	}

	void OnButtonClick() override
	{
		Debug::Log("Game Save and Exit logic");

		//TODO добавить логику сохранения

		if(objectContext.gameStateMachine->IsPaused())
		{
			objectContext.gameStateMachine->Contintue();
			//SaveManager::SaveGame();
			objectContext.sceneManager->SwitchToScene(GameLevels::MainMenu);
		}
	}

private:
	std::string buttonText = "Save and exit game";

	Filename buttonTexture = "Menu/exit_pause_button.png";

	//unsigned short textSize = 26;
	//sf::Color textColor = sf::Color::Red;
	//Filename fontFilename = "Fonts/BenguiatStd-Bold.otf";
	//sf::Vector2f textOffset = { 0.f, 10.f };

	DrawLayer drawLayer = 300;
};
