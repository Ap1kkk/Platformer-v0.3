#pragma once

#include <string>
#include <map>
#include <fstream>

#include "DataTypes.h"

#include "EventListener.h"
#include "OnEntityDiedData.h"

#include "TunnelCollidersData.h"

#include "PlayerDataRequestData.h"
#include "EnemyDamagedData.h"

#include "Debug.h"

const std::string SAVE_FILENAME = "../Assets/Saves/save.txt";

const short DEFAULT_PLAYER_HP = 100;
const short DEFAULT_ENEMY_HP = 100;

class SaveManager : public EventListener
{
public:
	void SubscribeOnEvents()
	{
		SubscribeOnEvent(EventType::OnPlayerDataCallback);
		SubscribeOnEvent(EventType::OnEntityDiedEvent);
		SubscribeOnEvent(EventType::OnEnemyDamaged);
	}

	static void ParceFromFile();
	static void SaveToFile();

	static void SaveGame() 
	{ 
		SetIsGameLoaded();

		lastSavedScene = activeScene;
		savedChunks = activeChunks;
		EventData data(EventType::OnPlayerDataRequest);
		Event::Invoke(data);
		savedPlayerHp = playerHp;
		savedPlayerPosition = playerPosition;
		savedEnemiesHp = activeEnemiesHp;
		SaveToFile();
	}

	static bool IsGameLoaded() { return isGameLoaded; }
	static void SetIsGameLoaded() { isGameLoaded = true; }
	static void ResetIsGameLoaded() { isGameLoaded = false; }

	static bool IsGameOver() { return isGameOver; }
	static void SetIsGameOver() { isGameOver = true; }
	static void ResetIsGameOver() { isGameOver = false; }

	static bool IsGameWon() { return isGameWon; }
	static void SetIsGameWon() { isGameWon = true; }
	static void ResetIsGameWon() { isGameWon = false; }

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
			activeChunks[chunkNumber] = enemyPositions;
			activeEnemiesHp[chunkNumber] = DEFAULT_ENEMY_HP;
		}

	}

	static void SetActiveScene(GameLevels scene) { activeScene = scene; }
	static GameLevels GetActiveScene() { return activeScene; }
	static GameLevels GetLastSavedScene() { return lastSavedScene; }

	static sf::Vector2f GetPlayerPosition() { return playerPosition; }
	static int GetSavedPlayerHealthPoints() { return savedPlayerHp; }

	static std::vector<sf::Vector2f> GetEnemySpawnData(ChunkId chunkId)
	{
		auto itr = savedChunks.find(chunkId);
		if (itr != savedChunks.end())
		{
			return itr->second;
		}
		else
		{
			return {};
		}
	}
	static int GetEnemyHealthPoints(ChunkId chunkId)
	{
		auto itr = savedEnemiesHp.find(chunkId);
		if (itr != savedEnemiesHp.end())
		{
			return itr->second;
		}
		else
		{
			return 0;
		}
	}


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
				auto enemiesItr = activeEnemiesHp.find(userData->chunkId);
				if (enemiesItr != activeEnemiesHp.end())
				{
					activeEnemiesHp.erase(enemiesItr);
				}
				auto chunkItr = activeChunks.find(userData->chunkId);
				if (chunkItr != activeChunks.end())
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
		if (data.eventType == EventType::OnEnemyDamaged)
		{
			auto userData = static_cast<EnemyDamagedData*>(data.userData);

			auto itr = activeChunks.find(userData->chunkSpawnId);
			if (itr != activeChunks.end())
			{
				if (!itr->second.empty())
				{
					activeEnemiesHp[userData->chunkSpawnId] = userData->hpAfterDamage;
				}
			}
		}
	}

private:
	static bool isGameLoaded;
	static bool isGameOver;
	static bool isGameWon;

	static GameLevels activeScene;
	static GameLevels lastSavedScene;

	static int playerHp;
	static int savedPlayerHp;
	static sf::Vector2f playerPosition;
	static sf::Vector2f savedPlayerPosition;
	static std::map<ChunkId, std::vector<sf::Vector2f>> activeChunks;
	static std::map<ChunkId, std::vector<sf::Vector2f>> savedChunks;
	static std::map<ChunkId, int> activeEnemiesHp;
	static std::map<ChunkId, int> savedEnemiesHp;

	static std::map<ChunkId, std::pair<EntityId, short>> enemies;
};

