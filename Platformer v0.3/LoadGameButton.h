#pragma once

#include "UIButton.h"
#include "Debug.h"

#include "SaveManager.h"

class LoadGameButton : public UIButton
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
		Debug::Log("Game Load logic");
		SaveManager::SetIsGameLoaded();
		SaveManager::ResetIsGameOver();
		SaveManager::ResetIsGameWon();
		auto startScene = SaveManager::GetLastSavedScene();
		if (startScene != GameLevels::MainMenu)
		{
			objectContext.sceneManager->SwitchToScene(startScene);
		}
		
	}

private:
	std::string buttonText = "Load game";

	Filename buttonTexture = "Menu/load_button.png";

	//unsigned short textSize = 26;
	//sf::Color textColor = sf::Color::Red;
	//Filename fontFilename = "Fonts/BenguiatStd-Bold.otf";
	//sf::Vector2f textOffset = { 0.f, 10.f };

	DrawLayer drawLayer = 300;
};
