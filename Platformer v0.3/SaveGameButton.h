#pragma once

#include "UIButton.h"
#include "Debug.h"

#include "SaveManager.h"

class SaveGameButton : public UIButton
{
public:

	void Awake() override
	{
		Initialize();
		AddSpriteComponent(drawLayer);
		AddTextComponent(drawLayer);

		SetTexture(buttonTexture);
		drawableTextComponent->SetFont(AssetAllocator::GetFont(AssetAllocator::GetPath() + fontFilename));
		drawableTextComponent->SetText(buttonText);
		drawableTextComponent->SetTextSize(textSize);

		drawableTextComponent->SetFillColor(sf::Color::Transparent);
		drawableTextComponent->SetOutlineColor(textColor);
		drawableTextComponent->SetOutlineThickness(thickness);

		drawableTextComponent->SetPositionOffset(textOffset);

		drawableTextComponent->Disable();

		SetUIPosition(position);

		spriteBounds = drawableSpriteComponent->GetSpriteBounds();
		spriteBounds.left += position.x;
		spriteBounds.top += position.y;
	}

	void OnButtonClick() override
	{
		Debug::Log("Game Save logic");
		SaveManager::SaveGame();
		drawableTextComponent->Enable();

	}

private:
	std::string buttonText = "Game saved";

	Filename buttonTexture = "Menu/save_pause_button.png";

	unsigned short textSize = 60;
	sf::Color textColor = sf::Color::Red;
	Filename fontFilename = "Fonts/BenguiatStd-Bold.otf";
	sf::Vector2f textOffset = { -310.f, 250.f };

	float thickness = 1.f;

	DrawLayer drawLayer = 300;
};



