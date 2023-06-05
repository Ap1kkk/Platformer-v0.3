#pragma once

#include <string>
#include <map>
#include <fstream>

#include "DataTypes.h"

#include "EventListener.h"
#include "OnEntityDiedData.h"

#include "TunnelCollidersData.h"

#include "PlayerDataRequestData.h"

const std::string SAVE_FILENAME = "../Assets/Saves/save.txt";

const short DEFAULT_PLAYER_HP = 100;

class SaveManager : public EventListener
{
public:
	void SubscribeOnEvents()
	{
		SubscribeOnEvent(EventType::OnPlayerDataCallback);
		SubscribeOnEvent(EventType::OnEntityDiedEvent);
	}

	static void ParceFromFile();
	static void SaveToFile();

	static void SaveGame() 
	{ 
		SetIsGameLoaded();

		EventData data(EventType::OnPlayerDataRequest);
		Event::Invoke(data);

		SaveToFile();
	}

	static bool IsGameLoaded() { return isGameLoaded; }
	static void SetIsGameLoaded() { isGameLoaded = true; }
	static void ResetIsGameLoaded() { isGameLoaded = false; }

	static void SetDefaultValues() 
	{
		playerHp = DEFAULT_PLAYER_HP;
		activeScene = GameLevels::FirstScene;
		int tunnelNumbers[20] =
		{
			11,	16,	15,	17,	8,
			6,	5,	14,	15,	7,
			18,	19,	14,	16,	10,
			20,	16,	15,	1,	7
		};

		for (auto chunkNumber = 0; chunkNumber < 20; ++chunkNumber)
		{
			auto enemyPositions = TunnelCollidersData::GetEnemySpawnData(tunnelNumbers[chunkNumber]);
			chunks[chunkNumber] = enemyPositions;
		}

	}

	static void SetActiveScene(GameLevels scene) { activeScene = scene; }
	static GameLevels GetActiveScene() { return activeScene; }

	static sf::Vector2f GetPlayerPosition() { return playerPosition; }

	static std::vector<sf::Vector2f> GetEnemySpawnData(ChunkId chunkId)
	{
		auto itr = chunks.find(chunkId);
		if (itr != chunks.end())
		{
			return itr->second;
		}
		else
		{
			return {};
		}
	}

	//static void SetEnemyPosition(ChunkId chunkId, sf::Vector2f spawnPosition)
	//{
	//	auto chunkItr = chunks.find(chunkId);
	//	if (chunkItr != chunks.end())
	//	{
	//		for (auto position = chunkItr->second.begin(); position != chunkItr->second.end(); ++position)
	//		{
	//			if (*position == spawnPosition)
	//			{
	//				chunkItr->second.erase(position);
	//			}
	//		}
	//	}
	//}

	void OnEventHappened(EventData& data) override
	{
		if (data.eventType == EventType::OnEntityDiedEvent)
		{
			auto userData = static_cast<OnEntityDiedData*>(data.userData);

			if (userData->isPlayer)
			{
				//TODO переделать
				playerHp = DEFAULT_PLAYER_HP;
			}
			else
			{
				auto chunkItr = chunks.find(userData->chunkId);
				if (chunkItr != chunks.end())
				{
					for (auto position = chunkItr->second.begin(); position != chunkItr->second.end(); ++position)
					{
						if (*position == userData->spawnPosition)
						{
							position = chunkItr->second.erase(position);
							break;
						}
					}
				}
			}

		}
		if (data.eventType == EventType::OnPlayerDataCallback)
		{
			auto userData = static_cast<PlayerDataRequestData*>(data.userData);

			playerPosition = userData->position;
			playerHp = userData->healthPoints;
		}
	}

private:
	static bool isGameLoaded;

	static GameLevels activeScene;

	static short playerHp;
	static sf::Vector2f playerPosition;
	static std::map<ChunkId, std::vector<sf::Vector2f>> chunks;
	static std::map<ChunkId, std::pair<EntityId, short>> enemies;
};

