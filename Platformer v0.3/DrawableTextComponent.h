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
	}
	void SetRotation(float angleInDeg) override
	{
		text.setRotation(angleInDeg);
	}

	void SetFont(sf::Font& font)
	{
		text.setFont(font);
	}
	void SetText(std::string string);

	void SetTextSize(unsigned int size)
	{
		text.setCharacterSize(size);
	}
	void SetFillColor(const sf::Color& color)
	{
		text.setFillColor(color);
	}
	void SetOutlineColor(const sf::Color& color)
	{
		text.setOutlineColor(color);
	}
	void SetOutlineThickness(float thickness)
	{
		text.setOutlineThickness(thickness);
	}

	void SetPositionOffset(const sf::Vector2f& offset)
	{
		positionOffset = offset;
	}

	void OnEnable() override
	{
		EventData data(EventType::OnTextDrawableEnabled);
		
		auto userData = new ComponentUserData;
		userData->component = this;

		data.id = componentId;
		data.userData = userData;

		Event::Invoke(data);
	}

	void OnDisable() override
	{
		EventData data(EventType::OnTextDrawableDisabled);
		
		auto userData = new ComponentUserData;
		userData->component = this;

		data.id = componentId;
		data.userData = userData;

		Event::Invoke(data);
	}

	void OnDestroy() override
	{
		EventData data(EventType::OnTextDrawableDestroyed);

		auto userData = new ComponentUserData;
		userData->component = this;

		data.id = ownerId;
		data.userData = userData;

		Event::Invoke(data);
	}

private:
	sf::Text text;
	sf::Vector2f positionOffset;
};

