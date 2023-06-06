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
		SetComponentLayer(ComponentOrder::Health);
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

	int TakeDamage(DamageData* damageData)
	{
		Debug::Log("damage taken");
		return ProcessDamage(damageData);

	}
	void SetHealthPoints(int healthPoints)
	{
		this->healthPoints = healthPoints;
	}

	void SetDrawableComponent(DrawableTextComponent* drawable)
	{
		this->drawable = drawable;
	}

	void SetTextOffset(sf::Vector2f offset)
	{
		textOffset = offset;
	}
	
	void SetIsPlayer() { isPlayer = true; }
	void SetEnemyData(ChunkId chunkId, sf::Vector2f spawnOffset) 
	{
		this->chunkId = chunkId;
		this->spawnOffset = spawnOffset;
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
	int ProcessDamage(DamageData* damageData)
	{
		healthPoints -= damageData->value;

		if (!IsAlive())
		{
			healthPoints = 0;
		}
		drawable->SetText(std::to_string(healthPoints));

		if (!IsAlive())
		{
			EventData eventData(EventType::OnEntityDiedEvent);

			auto userData = new OnEntityDiedData;
			userData->entityId = ownerId;
			if (isPlayer)
			{
				userData->isPlayer = true;
			}
			else
			{
				userData->chunkId = chunkId;
				userData->spawnPosition = spawnOffset;
			}
			eventData.userData = userData;

			Event::Invoke(eventData);

			delete userData;
		}
		if (IsAlive())
		{
			return healthPoints;
		}
		else
		{
			return 0;
		}
	}

	bool IsAlive() { return healthPoints > 0; }

	int healthPoints;

	DrawableTextComponent* drawable;

	unsigned short textSize = 26;
	sf::Color textColor = sf::Color::Red;
	Filename fontFilename = "Fonts/BenguiatStd-Bold.otf";
	sf::Vector2f textOffset = { 0.f, -120.f };

	bool isPlayer;
	ChunkId chunkId;
	sf::Vector2f spawnOffset;
};

