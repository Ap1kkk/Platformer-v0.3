#include "UIButton.h"

void UIButton::Awake()
{
	Initialize();
	AddSpriteComponent(drawLayer);
	AddTextComponent(drawLayer);
	SetTexture("floor.png");
	drawableTextComponent->SetFont(AssetAllocator::GetFont(AssetAllocator::GetPath() + "Fonts/calibri.ttf"));
	drawableTextComponent->SetText("213455");
	drawableTextComponent->SetFillColor(sf::Color::Red);
	//drawableTextComponent->SetPositionOffset(sf::Vector2f(0.f, -20.f));
	SetUIPosition(position);
	spriteBounds = drawableSpriteComponent->GetSpriteBounds();
}

void UIButton::CaptureMousePosition()
{
	auto mousePosition = sf::Mouse::getPosition(objectContext.window->GetWindow());

	mousePosition.x -= WINDOW_WIDTH / 2;
	mousePosition.y -= WINDOW_HEIGHT / 2;

	if (spriteBounds.contains(mousePosition.x, mousePosition.y))
	{
		OnButtonHover();
		if (Input::IsKeyDown(Input::Key::LMouseButton))
		{
			OnButtonClick();
		}
	}
}

void UIButton::UpdateUI()
{
	CaptureMousePosition();
}

void UIButton::SetPosition(sf::Vector2f position)
{
	this->position = position;
}

void UIButton::SetPosition(float x, float y)
{
	position.x = x;
	position.y = y;
}

void UIButton::SetDrawLayer(DrawLayer drawlayer)
{
	this->drawLayer = drawLayer;
}
