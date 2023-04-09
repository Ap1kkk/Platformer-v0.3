#include "UIButton.h"

void UIButton::Awake()
{
	Initialize(true, drawLayer);
	SetTexture("floor.png");
	SetUIPosition(position);
	spriteBounds = drawableComponent->GetSpriteBounds();
}

void UIButton::CaptureMousePosition()
{
	//auto mousePosition = CorrectMouseCoordinates(sf::Mouse::getPosition(objectContext.window->GetWindow()));
	auto mousePosition = sf::Mouse::getPosition(objectContext.window->GetWindow());

	mousePosition.x -= WINDOW_WIDTH / 2;
	mousePosition.y -= WINDOW_HEIGHT / 2;


	if (spriteBounds.contains(mousePosition.x, mousePosition.y))
	{
		Debug::Log("Intersection");
	}
	//Debug::Log("===");
	Debug::Log(sf::Vector2f(mousePosition));
	//Debug::Log(sf::Vector2f(spriteBounds.left, spriteBounds.top));
	//Debug::Log("===");

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
