#include "SaveManager.h"

bool SaveManager::isGameLoaded = false;

GameLevels SaveManager::activeScene = GameLevels::FirstScene;

short SaveManager::playerHp = 100;
sf::Vector2f SaveManager::playerPosition = {0.f, 0.f};
std::map<ChunkId, std::vector<sf::Vector2f>> SaveManager::chunks = {};
std::map<ChunkId, std::pair<EntityId, short>> SaveManager::enemies = {};

void SaveManager::ParceFromFile()
{
	std::string line;

	std::ifstream in(SAVE_FILENAME);
	if (in.is_open())
	{
		while (std::getline(in, line))
		{
			std::cout << line << std::endl;

		}
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
		out << "h " + std::to_string(playerHp) << std::endl;
		out << "p " + std::to_string(playerPosition.x) + " / " + std::to_string(playerPosition.y) << std::endl;
		out << "s " + std::to_string((short)activeScene) << std::endl;

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
			auto itr = chunks.find(i);
			if (itr != chunks.end())
			{
				for (auto& pos : itr->second)
				{
					out << " | " + std::to_string(pos.x) + " / " + std::to_string(pos.y);
				}
			}
			out << std::endl;
		}

	}
	out.close();
}
