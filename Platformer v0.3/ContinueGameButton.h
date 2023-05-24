#pragma once

#include "UIButton.h"
#include "Debug.h"

class ContinueGameButton : public UIButton
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
		Debug::Log("Game continue logic");
		if (objectContext.gameStateMachine->IsPaused())
		{
			objectContext.gameStateMachine->Contintue();
		}
	}

private:
	std::string buttonText = "Continue game";

	Filename buttonTexture = "Menu/continue_button.png";

	//unsigned short textSize = 26;
	//sf::Color textColor = sf::Color::Red;
	//Filename fontFilename = "Fonts/BenguiatStd-Bold.otf";
	//sf::Vector2f textOffset = { 0.f, 10.f };

	DrawLayer drawLayer = 300;
};
