#pragma once

#include "IComponent.h"

#include "Debug.h"

#include "Damageble.h"
#include "AssetAllocator.h"
#include "DrawableTextComponent.h"

const int START_HEALTH_POINTS = 100;

class Health : public IComponent
{
public:
	Health()
	{
		healthPoints = START_HEALTH_POINTS;
	}
	virtual ~Health()
	{

	}

	void Awake() override
	{
		drawable->SetFont(AssetAllocator::GetFont(AssetAllocator::GetPath() + fontFilename));
		drawable->SetText(std::to_string(healthPoints));
		drawable->SetTextSize(textSize);
		drawable->SetFillColor(textColor);
		drawable->SetPositionOffset(textOffset);
	}

	void TakeDamage(DamageData* damageData)
	{
		Debug::Log("damage taken");
		ProcessDamage(damageData);
		if (!IsAlive())
		{
			healthPoints = 0;
		}
		drawable->SetText(std::to_string(healthPoints));
	}

	void SetDrawableComponent(DrawableTextComponent* drawable)
	{
		this->drawable = drawable;
	}

	void SetTextOffset(sf::Vector2f offset)
	{
		textOffset = offset;
	}

	unsigned int GetHealthPoints()
	{
		return healthPoints;
	}

	void OnDestroy() override
	{

	}

private:
	//TODO добавить учет всевозможных сопротивлений и так далее
	void ProcessDamage(DamageData* damageData)
	{
		healthPoints -= damageData->value;

		if (!IsAlive())
		{
			EventData eventData(EventType::OnEntityDiedEvent);

			auto userData = new OnEntityDiedData;
			userData->entityId = ownerId;
			eventData.userData = userData;

			Event::Invoke(eventData);

			delete userData;
		}
	}

	bool IsAlive() { return healthPoints > 0; }

	int healthPoints;

	DrawableTextComponent* drawable;

	unsigned short textSize = 26;
	sf::Color textColor = sf::Color::Red;
	Filename fontFilename = "Fonts/BenguiatStd-Bold.otf";
	sf::Vector2f textOffset = { 0.f, -120.f };
};

