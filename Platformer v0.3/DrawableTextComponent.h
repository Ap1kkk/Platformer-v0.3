#pragma once

#include "DrawableComponent.h"

class DrawableTextComponent : public DrawableComponent
{
public:

	void Draw(Window* window) override
	{
		SynchronizeTransform();
		window->Draw(text);
	}

	void SetWorldPosition(sf::Vector2f& centerPosition) override
	{
		centerPosition += positionOffset;
		text.setPosition(centerPosition);
		//Debug::Log(centerPosition);
	}
	void SetRotation(float angleInDeg) override
	{
		text.setRotation(angleInDeg);
	}

	void SetFont(sf::Font& font)
	{
		text.setFont(font);
	}
	void SetText(std::string string)
	{
		text.setCharacterSize(24);
		text.setFillColor(sf::Color::Red);
		text.setString(string);

		auto rect = text.getGlobalBounds();
		text.setOrigin(rect.width / 2, rect.height / 2);
	}

	void SetPositionOffset(const sf::Vector2f& offset)
	{
		positionOffset = offset;
	}


private:
	sf::Text text;
	sf::Vector2f positionOffset;
};

