#include "UIButton.h"

void UIButton::CaptureMousePosition()
{
	auto mousePosition = sf::Mouse::getPosition(objectContext.window->GetWindow());

	mousePosition.x -= WINDOW_WIDTH / 2;
	mousePosition.y -= WINDOW_HEIGHT / 2;

	//Debug::Log(std::to_string(mousePosition.x) + "; " + std::to_string(mousePosition.y));

	if (spriteBounds.contains(mousePosition.x, mousePosition.y))
	{
		//Debug::Log("Intersect");
		OnButtonHover();
		if (Input::IsKeyDown(Input::Key::LMouseButton))
		{
			Debug::Log("Click");
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
