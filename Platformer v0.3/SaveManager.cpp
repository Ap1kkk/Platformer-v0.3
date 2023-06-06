#include "SaveManager.h"

bool SaveManager::isGameLoaded = false;
bool SaveManager::isGameOver = false;
bool SaveManager::isGameWon = false;

GameLevels SaveManager::activeScene = GameLevels::FirstScene;
GameLevels SaveManager::lastSavedScene = GameLevels::FirstScene;

int SaveManager::playerHp = DEFAULT_PLAYER_HP;
int SaveManager::savedPlayerHp = DEFAULT_PLAYER_HP;
sf::Vector2f SaveManager::playerPosition = { 0.f, 0.f };
sf::Vector2f SaveManager::savedPlayerPosition = {0.f, 0.f};
std::map<ChunkId, std::vector<sf::Vector2f>> SaveManager::activeChunks = {};
std::map<ChunkId, std::vector<sf::Vector2f>> SaveManager::savedChunks = {};
std::map<ChunkId, int> SaveManager::activeEnemiesHp = {};
std::map<ChunkId, int> SaveManager::savedEnemiesHp = {};

std::map<ChunkId, std::pair<EntityId, short>> SaveManager::enemies = {};

void SaveManager::ParceFromFile()
{
	std::string line;

	std::ifstream in(SAVE_FILENAME);
	if (in.is_open())
	{
		while (std::getline(in, line))
		{
			if (line[0] == 'h')
			{
				savedPlayerHp = std::atoi(line.substr(1, line.length() - 1).c_str());
				playerHp = savedPlayerHp;
			}
			if (line[0] == 's')
			{
				auto scene = std::atoi(line.substr(1, line.length() - 1).c_str());
				lastSavedScene = (GameLevels)scene;
				activeScene = lastSavedScene;
			}
			if (line[0] == 'p')
			{
				auto vectorStr = line.substr(1, line.length() - 1);
				
				auto delimiterIndex = vectorStr.find("/");
				if (delimiterIndex != std::string::npos)
				{
					float xPos = (float)std::atof(vectorStr.substr(0, delimiterIndex).c_str());
					float yPos = (float)std::atof(vectorStr.substr(delimiterIndex + 1, vectorStr.length() - 1).c_str());
					savedPlayerPosition = { xPos, yPos };
					playerPosition = savedPlayerPosition;
				}
			}
			if (line[0] == 'c')
			{
				//TODO работает только для одной добавленной позиции
				auto mainDelimiterIndex = line.find("|");
				if (mainDelimiterIndex != std::string::npos)
				{
					ChunkSpawnId chunkSpawnId = std::atoi(line.substr(1, mainDelimiterIndex).c_str());
					std::vector<sf::Vector2f> positions = {};

					auto vectorStr = line.substr(mainDelimiterIndex + 1, line.length() - 1);

					auto delimiterIndex = vectorStr.find("/");
					if (delimiterIndex != std::string::npos)
					{
						sf::Vector2f spawnPosition;
						float xPos = (float)std::atof(vectorStr.substr(0, delimiterIndex).c_str());
						float yPos = (float)std::atof(vectorStr.substr(delimiterIndex + 1, vectorStr.length() - 1).c_str());
						spawnPosition = { xPos, yPos };
						positions.push_back(spawnPosition);
					}
					savedChunks[chunkSpawnId] = positions;
				}
			}
			if (line[0] == 'e')
			{
				//TODO работает только для одной добавленной позиции
				auto mainDelimiterIndex = line.find("|");
				if (mainDelimiterIndex != std::string::npos)
				{
					ChunkSpawnId chunkSpawnId = std::atoi(line.substr(1, mainDelimiterIndex).c_str());
					
					auto enemyHp = std::atoi(line.substr(mainDelimiterIndex + 1, line.length() - 1).c_str());
					savedEnemiesHp[chunkSpawnId] = enemyHp;
					activeEnemiesHp = savedEnemiesHp;
				}
			}
		}
		activeChunks = savedChunks;
	}
}

void SaveManager::SaveToFile()
{
	int tunnelNumbers[20] =
	{
		11,	16,	15,	17,	8,
		6,	5,	14,	15,	7,
		18,	19,	14,	16,	10,
		20,	16,	15,	1,	7
	};

	std::ofstream out;
	out.open(SAVE_FILENAME);
	if (out.is_open())
	{
		out << "h " + std::to_string(savedPlayerHp) << std::endl;
		out << "p " + std::to_string(savedPlayerPosition.x) + " / " + std::to_string(savedPlayerPosition.y) << std::endl;
		out << "s " + std::to_string((short)lastSavedScene) << std::endl;

		for (int i = 0; i < 20; ++i)
		{
			if (i < 10)
			{
				out << "c 0" + std::to_string(i);

			}
			else
			{
				out << "c " + std::to_string(i);
			}
			auto itr = savedChunks.find(i);
			if (itr != savedChunks.end())
			{
				for (auto& pos : itr->second)
				{
					out << " | " + std::to_string(pos.x) + " / " + std::to_string(pos.y);
				}
			}
			out << std::endl;
		}

		for (int i = 0; i < 20; ++i)
		{
			if (i < 10)
			{
				out << "e 0" + std::to_string(i);

			}
			else
			{
				out << "e " + std::to_string(i);
			}
			auto itr = savedChunks.find(i);
			if (itr != savedChunks.end())
			{
				if (!itr->second.empty())
				{
					out << " | " + std::to_string(savedEnemiesHp[i]);
				}
			}
			out << std::endl;
		}
	}
	out.close();
}
