#pragma once

#include <box2d/box2d.h>

#include <map>
#include <vector>

#include "Debug.h"

#define TUNNEL_CHUNK_NUMBER 4

struct ColliderData
{
	b2Vec2 centerPosition;
	b2PolygonShape shape;
};

using CollidersDataVector = std::vector<ColliderData>;
using EnemySpawnPositions = std::vector<sf::Vector2f>;

class TunnelCollidersData
{
public:
	TunnelCollidersData()
	{
		GenerateData();
	}

	static CollidersDataVector GetCollidersData(short tunnelNumber)
	{
		auto itr = collidersMap.find(tunnelNumber);

		if (itr != collidersMap.end())
		{
			return itr->second;
		}
		else
		{
			Debug::LogError("Wrong tunnel number", typeid(TunnelCollidersData).name());
		}
	}

	static EnemySpawnPositions GetEnemySpawnData(short tunnelNumber)
	{
		auto itr = enemySpawnMap.find(tunnelNumber);

		if (itr != enemySpawnMap.end())
		{
			return itr->second;
		}
		else
		{
			Debug::LogError("Wrong tunnel number", typeid(TunnelCollidersData).name());
		}
	}

private:
	void GenerateData()
	{
		///--------- 1 туннель ---------
		{
			CollidersDataVector colliders;

			ColliderData data1;
			data1.centerPosition = { 0.f, 170.f };
			data1.shape.SetAsBox(1920.f / 2, 10.f, data1.centerPosition, 0);

			colliders.push_back(data1);

			ColliderData data2;
			data2.centerPosition = { 0.f, -170.f };
			data2.shape.SetAsBox(1920.f / 2, 10.f, data2.centerPosition, 0);

			colliders.push_back(data2);

			collidersMap.emplace(std::make_pair(1, colliders));

			{
				EnemySpawnPositions enemySpawns;

				{
					sf::Vector2f position(-760.f, 0.f);
					enemySpawns.push_back(position);
				}
				{
					sf::Vector2f position(760.f, 0.f);
					enemySpawns.push_back(position);
				}
				enemySpawnMap.emplace(std::make_pair(1, enemySpawns));
			}

		}
		///--------- 1 туннель ---------

		///--------- 2 туннель ---------
		{
			CollidersDataVector colliders;

			{
				ColliderData data;
				const short SIZE = 3;
				b2Vec2 vertices[SIZE];

				vertices[0].Set(WIDTH_CENTER + 738.f, HEIGHT_CENTER + 0.f);
				vertices[1].Set(WIDTH_CENTER + 1276.f, HEIGHT_CENTER + 355.f);
				vertices[2].Set(WIDTH_CENTER + 0.f, HEIGHT_CENTER + 355.f);

				data.shape.Set(vertices, SIZE);

				colliders.push_back(data);
			}

			{
				ColliderData data;
				data.centerPosition = { 0.f, 170.f };
				data.shape.SetAsBox(1920.f / 2, 10.f, data.centerPosition, 0);

				colliders.push_back(data);
			}

			{
				ColliderData data;
				const short SIZE = 4;
				b2Vec2 vertices[SIZE];

				vertices[0].Set(WIDTH_CENTER + 1213.f, HEIGHT_CENTER + 0.f);
				vertices[1].Set(WIDTH_CENTER + 1920.f, HEIGHT_CENTER + 0.f);
				vertices[2].Set(WIDTH_CENTER + 1920.f, HEIGHT_CENTER + 355.f);
				vertices[3].Set(WIDTH_CENTER + 1535.f, HEIGHT_CENTER + 196.f);

				data.shape.Set(vertices, SIZE);

				colliders.push_back(data);

			}
			collidersMap.emplace(std::make_pair(2, colliders));

			{
				EnemySpawnPositions enemySpawns;

				{
					sf::Vector2f position(WIDTH_CENTER + 1747.f, HEIGHT_CENTER + 594.f);
					enemySpawns.push_back(position);
				}
				{
					sf::Vector2f position(WIDTH_CENTER + 123.f, HEIGHT_CENTER + 569.f);
					enemySpawns.push_back(position);
				}
				enemySpawnMap.emplace(std::make_pair(2, enemySpawns));
			}
		}
		///--------- 2 туннель ---------

		///--------- 3 туннель ---------
		{
			CollidersDataVector colliders;

			{
				ColliderData data;
				data.centerPosition = { 0.f, 170.f };
				data.shape.SetAsBox(1920.f / 2, 10.f, data.centerPosition, 0);

				colliders.push_back(data);
			}

			{
				ColliderData data;
				const short SIZE = 4;
				b2Vec2 vertices[SIZE];

				vertices[0].Set(WIDTH_CENTER + 0.f, HEIGHT_CENTER + 355.f);
				vertices[1].Set(WIDTH_CENTER + 0.f, HEIGHT_CENTER + 0.f);
				vertices[2].Set(WIDTH_CENTER + 716.f, HEIGHT_CENTER + 0.f);
				vertices[3].Set(WIDTH_CENTER + 413.f, HEIGHT_CENTER + 189.f);

				data.shape.Set(vertices, SIZE);

				colliders.push_back(data);
			}

			{
				ColliderData data;
				const short SIZE = 3;
				b2Vec2 vertices[SIZE];

				vertices[0].Set(WIDTH_CENTER + 642.f, HEIGHT_CENTER + 355.f);
				vertices[1].Set(WIDTH_CENTER + 1205.f, HEIGHT_CENTER + 0.f);
				vertices[2].Set(WIDTH_CENTER + 1920.f, HEIGHT_CENTER + 355.f);

				data.shape.Set(vertices, SIZE);

				colliders.push_back(data);
			}
			collidersMap.emplace(std::make_pair(3, colliders));
			{
				EnemySpawnPositions enemySpawns;

				{
					sf::Vector2f position(WIDTH_CENTER + 1650.f, HEIGHT_CENTER + 560.f);
					enemySpawns.push_back(position);
				}
				{
					sf::Vector2f position(WIDTH_CENTER + 123.f, HEIGHT_CENTER + 569.f);
					enemySpawns.push_back(position);
				}
				enemySpawnMap.emplace(std::make_pair(3, enemySpawns));
			}
		}
		///--------- 3 туннель ---------

		///--------- 4 туннель ---------
		{
			CollidersDataVector colliders;

			{
				ColliderData data;
				data.centerPosition = { 0.f, -170.f };
				data.shape.SetAsBox(1920.f / 2, 10.f, data.centerPosition, 0);

				colliders.push_back(data);
			}

			{
				ColliderData data;
				const short SIZE = 4;
				b2Vec2 vertices[SIZE];

				vertices[0].Set(WIDTH_CENTER + 0.f, HEIGHT_CENTER + 720.f);
				vertices[1].Set(WIDTH_CENTER + 408.f, HEIGHT_CENTER + 878.f);
				vertices[2].Set(WIDTH_CENTER + 715.f, HEIGHT_CENTER + 1080.f);
				vertices[3].Set(WIDTH_CENTER + 0.f, HEIGHT_CENTER + 1080.f);

				data.shape.Set(vertices, SIZE);

				colliders.push_back(data);
			}

			{
				ColliderData data;
				const short SIZE = 4;
				b2Vec2 vertices[SIZE];

				vertices[0].Set(WIDTH_CENTER + 660.f, HEIGHT_CENTER + 720.f);
				vertices[1].Set(WIDTH_CENTER + 1920.f, HEIGHT_CENTER + 720.f);
				vertices[2].Set(WIDTH_CENTER + 1200.f, HEIGHT_CENTER + 1080.f);
				vertices[3].Set(WIDTH_CENTER + 970.f, HEIGHT_CENTER + 886.f);
				//TODO не совсем правильно отрисовывается из-за того что форма получаается не выпуклой

				data.shape.Set(vertices, SIZE);

				colliders.push_back(data);
			}
			collidersMap.emplace(std::make_pair(4, colliders));
			{
				EnemySpawnPositions enemySpawns;

				{
					sf::Vector2f position(WIDTH_CENTER + 853.f, HEIGHT_CENTER + 546.f);
					enemySpawns.push_back(position);
				}
				{
					sf::Vector2f position(WIDTH_CENTER + 1720.f, HEIGHT_CENTER + 545.f);
					enemySpawns.push_back(position);
				}
				enemySpawnMap.emplace(std::make_pair(4, enemySpawns));
			}
		}
		///--------- 4 туннель ---------

		///--------- 5 туннель ---------
		{
			CollidersDataVector colliders;

			{
				ColliderData data;
				data.centerPosition = { 0.f, -170.f };
				data.shape.SetAsBox(1920.f / 2, 10.f, data.centerPosition, 0);

				colliders.push_back(data);
			}

			{
				ColliderData data;
				const short SIZE = 4;
				b2Vec2 vertices[SIZE];

				vertices[0].Set(WIDTH_CENTER + 0.f, HEIGHT_CENTER + 720.f);
				vertices[1].Set(WIDTH_CENTER + 1183.f, HEIGHT_CENTER + 722.f);
				vertices[2].Set(WIDTH_CENTER + 723.f, HEIGHT_CENTER + 1080.f);
				vertices[3].Set(WIDTH_CENTER + 0.f, HEIGHT_CENTER + 1080.f);

				data.shape.Set(vertices, SIZE);

				colliders.push_back(data);
			}

			{
				ColliderData data;
				const short SIZE = 4;
				b2Vec2 vertices[SIZE];

				vertices[0].Set(WIDTH_CENTER + 1920.f, HEIGHT_CENTER + 720.f);
				vertices[1].Set(WIDTH_CENTER + 1500.f, HEIGHT_CENTER + 855.f);
				vertices[2].Set(WIDTH_CENTER + 1205.f, HEIGHT_CENTER + 1080.f);
				vertices[3].Set(WIDTH_CENTER + 1920.f, HEIGHT_CENTER + 1080.f);

				data.shape.Set(vertices, SIZE);

				colliders.push_back(data);
			}

			collidersMap.emplace(std::make_pair(5, colliders));
			{
				EnemySpawnPositions enemySpawns;

				{
					sf::Vector2f position(WIDTH_CENTER + 1085.f, HEIGHT_CENTER + 522.f);
					enemySpawns.push_back(position);
				}
				{
					sf::Vector2f position(WIDTH_CENTER + 231.f, HEIGHT_CENTER + 545.f);
					enemySpawns.push_back(position);
				}
				enemySpawnMap.emplace(std::make_pair(5, enemySpawns));
			}
		}
		///--------- 5 туннель ---------

		///--------- 6 туннель ---------
		{
			CollidersDataVector colliders;

			{
				ColliderData data;
				const short SIZE = 4;
				b2Vec2 vertices[SIZE];

				vertices[0].Set(WIDTH_CENTER + 1920 - 0.f, HEIGHT_CENTER + 357.f);
				vertices[1].Set(WIDTH_CENTER + 1920 - 433.f, HEIGHT_CENTER + 211.f);
				vertices[2].Set(WIDTH_CENTER + 1920 - 433.f, HEIGHT_CENTER + 180.f);
				vertices[3].Set(WIDTH_CENTER + 1920 - 0.f, HEIGHT_CENTER + 330.f);

				data.shape.Set(vertices, SIZE);

				colliders.push_back(data);
			}

			{
				ColliderData data;
				const short SIZE = 4;
				b2Vec2 vertices[SIZE];

				vertices[0].Set(WIDTH_CENTER + 1920 - 433.f, HEIGHT_CENTER + 211.f);
				vertices[1].Set(WIDTH_CENTER + 1920 - 715.f, HEIGHT_CENTER + 0.f);
				vertices[2].Set(WIDTH_CENTER + 1920 - 695.f, HEIGHT_CENTER + 0.f);
				vertices[3].Set(WIDTH_CENTER + 1920 - 433.f, HEIGHT_CENTER + 190.f);

				data.shape.Set(vertices, SIZE);

				colliders.push_back(data);
			}

			{
				ColliderData data;
				const short SIZE = 4;
				b2Vec2 vertices[SIZE];

				vertices[0].Set(WIDTH_CENTER + 1920 - 0.f, HEIGHT_CENTER + 723.f);
				vertices[1].Set(WIDTH_CENTER + 1920 - 717.f, HEIGHT_CENTER + 397.f);
				vertices[2].Set(WIDTH_CENTER + 1920 - 717.f, HEIGHT_CENTER + 415.f);
				vertices[3].Set(WIDTH_CENTER + 1920 - 0.f, HEIGHT_CENTER + 745.f);

				data.shape.Set(vertices, SIZE);

				colliders.push_back(data);
			}

			{
				ColliderData data;
				const short SIZE = 4;
				b2Vec2 vertices[SIZE];

				vertices[0].Set(WIDTH_CENTER + 1920 - 717.f, HEIGHT_CENTER + 397.f);
				vertices[1].Set(WIDTH_CENTER + 1920 - 1190.f, HEIGHT_CENTER + 0.f);
				vertices[2].Set(WIDTH_CENTER + 1920 - 1210.f, HEIGHT_CENTER + 0.f);
				vertices[3].Set(WIDTH_CENTER + 1920 - 717.f, HEIGHT_CENTER + 420.f);

				data.shape.Set(vertices, SIZE);

				colliders.push_back(data);
			}

			collidersMap.emplace(std::make_pair(6, colliders));
			{
				EnemySpawnPositions enemySpawns;

				{
					sf::Vector2f position(WIDTH_CENTER + 1234.f, HEIGHT_CENTER + 253.f);
					enemySpawns.push_back(position);
				}
				enemySpawnMap.emplace(std::make_pair(6, enemySpawns));
			}
		}
		///--------- 6 туннель ---------

		///--------- 7 туннель ---------
		{
			CollidersDataVector colliders;

			{
				ColliderData data;
				const short SIZE = 4;
				b2Vec2 vertices[SIZE];

				vertices[0].Set(WIDTH_CENTER + 0.f, HEIGHT_CENTER + 357.f);
				vertices[1].Set(WIDTH_CENTER + 433.f, HEIGHT_CENTER + 211.f);
				vertices[2].Set(WIDTH_CENTER + 433.f, HEIGHT_CENTER + 180.f);
				vertices[3].Set(WIDTH_CENTER + 0.f, HEIGHT_CENTER + 330.f);

				data.shape.Set(vertices, SIZE);

				colliders.push_back(data);
			}

			{
				ColliderData data;
				const short SIZE = 4;
				b2Vec2 vertices[SIZE];

				vertices[0].Set(WIDTH_CENTER + 433.f, HEIGHT_CENTER + 211.f);
				vertices[1].Set(WIDTH_CENTER + 715.f, HEIGHT_CENTER + 0.f);
				vertices[2].Set(WIDTH_CENTER + 695.f, HEIGHT_CENTER + 0.f);
				vertices[3].Set(WIDTH_CENTER + 433.f, HEIGHT_CENTER + 190.f);

				data.shape.Set(vertices, SIZE);

				colliders.push_back(data);
			}

			{
				ColliderData data;
				const short SIZE = 4;
				b2Vec2 vertices[SIZE];

				vertices[0].Set(WIDTH_CENTER + 0.f, HEIGHT_CENTER + 723.f);
				vertices[1].Set(WIDTH_CENTER + 717.f, HEIGHT_CENTER + 397.f);
				vertices[2].Set(WIDTH_CENTER + 717.f, HEIGHT_CENTER + 415.f);
				vertices[3].Set(WIDTH_CENTER + 0.f, HEIGHT_CENTER + 745.f);

				data.shape.Set(vertices, SIZE);

				colliders.push_back(data);
			}

			{
				ColliderData data;
				const short SIZE = 4;
				b2Vec2 vertices[SIZE];

				vertices[0].Set(WIDTH_CENTER + 717.f, HEIGHT_CENTER + 397.f);
				vertices[1].Set(WIDTH_CENTER + 1190.f, HEIGHT_CENTER + 0.f);
				vertices[2].Set(WIDTH_CENTER + 1210.f, HEIGHT_CENTER + 0.f);
				vertices[3].Set(WIDTH_CENTER + 717.f, HEIGHT_CENTER + 420.f);

				data.shape.Set(vertices, SIZE);

				colliders.push_back(data);
			}

			collidersMap.emplace(std::make_pair(7, colliders));
			{
				EnemySpawnPositions enemySpawns;

				{
					sf::Vector2f position(WIDTH_CENTER + 610.f, HEIGHT_CENTER + 315.f);
					enemySpawns.push_back(position);
				}
				enemySpawnMap.emplace(std::make_pair(7, enemySpawns));
			}
		}
		///--------- 7 туннель ---------

		///--------- 8 туннель ---------
		{
			CollidersDataVector colliders;

			{
				ColliderData data;
				const short SIZE = 4;
				b2Vec2 vertices[SIZE];

				vertices[0].Set(WIDTH_CENTER + 0.f, HEIGHT_CENTER + 1080 - 357.f);
				vertices[1].Set(WIDTH_CENTER + 433.f, HEIGHT_CENTER + 1080 - 211.f);
				vertices[2].Set(WIDTH_CENTER + 433.f, HEIGHT_CENTER + 1080 - 180.f);
				vertices[3].Set(WIDTH_CENTER + 0.f, HEIGHT_CENTER + 1080 - 330.f);

				data.shape.Set(vertices, SIZE);

				colliders.push_back(data);
			}

			{
				ColliderData data;
				const short SIZE = 4;
				b2Vec2 vertices[SIZE];

				vertices[0].Set(WIDTH_CENTER + 433.f, HEIGHT_CENTER + 1080 - 211.f);
				vertices[1].Set(WIDTH_CENTER + 715.f, HEIGHT_CENTER + 1080 - 0.f);
				vertices[2].Set(WIDTH_CENTER + 695.f, HEIGHT_CENTER + 1080 - 0.f);
				vertices[3].Set(WIDTH_CENTER + 433.f, HEIGHT_CENTER + 1080 - 190.f);

				data.shape.Set(vertices, SIZE);

				colliders.push_back(data);
			}

			{
				ColliderData data;
				const short SIZE = 4;
				b2Vec2 vertices[SIZE];

				vertices[0].Set(WIDTH_CENTER + 0.f, HEIGHT_CENTER + 1080 - 723.f);
				vertices[1].Set(WIDTH_CENTER + 717.f, HEIGHT_CENTER + 1080 - 397.f);
				vertices[2].Set(WIDTH_CENTER + 717.f, HEIGHT_CENTER + 1080 - 415.f);
				vertices[3].Set(WIDTH_CENTER + 0.f, HEIGHT_CENTER + 1080 - 745.f);

				data.shape.Set(vertices, SIZE);

				colliders.push_back(data);
			}

			{
				ColliderData data;
				const short SIZE = 4;
				b2Vec2 vertices[SIZE];

				vertices[0].Set(WIDTH_CENTER + 717.f, HEIGHT_CENTER + 1080 - 397.f);
				vertices[1].Set(WIDTH_CENTER + 1190.f, HEIGHT_CENTER + 1080 - 0.f);
				vertices[2].Set(WIDTH_CENTER + 1210.f, HEIGHT_CENTER + 1080 - 0.f);
				vertices[3].Set(WIDTH_CENTER + 717.f, HEIGHT_CENTER + 1080 - 420.f);

				data.shape.Set(vertices, SIZE);

				colliders.push_back(data);
			}

			collidersMap.emplace(std::make_pair(8, colliders));
			{
				EnemySpawnPositions enemySpawns;

				{
					sf::Vector2f position(WIDTH_CENTER + 610.f, HEIGHT_CENTER + 815.f);
					enemySpawns.push_back(position);
				}
				enemySpawnMap.emplace(std::make_pair(8, enemySpawns));
			}
		}
		///--------- 8 туннель ---------

		///--------- 9 туннель ---------
		{
			CollidersDataVector colliders;

			{
				ColliderData data;
				const short SIZE = 4;
				b2Vec2 vertices[SIZE];

				vertices[0].Set(WIDTH_CENTER + 1920 - 0.f, HEIGHT_CENTER + 1080 - 357.f);
				vertices[1].Set(WIDTH_CENTER + 1920 - 433.f, HEIGHT_CENTER + 1080 - 211.f);
				vertices[2].Set(WIDTH_CENTER + 1920 - 433.f, HEIGHT_CENTER + 1080 - 180.f);
				vertices[3].Set(WIDTH_CENTER + 1920 - 0.f, HEIGHT_CENTER + 1080 - 330.f);

				data.shape.Set(vertices, SIZE);

				colliders.push_back(data);
			}

			{
				ColliderData data;
				const short SIZE = 4;
				b2Vec2 vertices[SIZE];

				vertices[0].Set(WIDTH_CENTER + 1920 - 433.f, HEIGHT_CENTER + 1080 - 211.f);
				vertices[1].Set(WIDTH_CENTER + 1920 - 315.f, HEIGHT_CENTER + 1080 - 0.f);
				vertices[2].Set(WIDTH_CENTER + 1920 - 695.f, HEIGHT_CENTER + 1080 - 0.f);
				vertices[3].Set(WIDTH_CENTER + 1920 - 433.f, HEIGHT_CENTER + 1080 - 190.f);

				data.shape.Set(vertices, SIZE);

				colliders.push_back(data);
			}

			{
				ColliderData data;
				const short SIZE = 4;
				b2Vec2 vertices[SIZE];

				vertices[0].Set(WIDTH_CENTER + 1920 - 0.f, HEIGHT_CENTER + 1080 - 723.f);
				vertices[1].Set(WIDTH_CENTER + 1920 - 717.f, HEIGHT_CENTER + 1080 - 397.f);
				vertices[2].Set(WIDTH_CENTER + 1920 - 717.f, HEIGHT_CENTER + 1080 - 415.f);
				vertices[3].Set(WIDTH_CENTER + 1920 - 0.f, HEIGHT_CENTER + 1080 - 745.f);

				data.shape.Set(vertices, SIZE);

				colliders.push_back(data);
			}

			{
				ColliderData data;
				const short SIZE = 4;
				b2Vec2 vertices[SIZE];

				vertices[0].Set(WIDTH_CENTER + 1920 - 717.f, HEIGHT_CENTER + 1080 - 397.f);
				vertices[1].Set(WIDTH_CENTER + 1920 - 1190.f, HEIGHT_CENTER + 1080 - 0.f);
				vertices[2].Set(WIDTH_CENTER + 1920 - 1210.f, HEIGHT_CENTER + 1080 - 0.f);
				vertices[3].Set(WIDTH_CENTER + 1920 - 717.f, HEIGHT_CENTER + 1080 - 420.f);

				data.shape.Set(vertices, SIZE);

				colliders.push_back(data);
			}

			collidersMap.emplace(std::make_pair(9, colliders));
			{
				EnemySpawnPositions enemySpawns;

				{
					sf::Vector2f position(WIDTH_CENTER + 1493.f, HEIGHT_CENTER + 738.f);
					enemySpawns.push_back(position);
				}
				enemySpawnMap.emplace(std::make_pair(9, enemySpawns));
			}
		}
		///--------- 9 туннель ---------

		///--------- 10 туннель ---------
		{

			CollidersDataVector colliders;

			{
				ColliderData data;
				const short SIZE = 4;
				b2Vec2 vertices[SIZE];

				vertices[0].Set(WIDTH_CENTER + 0.f, HEIGHT_CENTER + 180.f);
				vertices[1].Set(WIDTH_CENTER + 1268.f, HEIGHT_CENTER + 83.f);
				vertices[2].Set(WIDTH_CENTER + 1268.f, HEIGHT_CENTER + 60.f);
				vertices[3].Set(WIDTH_CENTER + 0.f, HEIGHT_CENTER + 200.f);

				data.shape.Set(vertices, SIZE);

				colliders.push_back(data);
			}

			{
				ColliderData data;
				const short SIZE = 4;
				b2Vec2 vertices[SIZE];

				vertices[0].Set(WIDTH_CENTER + 0.f, HEIGHT_CENTER + 456.f);
				vertices[1].Set(WIDTH_CENTER + 1096.f, HEIGHT_CENTER + 412.f);
				vertices[2].Set(WIDTH_CENTER + 1096.f, HEIGHT_CENTER + 440.f);
				vertices[3].Set(WIDTH_CENTER + 0.f, HEIGHT_CENTER + 480.f);

				data.shape.Set(vertices, SIZE);

				colliders.push_back(data);
			}

			///------- полукруг --------

			{
				ColliderData data;
				const short SIZE = 4;
				b2Vec2 vertices[SIZE];

				vertices[0].Set(WIDTH_CENTER + 1269.f, HEIGHT_CENTER + 83.f);
				vertices[1].Set(WIDTH_CENTER + 1393.f, HEIGHT_CENTER + 122.f);
				vertices[2].Set(WIDTH_CENTER + 1420.f, HEIGHT_CENTER + 122.f);
				vertices[3].Set(WIDTH_CENTER + 1269.f, HEIGHT_CENTER + 55.f);

				data.shape.Set(vertices, SIZE);

				colliders.push_back(data);
			}

			{
				ColliderData data;
				const short SIZE = 4;
				b2Vec2 vertices[SIZE];

				vertices[0].Set(WIDTH_CENTER + 1394.f, HEIGHT_CENTER + 83.f);
				vertices[1].Set(WIDTH_CENTER + 1370.f, HEIGHT_CENTER + 309.f);
				vertices[2].Set(WIDTH_CENTER + 1400.f, HEIGHT_CENTER + 309.f);
				vertices[3].Set(WIDTH_CENTER + 1420.f, HEIGHT_CENTER + 83.f);

				data.shape.Set(vertices, SIZE);

				colliders.push_back(data);
			}

			{
				ColliderData data;
				const short SIZE = 4;
				b2Vec2 vertices[SIZE];

				vertices[0].Set(WIDTH_CENTER + 1097.f, HEIGHT_CENTER + 412.f);
				vertices[1].Set(WIDTH_CENTER + 1370.f, HEIGHT_CENTER + 310.f);
				vertices[2].Set(WIDTH_CENTER + 1370.f, HEIGHT_CENTER + 330.f);
				vertices[3].Set(WIDTH_CENTER + 1097.f, HEIGHT_CENTER + 430.f);

				data.shape.Set(vertices, SIZE);

				colliders.push_back(data);
			}

			///------- полукруг --------

			{
				ColliderData data;
				const short SIZE = 4;
				b2Vec2 vertices[SIZE];

				vertices[0].Set(WIDTH_CENTER + 0.f, HEIGHT_CENTER + 643.f);
				vertices[1].Set(WIDTH_CENTER + 604.f, HEIGHT_CENTER + 797.f);
				vertices[2].Set(WIDTH_CENTER + 604.f, HEIGHT_CENTER + 770.f);
				vertices[3].Set(WIDTH_CENTER + 0.f, HEIGHT_CENTER + 620.f);

				data.shape.Set(vertices, SIZE);

				colliders.push_back(data);
			}

			{
				ColliderData data;
				const short SIZE = 4;
				b2Vec2 vertices[SIZE];

				vertices[0].Set(WIDTH_CENTER + 605.f, HEIGHT_CENTER + 797.f);
				vertices[1].Set(WIDTH_CENTER + 1148.f, HEIGHT_CENTER + 1080.f);
				vertices[2].Set(WIDTH_CENTER + 1180.f, HEIGHT_CENTER + 1080.f);
				vertices[3].Set(WIDTH_CENTER + 605.f, HEIGHT_CENTER + 770.f);

				data.shape.Set(vertices, SIZE);

				colliders.push_back(data);
			}

			{
				ColliderData data;
				const short SIZE = 4;
				b2Vec2 vertices[SIZE];

				vertices[0].Set(WIDTH_CENTER + 0.f, HEIGHT_CENTER + 890.f);
				vertices[1].Set(WIDTH_CENTER + 389.f, HEIGHT_CENTER + 975.f);
				vertices[2].Set(WIDTH_CENTER + 389.f, HEIGHT_CENTER + 1000.f);
				vertices[3].Set(WIDTH_CENTER + 0.f, HEIGHT_CENTER + 925.f);

				data.shape.Set(vertices, SIZE);

				colliders.push_back(data);
			}

			{
				ColliderData data;
				const short SIZE = 4;
				b2Vec2 vertices[SIZE];

				vertices[0].Set(WIDTH_CENTER + 390.f, HEIGHT_CENTER + 975.f);
				vertices[1].Set(WIDTH_CENTER + 658.f, HEIGHT_CENTER + 1080.f);
				vertices[2].Set(WIDTH_CENTER + 630.f, HEIGHT_CENTER + 1080.f);
				vertices[3].Set(WIDTH_CENTER + 390.f, HEIGHT_CENTER + 1000.f);

				data.shape.Set(vertices, SIZE);

				colliders.push_back(data);
			}

			collidersMap.emplace(std::make_pair(10, colliders));
			{
				EnemySpawnPositions enemySpawns;

				{
					sf::Vector2f position(WIDTH_CENTER + 782.f, HEIGHT_CENTER + 325.f);
					enemySpawns.push_back(position);
				}
				{
					sf::Vector2f position(WIDTH_CENTER + 114.f, HEIGHT_CENTER + 826.f);
					enemySpawns.push_back(position);
				}
				enemySpawnMap.emplace(std::make_pair(10, enemySpawns));
			}

		}
		///--------- 10 туннель ---------

		///--------- 11 туннель ---------
		{

			CollidersDataVector colliders;

			{
				ColliderData data;
				const short SIZE = 4;
				b2Vec2 vertices[SIZE];

				vertices[0].Set(WIDTH_CENTER + 1920.f, HEIGHT_CENTER + 180.f);
				vertices[1].Set(WIDTH_CENTER + 652.f, HEIGHT_CENTER + 83.f);
				vertices[2].Set(WIDTH_CENTER + 652.f, HEIGHT_CENTER + 60.f);
				vertices[3].Set(WIDTH_CENTER + 1920.f, HEIGHT_CENTER + 200.f);

				data.shape.Set(vertices, SIZE);

				colliders.push_back(data);
			}

			{
				ColliderData data;
				const short SIZE = 4;
				b2Vec2 vertices[SIZE];

				vertices[0].Set(WIDTH_CENTER + 1920 - 0.f, HEIGHT_CENTER + 456.f);
				vertices[1].Set(WIDTH_CENTER + 1920 - 1096.f, HEIGHT_CENTER + 412.f);
				vertices[2].Set(WIDTH_CENTER + 1920 - 1096.f, HEIGHT_CENTER + 440.f);
				vertices[3].Set(WIDTH_CENTER + 1920 - 0.f, HEIGHT_CENTER + 480.f);

				data.shape.Set(vertices, SIZE);

				colliders.push_back(data);
			}

			///------- полукруг --------

			{
				ColliderData data;
				const short SIZE = 4;
				b2Vec2 vertices[SIZE];

				vertices[0].Set(WIDTH_CENTER + 1920 - 1269.f, HEIGHT_CENTER + 83.f);
				vertices[1].Set(WIDTH_CENTER + 1920 - 1393.f, HEIGHT_CENTER + 122.f);
				vertices[2].Set(WIDTH_CENTER + 1920 - 1420.f, HEIGHT_CENTER + 122.f);
				vertices[3].Set(WIDTH_CENTER + 1920 - 1269.f, HEIGHT_CENTER + 55.f);

				data.shape.Set(vertices, SIZE);

				colliders.push_back(data);
			}

			{
				ColliderData data;
				const short SIZE = 4;
				b2Vec2 vertices[SIZE];

				vertices[0].Set(WIDTH_CENTER + 1920 - 1394.f, HEIGHT_CENTER + 83.f);
				vertices[1].Set(WIDTH_CENTER + 1920 - 1370.f, HEIGHT_CENTER + 309.f);
				vertices[2].Set(WIDTH_CENTER + 1920 - 1400.f, HEIGHT_CENTER + 309.f);
				vertices[3].Set(WIDTH_CENTER + 1920 - 1420.f, HEIGHT_CENTER + 83.f);

				data.shape.Set(vertices, SIZE);

				colliders.push_back(data);
			}

			{
				ColliderData data;
				const short SIZE = 4;
				b2Vec2 vertices[SIZE];

				vertices[0].Set(WIDTH_CENTER + 1920 - 1097.f, HEIGHT_CENTER + 412.f);
				vertices[1].Set(WIDTH_CENTER + 1920 - 1370.f, HEIGHT_CENTER + 310.f);
				vertices[2].Set(WIDTH_CENTER + 1920 - 1370.f, HEIGHT_CENTER + 330.f);
				vertices[3].Set(WIDTH_CENTER + 1920 - 1097.f, HEIGHT_CENTER + 430.f);

				data.shape.Set(vertices, SIZE);

				colliders.push_back(data);
			}

			///------- полукруг --------

			{
				ColliderData data;
				const short SIZE = 4;
				b2Vec2 vertices[SIZE];

				vertices[0].Set(WIDTH_CENTER + 1920 - 0.f, HEIGHT_CENTER + 643.f);
				vertices[1].Set(WIDTH_CENTER + 1920 - 604.f, HEIGHT_CENTER + 797.f);
				vertices[2].Set(WIDTH_CENTER + 1920 - 604.f, HEIGHT_CENTER + 770.f);
				vertices[3].Set(WIDTH_CENTER + 1920 - 0.f, HEIGHT_CENTER + 620.f);

				data.shape.Set(vertices, SIZE);

				colliders.push_back(data);
			}

			{
				ColliderData data;
				const short SIZE = 4;
				b2Vec2 vertices[SIZE];

				vertices[0].Set(WIDTH_CENTER + 1920 - 605.f, HEIGHT_CENTER + 797.f);
				vertices[1].Set(WIDTH_CENTER + 1920 - 1148.f, HEIGHT_CENTER + 1080.f);
				vertices[2].Set(WIDTH_CENTER + 1920 - 1180.f, HEIGHT_CENTER + 1080.f);
				vertices[3].Set(WIDTH_CENTER + 1920 - 605.f, HEIGHT_CENTER + 770.f);

				data.shape.Set(vertices, SIZE);

				colliders.push_back(data);
			}

			{
				ColliderData data;
				const short SIZE = 4;
				b2Vec2 vertices[SIZE];

				vertices[0].Set(WIDTH_CENTER + 1920 - 0.f, HEIGHT_CENTER + 890.f);
				vertices[1].Set(WIDTH_CENTER + 1920 - 389.f, HEIGHT_CENTER + 975.f);
				vertices[2].Set(WIDTH_CENTER + 1920 - 389.f, HEIGHT_CENTER + 1000.f);
				vertices[3].Set(WIDTH_CENTER + 1920 - 0.f, HEIGHT_CENTER + 925.f);

				data.shape.Set(vertices, SIZE);

				colliders.push_back(data);
			}

			{
				ColliderData data;
				const short SIZE = 4;
				b2Vec2 vertices[SIZE];

				vertices[0].Set(WIDTH_CENTER + 1920 - 390.f, HEIGHT_CENTER + 975.f);
				vertices[1].Set(WIDTH_CENTER + 1920 - 658.f, HEIGHT_CENTER + 1080.f);
				vertices[2].Set(WIDTH_CENTER + 1920 - 630.f, HEIGHT_CENTER + 1080.f);
				vertices[3].Set(WIDTH_CENTER + 1920 - 390.f, HEIGHT_CENTER + 1000.f);

				data.shape.Set(vertices, SIZE);

				colliders.push_back(data);
			}

			collidersMap.emplace(std::make_pair(11, colliders));
			{
				EnemySpawnPositions enemySpawns;

				{
					sf::Vector2f position(WIDTH_CENTER + 1100.f, HEIGHT_CENTER + 321.f);
					enemySpawns.push_back(position);
				}
				{
					sf::Vector2f position(WIDTH_CENTER + 1763.f, HEIGHT_CENTER + 839.f);
					enemySpawns.push_back(position);
				}
				enemySpawnMap.emplace(std::make_pair(11, enemySpawns));
			}

		}
		///--------- 11 туннель ---------

		///--------- 12 туннель ---------
		{

			CollidersDataVector colliders;

			{
				ColliderData data;
				const short SIZE = 4;
				b2Vec2 vertices[SIZE];

				vertices[0].Set(WIDTH_CENTER + 0.f, HEIGHT_CENTER + 1080 - 180.f);
				vertices[1].Set(WIDTH_CENTER + 1268.f, HEIGHT_CENTER + 1080 - 83.f);
				vertices[2].Set(WIDTH_CENTER + 1268.f, HEIGHT_CENTER + 1080 - 60.f);
				vertices[3].Set(WIDTH_CENTER + 0.f, HEIGHT_CENTER + 1080 - 200.f);

				data.shape.Set(vertices, SIZE);

				colliders.push_back(data);
			}

			{
				ColliderData data;
				const short SIZE = 4;
				b2Vec2 vertices[SIZE];

				vertices[0].Set(WIDTH_CENTER + 0.f, HEIGHT_CENTER + 1080 - 456.f);
				vertices[1].Set(WIDTH_CENTER + 1096.f, HEIGHT_CENTER + 1080 - 412.f);
				vertices[2].Set(WIDTH_CENTER + 1096.f, HEIGHT_CENTER + 1080 - 440.f);
				vertices[3].Set(WIDTH_CENTER + 0.f, HEIGHT_CENTER + 1080 - 480.f);

				data.shape.Set(vertices, SIZE);

				colliders.push_back(data);
			}

			///------- полукруг --------

			{
				ColliderData data;
				const short SIZE = 4;
				b2Vec2 vertices[SIZE];

				vertices[0].Set(WIDTH_CENTER + 1269.f, HEIGHT_CENTER + 1080 - 83.f);
				vertices[1].Set(WIDTH_CENTER + 1393.f, HEIGHT_CENTER + 1080 - 122.f);
				vertices[2].Set(WIDTH_CENTER + 1420.f, HEIGHT_CENTER + 1080 - 122.f);
				vertices[3].Set(WIDTH_CENTER + 1269.f, HEIGHT_CENTER + 1080 - 55.f);

				data.shape.Set(vertices, SIZE);

				colliders.push_back(data);
			}

			{
				ColliderData data;
				const short SIZE = 4;
				b2Vec2 vertices[SIZE];

				vertices[0].Set(WIDTH_CENTER + 1394.f, HEIGHT_CENTER + 1080 - 83.f);
				vertices[1].Set(WIDTH_CENTER + 1370.f, HEIGHT_CENTER + 1080 - 309.f);
				vertices[2].Set(WIDTH_CENTER + 1400.f, HEIGHT_CENTER + 1080 - 309.f);
				vertices[3].Set(WIDTH_CENTER + 1420.f, HEIGHT_CENTER + 1080 - 83.f);

				data.shape.Set(vertices, SIZE);

				colliders.push_back(data);
			}

			{
				ColliderData data;
				const short SIZE = 4;
				b2Vec2 vertices[SIZE];

				vertices[0].Set(WIDTH_CENTER + 1097.f, HEIGHT_CENTER + 1080 - 412.f);
				vertices[1].Set(WIDTH_CENTER + 1370.f, HEIGHT_CENTER + 1080 - 310.f);
				vertices[2].Set(WIDTH_CENTER + 1370.f, HEIGHT_CENTER + 1080 - 330.f);
				vertices[3].Set(WIDTH_CENTER + 1097.f, HEIGHT_CENTER + 1080 - 430.f);

				data.shape.Set(vertices, SIZE);

				colliders.push_back(data);
			}

			///------- полукруг --------

			{
				ColliderData data;
				const short SIZE = 4;
				b2Vec2 vertices[SIZE];

				vertices[0].Set(WIDTH_CENTER + 0.f, HEIGHT_CENTER + 1080 - 643.f);
				vertices[1].Set(WIDTH_CENTER + 604.f, HEIGHT_CENTER + 1080 - 797.f);
				vertices[2].Set(WIDTH_CENTER + 604.f, HEIGHT_CENTER + 1080 - 770.f);
				vertices[3].Set(WIDTH_CENTER + 0.f, HEIGHT_CENTER + 1080 - 620.f);

				data.shape.Set(vertices, SIZE);

				colliders.push_back(data);
			}

			{
				ColliderData data;
				const short SIZE = 4;
				b2Vec2 vertices[SIZE];

				vertices[0].Set(WIDTH_CENTER + 605.f, HEIGHT_CENTER + 1080 - 797.f);
				vertices[1].Set(WIDTH_CENTER + 1148.f, HEIGHT_CENTER + 1080 - 1080.f);
				vertices[2].Set(WIDTH_CENTER + 1180.f, HEIGHT_CENTER + 1080 - 1080.f);
				vertices[3].Set(WIDTH_CENTER + 605.f, HEIGHT_CENTER + 1080 - 770.f);

				data.shape.Set(vertices, SIZE);

				colliders.push_back(data);
			}

			{
				ColliderData data;
				const short SIZE = 4;
				b2Vec2 vertices[SIZE];

				vertices[0].Set(WIDTH_CENTER + 0.f, HEIGHT_CENTER + 1080 - 890.f);
				vertices[1].Set(WIDTH_CENTER + 389.f, HEIGHT_CENTER + 1080 - 975.f);
				vertices[2].Set(WIDTH_CENTER + 389.f, HEIGHT_CENTER + 1080 - 1000.f);
				vertices[3].Set(WIDTH_CENTER + 0.f, HEIGHT_CENTER + 1080 - 925.f);

				data.shape.Set(vertices, SIZE);

				colliders.push_back(data);
			}

			{
				ColliderData data;
				const short SIZE = 4;
				b2Vec2 vertices[SIZE];

				vertices[0].Set(WIDTH_CENTER + 390.f, HEIGHT_CENTER + 1080 - 975.f);
				vertices[1].Set(WIDTH_CENTER + 658.f, HEIGHT_CENTER + 1080 - 1080.f);
				vertices[2].Set(WIDTH_CENTER + 630.f, HEIGHT_CENTER + 1080 - 1080.f);
				vertices[3].Set(WIDTH_CENTER + 390.f, HEIGHT_CENTER + 1080 - 1000.f);

				data.shape.Set(vertices, SIZE);

				colliders.push_back(data);
			}

			collidersMap.emplace(std::make_pair(12, colliders));
			{
				EnemySpawnPositions enemySpawns;

				{
					sf::Vector2f position(WIDTH_CENTER + 695.f, HEIGHT_CENTER + 166.f);
					enemySpawns.push_back(position);
				}
				{
					sf::Vector2f position(WIDTH_CENTER + 711.f, HEIGHT_CENTER + 842.f);
					enemySpawns.push_back(position);
				}
				enemySpawnMap.emplace(std::make_pair(12, enemySpawns));
			}
		}
		///--------- 12 туннель ---------

		///--------- 13 туннель ---------
		{

			CollidersDataVector colliders;

			{
				ColliderData data;
				const short SIZE = 4;
				b2Vec2 vertices[SIZE];

				vertices[0].Set(WIDTH_CENTER + 1920 - 0.f, HEIGHT_CENTER + 1080 - 180.f);
				vertices[1].Set(WIDTH_CENTER + 1920 - 1268.f, HEIGHT_CENTER + 1080 - 83.f);
				vertices[2].Set(WIDTH_CENTER + 1920 - 1268.f, HEIGHT_CENTER + 1080 - 60.f);
				vertices[3].Set(WIDTH_CENTER + 1920 - 0.f, HEIGHT_CENTER + 1080 - 200.f);

				data.shape.Set(vertices, SIZE);

				colliders.push_back(data);
			}

			{
				ColliderData data;
				const short SIZE = 4;
				b2Vec2 vertices[SIZE];

				vertices[0].Set(WIDTH_CENTER + 1920 - 0.f, HEIGHT_CENTER + 1080 - 456.f);
				vertices[1].Set(WIDTH_CENTER + 1920 - 1096.f, HEIGHT_CENTER + 1080 - 412.f);
				vertices[2].Set(WIDTH_CENTER + 1920 - 1096.f, HEIGHT_CENTER + 1080 - 440.f);
				vertices[3].Set(WIDTH_CENTER + 1920 - 0.f, HEIGHT_CENTER + 1080 - 480.f);

				data.shape.Set(vertices, SIZE);

				colliders.push_back(data);
			}

			///------- полукруг --------

			{
				ColliderData data;
				const short SIZE = 4;
				b2Vec2 vertices[SIZE];

				vertices[0].Set(WIDTH_CENTER + 1920 - 1269.f, HEIGHT_CENTER + 1080 - 83.f);
				vertices[1].Set(WIDTH_CENTER + 1920 - 1393.f, HEIGHT_CENTER + 1080 - 122.f);
				vertices[2].Set(WIDTH_CENTER + 1920 - 1420.f, HEIGHT_CENTER + 1080 - 122.f);
				vertices[3].Set(WIDTH_CENTER + 1920 - 1269.f, HEIGHT_CENTER + 1080 - 55.f);

				data.shape.Set(vertices, SIZE);

				colliders.push_back(data);
			}

			{
				ColliderData data;
				const short SIZE = 4;
				b2Vec2 vertices[SIZE];

				vertices[0].Set(WIDTH_CENTER + 1920 - 1394.f, HEIGHT_CENTER + 1080 - 83.f);
				vertices[1].Set(WIDTH_CENTER + 1920 - 1370.f, HEIGHT_CENTER + 1080 - 309.f);
				vertices[2].Set(WIDTH_CENTER + 1920 - 1400.f, HEIGHT_CENTER + 1080 - 309.f);
				vertices[3].Set(WIDTH_CENTER + 1920 - 1420.f, HEIGHT_CENTER + 1080 - 83.f);

				data.shape.Set(vertices, SIZE);

				colliders.push_back(data);
			}

			{
				ColliderData data;
				const short SIZE = 4;
				b2Vec2 vertices[SIZE];

				vertices[0].Set(WIDTH_CENTER + 1920 - 1097.f, HEIGHT_CENTER + 1080 - 412.f);
				vertices[1].Set(WIDTH_CENTER + 1920 - 1370.f, HEIGHT_CENTER + 1080 - 310.f);
				vertices[2].Set(WIDTH_CENTER + 1920 - 1370.f, HEIGHT_CENTER + 1080 - 330.f);
				vertices[3].Set(WIDTH_CENTER + 1920 - 1097.f, HEIGHT_CENTER + 1080 - 430.f);

				data.shape.Set(vertices, SIZE);

				colliders.push_back(data);
			}

			///------- полукруг --------

			{
				ColliderData data;
				const short SIZE = 4;
				b2Vec2 vertices[SIZE];

				vertices[0].Set(WIDTH_CENTER + 1920 - 0.f, HEIGHT_CENTER + 1080 - 643.f);
				vertices[1].Set(WIDTH_CENTER + 1920 - 604.f, HEIGHT_CENTER + 1080 - 797.f);
				vertices[2].Set(WIDTH_CENTER + 1920 - 604.f, HEIGHT_CENTER + 1080 - 770.f);
				vertices[3].Set(WIDTH_CENTER + 1920 - 0.f, HEIGHT_CENTER + 1080 - 620.f);

				data.shape.Set(vertices, SIZE);

				colliders.push_back(data);
			}

			{
				ColliderData data;
				const short SIZE = 4;
				b2Vec2 vertices[SIZE];

				vertices[0].Set(WIDTH_CENTER + 1920 - 605.f, HEIGHT_CENTER + 1080 - 797.f);
				vertices[1].Set(WIDTH_CENTER + 1920 - 1148.f, HEIGHT_CENTER + 1080 - 1080.f);
				vertices[2].Set(WIDTH_CENTER + 1920 - 1180.f, HEIGHT_CENTER + 1080 - 1080.f);
				vertices[3].Set(WIDTH_CENTER + 1920 - 605.f, HEIGHT_CENTER + 1080 - 770.f);

				data.shape.Set(vertices, SIZE);

				colliders.push_back(data);
			}

			{
				ColliderData data;
				const short SIZE = 4;
				b2Vec2 vertices[SIZE];

				vertices[0].Set(WIDTH_CENTER + 1920 - 0.f, HEIGHT_CENTER + 1080 - 890.f);
				vertices[1].Set(WIDTH_CENTER + 1920 - 389.f, HEIGHT_CENTER + 1080 - 975.f);
				vertices[2].Set(WIDTH_CENTER + 1920 - 389.f, HEIGHT_CENTER + 1080 - 1000.f);
				vertices[3].Set(WIDTH_CENTER + 1920 - 0.f, HEIGHT_CENTER + 1080 - 925.f);

				data.shape.Set(vertices, SIZE);

				colliders.push_back(data);
			}

			{
				ColliderData data;
				const short SIZE = 4;
				b2Vec2 vertices[SIZE];

				vertices[0].Set(WIDTH_CENTER + 1920 - 390.f, HEIGHT_CENTER + 1080 - 975.f);
				vertices[1].Set(WIDTH_CENTER + 1920 - 658.f, HEIGHT_CENTER + 1080 - 1080.f);
				vertices[2].Set(WIDTH_CENTER + 1920 - 630.f, HEIGHT_CENTER + 1080 - 1080.f);
				vertices[3].Set(WIDTH_CENTER + 1920 - 390.f, HEIGHT_CENTER + 1080 - 1000.f);

				data.shape.Set(vertices, SIZE);

				colliders.push_back(data);
			}

			collidersMap.emplace(std::make_pair(13, colliders));
			{
				EnemySpawnPositions enemySpawns;

				{
					sf::Vector2f position(WIDTH_CENTER + 1253.f, HEIGHT_CENTER + 191.f);
					enemySpawns.push_back(position);
				}
				{
					sf::Vector2f position(WIDTH_CENTER + 1031.f, HEIGHT_CENTER + 843.f);
					enemySpawns.push_back(position);
				}
				enemySpawnMap.emplace(std::make_pair(13, enemySpawns));
			}
		}
		///--------- 13 туннель ---------

		///--------- 14 туннель ---------
		{
			CollidersDataVector colliders;

			{
				ColliderData data;
				const short SIZE = 4;
				b2Vec2 vertices[SIZE];

				vertices[0].Set(WIDTH_CENTER + 0.f, HEIGHT_CENTER + 367.f);
				vertices[1].Set(WIDTH_CENTER + 1920.f, HEIGHT_CENTER + 186.f);
				vertices[2].Set(WIDTH_CENTER + 1920.f, HEIGHT_CENTER + 150.f);
				vertices[3].Set(WIDTH_CENTER + 0.f, HEIGHT_CENTER + 330.f);

				data.shape.Set(vertices, SIZE);

				colliders.push_back(data);
			}

			{
				ColliderData data;
				const short SIZE = 4;
				b2Vec2 vertices[SIZE];

				vertices[0].Set(WIDTH_CENTER + 0.f, HEIGHT_CENTER + 722.f);
				vertices[1].Set(WIDTH_CENTER + 1920.f, HEIGHT_CENTER + 902.f);
				vertices[2].Set(WIDTH_CENTER + 1920.f, HEIGHT_CENTER + 930.f);
				vertices[3].Set(WIDTH_CENTER + 0.f, HEIGHT_CENTER + 750.f);

				data.shape.Set(vertices, SIZE);

				colliders.push_back(data);
			}

			{
				ColliderData data;
				const short SIZE = 3;
				b2Vec2 vertices[SIZE];

				vertices[0].Set(WIDTH_CENTER + 917.f, HEIGHT_CENTER + 553.f);
				vertices[1].Set(WIDTH_CENTER + 1920.f, HEIGHT_CENTER + 460.f);
				vertices[2].Set(WIDTH_CENTER + 1920.f, HEIGHT_CENTER + 622.f);

				data.shape.Set(vertices, SIZE);

				colliders.push_back(data);
			}

			collidersMap.emplace(std::make_pair(14, colliders));
			{
				EnemySpawnPositions enemySpawns;

				{
					sf::Vector2f position(WIDTH_CENTER + 259.f, HEIGHT_CENTER + 666.f);
					enemySpawns.push_back(position);
				}
				{
					sf::Vector2f position(WIDTH_CENTER + 1663.f, HEIGHT_CENTER + 382.f);
					enemySpawns.push_back(position);
				}
				enemySpawnMap.emplace(std::make_pair(14, enemySpawns));
			}
		}
		///--------- 14 туннель ---------

		///--------- 15 туннель ---------
		{
			CollidersDataVector colliders;

			{
				ColliderData data;
				const short SIZE = 4;
				b2Vec2 vertices[SIZE];

				vertices[0].Set(WIDTH_CENTER + 1920 - 0.f, HEIGHT_CENTER + 367.f);
				vertices[1].Set(WIDTH_CENTER + 1920 - 1920.f, HEIGHT_CENTER + 186.f);
				vertices[2].Set(WIDTH_CENTER + 1920 - 1920.f, HEIGHT_CENTER + 150.f);
				vertices[3].Set(WIDTH_CENTER + 1920 - 0.f, HEIGHT_CENTER + 330.f);

				data.shape.Set(vertices, SIZE);

				colliders.push_back(data);
			}

			{
				ColliderData data;
				const short SIZE = 4;
				b2Vec2 vertices[SIZE];

				vertices[0].Set(WIDTH_CENTER + 1920 - 0.f, HEIGHT_CENTER + 722.f);
				vertices[1].Set(WIDTH_CENTER + 1920 - 1920.f, HEIGHT_CENTER + 902.f);
				vertices[2].Set(WIDTH_CENTER + 1920 - 1920.f, HEIGHT_CENTER + 930.f);
				vertices[3].Set(WIDTH_CENTER + 1920 - 0.f, HEIGHT_CENTER + 750.f);

				data.shape.Set(vertices, SIZE);

				colliders.push_back(data);
			}

			{
				ColliderData data;
				const short SIZE = 3;
				b2Vec2 vertices[SIZE];

				vertices[0].Set(WIDTH_CENTER + 1920 - 917.f, HEIGHT_CENTER + 553.f);
				vertices[1].Set(WIDTH_CENTER + 1920 - 1920.f, HEIGHT_CENTER + 460.f);
				vertices[2].Set(WIDTH_CENTER + 1920 - 1920.f, HEIGHT_CENTER + 622.f);

				data.shape.Set(vertices, SIZE);

				colliders.push_back(data);
			}

			collidersMap.emplace(std::make_pair(15, colliders));
			{
				EnemySpawnPositions enemySpawns;

				{
					sf::Vector2f position(WIDTH_CENTER + 318.f, HEIGHT_CENTER + 386.f);
					enemySpawns.push_back(position);
				}
				{
					sf::Vector2f position(WIDTH_CENTER + 1603.f, HEIGHT_CENTER + 639.f);
					enemySpawns.push_back(position);
				}
				enemySpawnMap.emplace(std::make_pair(15, enemySpawns));
			}
		}
		///--------- 15 туннель ---------

		///--------- 16 туннель ---------
		{
			CollidersDataVector colliders;

			{
				ColliderData data;
				const short SIZE = 4;
				b2Vec2 vertices[SIZE];

				vertices[0].Set(WIDTH_CENTER + 0.f, HEIGHT_CENTER + 187.f);
				vertices[1].Set(WIDTH_CENTER + 1920.f, HEIGHT_CENTER + 187.f);
				vertices[2].Set(WIDTH_CENTER + 1920.f, HEIGHT_CENTER + 150.f);
				vertices[3].Set(WIDTH_CENTER + 0.f, HEIGHT_CENTER + 150.f);

				data.shape.Set(vertices, SIZE);

				colliders.push_back(data);
			}

			{
				ColliderData data;
				const short SIZE = 4;
				b2Vec2 vertices[SIZE];

				vertices[0].Set(WIDTH_CENTER + 0.f, HEIGHT_CENTER + 454.f);
				vertices[1].Set(WIDTH_CENTER + 1920.f, HEIGHT_CENTER + 454.f);
				vertices[2].Set(WIDTH_CENTER + 1920.f, HEIGHT_CENTER + 480.f);
				vertices[3].Set(WIDTH_CENTER + 0.f, HEIGHT_CENTER + 480.f);

				data.shape.Set(vertices, SIZE);

				colliders.push_back(data);
			}

			{
				ColliderData data;
				const short SIZE = 4;
				b2Vec2 vertices[SIZE];

				vertices[0].Set(WIDTH_CENTER + 0.f, HEIGHT_CENTER + 637.f);
				vertices[1].Set(WIDTH_CENTER + 1920.f, HEIGHT_CENTER + 637.f);
				vertices[2].Set(WIDTH_CENTER + 1920.f, HEIGHT_CENTER + 607.f);
				vertices[3].Set(WIDTH_CENTER + 0.f, HEIGHT_CENTER + 607.f);

				data.shape.Set(vertices, SIZE);

				colliders.push_back(data);
			}

			{
				ColliderData data;
				const short SIZE = 4;
				b2Vec2 vertices[SIZE];

				vertices[0].Set(WIDTH_CENTER + 0.f, HEIGHT_CENTER + 907.f);
				vertices[1].Set(WIDTH_CENTER + 1920.f, HEIGHT_CENTER + 907.f);
				vertices[2].Set(WIDTH_CENTER + 1920.f, HEIGHT_CENTER + 937.f);
				vertices[3].Set(WIDTH_CENTER + 0.f, HEIGHT_CENTER + 937.f);

				data.shape.Set(vertices, SIZE);

				colliders.push_back(data);
			}

			collidersMap.emplace(std::make_pair(16, colliders));
			{
				EnemySpawnPositions enemySpawns;

				{
					sf::Vector2f position(WIDTH_CENTER + 264.f, HEIGHT_CENTER + 396.f);
					enemySpawns.push_back(position);
				}
				{
					sf::Vector2f position(WIDTH_CENTER + 1546.f, HEIGHT_CENTER + 746.f);
					enemySpawns.push_back(position);
				}
				enemySpawnMap.emplace(std::make_pair(16, enemySpawns));
			}
		}
		///--------- 16 туннель ---------

		///--------- 17 туннель ---------
		{
			CollidersDataVector colliders;

			{
				ColliderData data;
				const short SIZE = 4;
				b2Vec2 vertices[SIZE];

				vertices[0].Set(WIDTH_CENTER + 0.f, HEIGHT_CENTER + 0.f);
				vertices[1].Set(WIDTH_CENTER + 432.f, HEIGHT_CENTER + 0.f);
				vertices[2].Set(WIDTH_CENTER + 261.f, HEIGHT_CENTER + 218.f);
				vertices[3].Set(WIDTH_CENTER + 0.f, HEIGHT_CENTER + 355.f);

				data.shape.Set(vertices, SIZE);

				colliders.push_back(data);
			}

			{
				ColliderData data;
				const short SIZE = 6;
				b2Vec2 vertices[SIZE];

				vertices[0].Set(WIDTH_CENTER + 1920.f, HEIGHT_CENTER + 0.f);
				vertices[1].Set(WIDTH_CENTER + 885.f, HEIGHT_CENTER + 0.f);
				vertices[2].Set(WIDTH_CENTER + 1063.f, HEIGHT_CENTER + 152.f);
				vertices[3].Set(WIDTH_CENTER + 1340.f, HEIGHT_CENTER + 298.f);
				vertices[4].Set(WIDTH_CENTER + 1700.f, HEIGHT_CENTER + 372.f);
				vertices[5].Set(WIDTH_CENTER + 1920.f, HEIGHT_CENTER + 365.f);

				data.shape.Set(vertices, SIZE);

				colliders.push_back(data);
			}

			{
				ColliderData data;
				const short SIZE = 6;
				b2Vec2 vertices[SIZE];

				vertices[0].Set(WIDTH_CENTER + 0.f, HEIGHT_CENTER + 730.f);
				vertices[1].Set(WIDTH_CENTER + 292.f, HEIGHT_CENTER + 607.f);
				vertices[2].Set(WIDTH_CENTER + 968.f, HEIGHT_CENTER + 650.f);
				vertices[3].Set(WIDTH_CENTER + 1920.f, HEIGHT_CENTER + 724.f);
				vertices[4].Set(WIDTH_CENTER + 1920.f, HEIGHT_CENTER + 1080.f);
				vertices[5].Set(WIDTH_CENTER + 0.f, HEIGHT_CENTER + 1080.f);


				data.shape.Set(vertices, SIZE);

				colliders.push_back(data);
			}

			{
				ColliderData data;
				const short SIZE = 4;
				b2Vec2 vertices[SIZE];

				vertices[0].Set(WIDTH_CENTER + 292.f, HEIGHT_CENTER + 607.f);
				vertices[1].Set(WIDTH_CENTER + 587.f, HEIGHT_CENTER + 300.f);
				vertices[2].Set(WIDTH_CENTER + 587.f, HEIGHT_CENTER + 330.f);
				vertices[3].Set(WIDTH_CENTER + 292.f, HEIGHT_CENTER + 637.f);


				data.shape.Set(vertices, SIZE);

				colliders.push_back(data);
			}

			{
				ColliderData data;
				const short SIZE = 5;
				b2Vec2 vertices[SIZE];

				vertices[0].Set(WIDTH_CENTER + 587.f, HEIGHT_CENTER + 300.f);
				vertices[1].Set(WIDTH_CENTER + 668.f, HEIGHT_CENTER + 277.f);
				vertices[2].Set(WIDTH_CENTER + 748.f, HEIGHT_CENTER + 294.f);
				vertices[3].Set(WIDTH_CENTER + 748.f, HEIGHT_CENTER + 330.f);
				vertices[4].Set(WIDTH_CENTER + 587.f, HEIGHT_CENTER + 330.f);


				data.shape.Set(vertices, SIZE);

				colliders.push_back(data);
			}

			{
				ColliderData data;
				const short SIZE = 5;
				b2Vec2 vertices[SIZE];

				vertices[0].Set(WIDTH_CENTER + 748.f, HEIGHT_CENTER + 294.f);
				vertices[1].Set(WIDTH_CENTER + 871.f, HEIGHT_CENTER + 380.f);
				vertices[2].Set(WIDTH_CENTER + 970.f, HEIGHT_CENTER + 530.f);
				vertices[3].Set(WIDTH_CENTER + 950.f, HEIGHT_CENTER + 530.f);
				vertices[4].Set(WIDTH_CENTER + 748.f, HEIGHT_CENTER + 350.f);


				data.shape.Set(vertices, SIZE);

				colliders.push_back(data);
			}

			{
				ColliderData data;
				const short SIZE = 4;
				b2Vec2 vertices[SIZE];

				vertices[0].Set(WIDTH_CENTER + 970.f, HEIGHT_CENTER + 530.f);
				vertices[1].Set(WIDTH_CENTER + 1259.f, HEIGHT_CENTER + 676.f);
				vertices[2].Set(WIDTH_CENTER + 1259.f, HEIGHT_CENTER + 700.f);
				vertices[3].Set(WIDTH_CENTER + 970.f, HEIGHT_CENTER + 550.f);


				data.shape.Set(vertices, SIZE);

				colliders.push_back(data);
			}


			collidersMap.emplace(std::make_pair(17, colliders));

			{
				EnemySpawnPositions enemySpawns;

				{
					sf::Vector2f position(WIDTH_CENTER + 1400.f, HEIGHT_CENTER + 589.f);
					enemySpawns.push_back(position);
				}

				enemySpawnMap.emplace(std::make_pair(17, enemySpawns));
			}
		}
		///--------- 17 туннель ---------

		///--------- 18 туннель ---------
		{
			CollidersDataVector colliders;

			{
				ColliderData data;
				const short SIZE = 3;
				b2Vec2 vertices[SIZE];

				vertices[0].Set(WIDTH_CENTER + 1920.f, HEIGHT_CENTER + 360.f);
				vertices[1].Set(WIDTH_CENTER + 1066.f, HEIGHT_CENTER + 339.f);
				vertices[2].Set(WIDTH_CENTER + 1066.f, HEIGHT_CENTER + 300.f);

				data.shape.Set(vertices, SIZE);

				colliders.push_back(data);
			}

			{
				ColliderData data;
				const short SIZE = 3;
				b2Vec2 vertices[SIZE];

				vertices[0].Set(WIDTH_CENTER + 1920.f, HEIGHT_CENTER + 722.f);
				vertices[1].Set(WIDTH_CENTER + 1603.f, HEIGHT_CENTER + 765.f);
				vertices[2].Set(WIDTH_CENTER + 1759.f, HEIGHT_CENTER + 776.f);

				data.shape.Set(vertices, SIZE);

				colliders.push_back(data);
			}

			{
				ColliderData data;
				const short SIZE = 3;
				b2Vec2 vertices[SIZE];

				vertices[0].Set(WIDTH_CENTER + 1603.f, HEIGHT_CENTER + 765.f);
				vertices[1].Set(WIDTH_CENTER + 850.f, HEIGHT_CENTER + 923.f);
				vertices[2].Set(WIDTH_CENTER + 1125.f, HEIGHT_CENTER + 960.f);

				data.shape.Set(vertices, SIZE);

				colliders.push_back(data);
			}

			{
				ColliderData data;
				const short SIZE = 3;
				b2Vec2 vertices[SIZE];

				vertices[0].Set(WIDTH_CENTER + 850.f, HEIGHT_CENTER + 923.f);
				vertices[1].Set(WIDTH_CENTER + 498.f, HEIGHT_CENTER + 824.f);
				vertices[2].Set(WIDTH_CENTER + 683.f, HEIGHT_CENTER + 946.f);

				data.shape.Set(vertices, SIZE);

				colliders.push_back(data);
			}

			{
				ColliderData data;
				const short SIZE = 3;
				b2Vec2 vertices[SIZE];

				vertices[0].Set(WIDTH_CENTER + 498.f, HEIGHT_CENTER + 824.f);
				vertices[1].Set(WIDTH_CENTER + 333.f, HEIGHT_CENTER + 487.f);
				vertices[2].Set(WIDTH_CENTER + 373.f, HEIGHT_CENTER + 768.f);

				data.shape.Set(vertices, SIZE);

				colliders.push_back(data);
			}

			{
				ColliderData data;
				const short SIZE = 3;
				b2Vec2 vertices[SIZE];

				vertices[0].Set(WIDTH_CENTER + 333.f, HEIGHT_CENTER + 487.f);
				vertices[1].Set(WIDTH_CENTER + 528.f, HEIGHT_CENTER + 261.f);
				vertices[2].Set(WIDTH_CENTER + 366.f, HEIGHT_CENTER + 328.f);

				data.shape.Set(vertices, SIZE);

				colliders.push_back(data);
			}

			{
				ColliderData data;
				const short SIZE = 3;
				b2Vec2 vertices[SIZE];

				vertices[0].Set(WIDTH_CENTER + 528.f, HEIGHT_CENTER + 261.f);
				vertices[1].Set(WIDTH_CENTER + 789.f, HEIGHT_CENTER + 238.f);
				vertices[2].Set(WIDTH_CENTER + 655.f, HEIGHT_CENTER + 197.f);

				data.shape.Set(vertices, SIZE);

				colliders.push_back(data);
			}

			{
				ColliderData data;
				const short SIZE = 3;
				b2Vec2 vertices[SIZE];

				vertices[0].Set(WIDTH_CENTER + 789.f, HEIGHT_CENTER + 238.f);
				vertices[1].Set(WIDTH_CENTER + 1066.f, HEIGHT_CENTER + 339.f);
				vertices[2].Set(WIDTH_CENTER + 960.f, HEIGHT_CENTER + 275.f);

				data.shape.Set(vertices, SIZE);

				colliders.push_back(data);
			}



			collidersMap.emplace(std::make_pair(18, colliders));
			{
				EnemySpawnPositions enemySpawns;

				{
					sf::Vector2f position(WIDTH_CENTER + 851.f, HEIGHT_CENTER + 739.f);
					enemySpawns.push_back(position);
				}

				enemySpawnMap.emplace(std::make_pair(18, enemySpawns));
			}
		}
		///--------- 18 туннель ---------

		///--------- 19 туннель ---------
		{
			CollidersDataVector colliders;

			{
				ColliderData data;
				const short SIZE = 5;
				b2Vec2 vertices[SIZE];

				vertices[0].Set(WIDTH_CENTER + 0.f, HEIGHT_CENTER + 0.f);
				vertices[1].Set(WIDTH_CENTER + 720.f, HEIGHT_CENTER + 0.f);
				vertices[2].Set(WIDTH_CENTER + 552.f, HEIGHT_CENTER + 179.f);
				vertices[3].Set(WIDTH_CENTER + 350.f, HEIGHT_CENTER + 279.f);
				vertices[4].Set(WIDTH_CENTER + 0.f, HEIGHT_CENTER + 349.f);

				data.shape.Set(vertices, SIZE);

				colliders.push_back(data);
			}

			{
				ColliderData data;
				const short SIZE = 3;
				b2Vec2 vertices[SIZE];

				vertices[0].Set(WIDTH_CENTER + 0.f, HEIGHT_CENTER + 724.f);
				vertices[1].Set(WIDTH_CENTER + 371.f, HEIGHT_CENTER + 692.f);
				vertices[2].Set(WIDTH_CENTER + 168.f, HEIGHT_CENTER + 759.f);

				data.shape.Set(vertices, SIZE);

				colliders.push_back(data);
			}

			{
				ColliderData data;
				const short SIZE = 3;
				b2Vec2 vertices[SIZE];

				vertices[0].Set(WIDTH_CENTER + 371.f, HEIGHT_CENTER + 692.f);
				vertices[1].Set(WIDTH_CENTER + 731.f, HEIGHT_CENTER + 433.f);
				vertices[2].Set(WIDTH_CENTER + 772.f, HEIGHT_CENTER + 563.f);

				data.shape.Set(vertices, SIZE);

				colliders.push_back(data);
			}

			{
				ColliderData data;
				const short SIZE = 3;
				b2Vec2 vertices[SIZE];

				vertices[0].Set(WIDTH_CENTER + 731.f, HEIGHT_CENTER + 433.f);
				vertices[1].Set(WIDTH_CENTER + 855.f, HEIGHT_CENTER + 255.f);
				vertices[2].Set(WIDTH_CENTER + 854.f, HEIGHT_CENTER + 300.f);

				data.shape.Set(vertices, SIZE);

				colliders.push_back(data);
			}

			{
				ColliderData data;
				const short SIZE = 3;
				b2Vec2 vertices[SIZE];

				vertices[0].Set(WIDTH_CENTER + 855.f, HEIGHT_CENTER + 255.f);
				vertices[1].Set(WIDTH_CENTER + 1023.f, HEIGHT_CENTER + 230.f);
				vertices[2].Set(WIDTH_CENTER + 935.f, HEIGHT_CENTER + 222.f);

				data.shape.Set(vertices, SIZE);

				colliders.push_back(data);
			}

			{
				ColliderData data;
				const short SIZE = 3;
				b2Vec2 vertices[SIZE];

				vertices[0].Set(WIDTH_CENTER + 1023.f, HEIGHT_CENTER + 230.f);
				vertices[1].Set(WIDTH_CENTER + 1191.f, HEIGHT_CENTER + 449.f);
				vertices[2].Set(WIDTH_CENTER + 1100.f, HEIGHT_CENTER + 391.f);

				data.shape.Set(vertices, SIZE);

				colliders.push_back(data);
			}

			{
				ColliderData data;
				const short SIZE = 3;
				b2Vec2 vertices[SIZE];

				vertices[0].Set(WIDTH_CENTER + 1191.f, HEIGHT_CENTER + 449.f);
				vertices[1].Set(WIDTH_CENTER + 1920.f, HEIGHT_CENTER + 721.f);
				vertices[2].Set(WIDTH_CENTER + 1500.f, HEIGHT_CENTER + 670.f);

				data.shape.Set(vertices, SIZE);

				colliders.push_back(data);
			}

			{
				ColliderData data;
				const short SIZE = 6;
				b2Vec2 vertices[SIZE];

				vertices[0].Set(WIDTH_CENTER + 1187.f, HEIGHT_CENTER + 0.f);
				vertices[1].Set(WIDTH_CENTER + 1920.f, HEIGHT_CENTER + 0.f);
				vertices[2].Set(WIDTH_CENTER + 1920.f, HEIGHT_CENTER + 358.f);
				vertices[3].Set(WIDTH_CENTER + 1495.f, HEIGHT_CENTER + 312.f);
				vertices[4].Set(WIDTH_CENTER + 1276.f, HEIGHT_CENTER + 192.f);
				vertices[5].Set(WIDTH_CENTER + 1177.f, HEIGHT_CENTER + 54.f);

				data.shape.Set(vertices, SIZE);

				colliders.push_back(data);
			}



			collidersMap.emplace(std::make_pair(19, colliders));
			{
				EnemySpawnPositions enemySpawns;

				{
					sf::Vector2f position(WIDTH_CENTER + 437.f, HEIGHT_CENTER + 529.f);
					enemySpawns.push_back(position);
				}

				enemySpawnMap.emplace(std::make_pair(19, enemySpawns));
			}
		}
		///--------- 19 туннель ---------

		///--------- 20 туннель ---------
		{
			CollidersDataVector colliders;

			{
				ColliderData data;
				const short SIZE = 3;
				b2Vec2 vertices[SIZE];

				vertices[0].Set(WIDTH_CENTER + 1920.f, HEIGHT_CENTER + 189.f);
				vertices[1].Set(WIDTH_CENTER + 820.f, HEIGHT_CENTER + 116.f);
				vertices[2].Set(WIDTH_CENTER + 906.f, HEIGHT_CENTER + 75.f);

				data.shape.Set(vertices, SIZE);

				colliders.push_back(data);
			}

			{
				ColliderData data;
				const short SIZE = 3;
				b2Vec2 vertices[SIZE];

				vertices[0].Set(WIDTH_CENTER + 820.f, HEIGHT_CENTER + 116.f);
				vertices[1].Set(WIDTH_CENTER + 393.f, HEIGHT_CENTER + 290.f);
				vertices[2].Set(WIDTH_CENTER + 452.f, HEIGHT_CENTER + 197.f);

				data.shape.Set(vertices, SIZE);

				colliders.push_back(data);
			}

			{
				ColliderData data;
				const short SIZE = 3;
				b2Vec2 vertices[SIZE];

				vertices[0].Set(WIDTH_CENTER + 393.f, HEIGHT_CENTER + 290.f);
				vertices[1].Set(WIDTH_CENTER + 270.f, HEIGHT_CENTER + 548.f);
				vertices[2].Set(WIDTH_CENTER + 298.f, HEIGHT_CENTER + 368.f);

				data.shape.Set(vertices, SIZE);

				colliders.push_back(data);
			}

			{
				ColliderData data;
				const short SIZE = 3;
				b2Vec2 vertices[SIZE];

				vertices[0].Set(WIDTH_CENTER + 270.f, HEIGHT_CENTER + 548.f);
				vertices[1].Set(WIDTH_CENTER + 344.f, HEIGHT_CENTER + 828.f);
				vertices[2].Set(WIDTH_CENTER + 264.f, HEIGHT_CENTER + 800.f);

				data.shape.Set(vertices, SIZE);

				colliders.push_back(data);
			}

			{
				ColliderData data;
				const short SIZE = 3;
				b2Vec2 vertices[SIZE];

				vertices[0].Set(WIDTH_CENTER + 344.f, HEIGHT_CENTER + 828.f);
				vertices[1].Set(WIDTH_CENTER + 682.f, HEIGHT_CENTER + 952.f);
				vertices[2].Set(WIDTH_CENTER + 500.f, HEIGHT_CENTER + 945.f);

				data.shape.Set(vertices, SIZE);

				colliders.push_back(data);
			}

			{
				ColliderData data;
				const short SIZE = 3;
				b2Vec2 vertices[SIZE];

				vertices[0].Set(WIDTH_CENTER + 682.f, HEIGHT_CENTER + 952.f);
				vertices[1].Set(WIDTH_CENTER + 1100.f, HEIGHT_CENTER + 970.f);
				vertices[2].Set(WIDTH_CENTER + 930.f, HEIGHT_CENTER + 995.f);

				data.shape.Set(vertices, SIZE);

				colliders.push_back(data);
			}

			{
				ColliderData data;
				const short SIZE = 3;
				b2Vec2 vertices[SIZE];

				vertices[0].Set(WIDTH_CENTER + 1100.f, HEIGHT_CENTER + 970.f);
				vertices[1].Set(WIDTH_CENTER + 1920.f, HEIGHT_CENTER + 902.f);
				vertices[2].Set(WIDTH_CENTER + 1660.f, HEIGHT_CENTER + 950.f);

				data.shape.Set(vertices, SIZE);

				colliders.push_back(data);
			}

			{
				ColliderData data;
				const short SIZE = 3;
				b2Vec2 vertices[SIZE];

				vertices[0].Set(WIDTH_CENTER + 1920.f, HEIGHT_CENTER + 457.f);
				vertices[1].Set(WIDTH_CENTER + 846.f, HEIGHT_CENTER + 412.f);
				vertices[2].Set(WIDTH_CENTER + 1130.f, HEIGHT_CENTER + 440.f);

				data.shape.Set(vertices, SIZE);

				colliders.push_back(data);
			}

			{
				ColliderData data;
				const short SIZE = 4;
				b2Vec2 vertices[SIZE];

				vertices[0].Set(WIDTH_CENTER + 846.f, HEIGHT_CENTER + 412.f);
				vertices[1].Set(WIDTH_CENTER + 732.f, HEIGHT_CENTER + 442.f);
				vertices[2].Set(WIDTH_CENTER + 670.f, HEIGHT_CENTER + 496.f);
				vertices[3].Set(WIDTH_CENTER + 684.f, HEIGHT_CENTER + 532.f);

				data.shape.Set(vertices, SIZE);

				colliders.push_back(data);
			}

			{
				ColliderData data;
				const short SIZE = 4;
				b2Vec2 vertices[SIZE];

				vertices[0].Set(WIDTH_CENTER + 670.f, HEIGHT_CENTER + 496.f);
				vertices[1].Set(WIDTH_CENTER + 670.f, HEIGHT_CENTER + 600.f);
				vertices[2].Set(WIDTH_CENTER + 731.f, HEIGHT_CENTER + 682.f);
				vertices[3].Set(WIDTH_CENTER + 725.f, HEIGHT_CENTER + 600.f);

				data.shape.Set(vertices, SIZE);

				colliders.push_back(data);
			}

			{
				ColliderData data;
				const short SIZE = 4;
				b2Vec2 vertices[SIZE];

				vertices[0].Set(WIDTH_CENTER + 731.f, HEIGHT_CENTER + 682.f);
				vertices[1].Set(WIDTH_CENTER + 840.f, HEIGHT_CENTER + 722.f);
				vertices[2].Set(WIDTH_CENTER + 992.f, HEIGHT_CENTER + 725.f);
				vertices[3].Set(WIDTH_CENTER + 850.f, HEIGHT_CENTER + 680.f);

				data.shape.Set(vertices, SIZE);

				colliders.push_back(data);
			}

			{
				ColliderData data;
				const short SIZE = 3;
				b2Vec2 vertices[SIZE];

				vertices[0].Set(WIDTH_CENTER + 992.f, HEIGHT_CENTER + 725.f);
				vertices[1].Set(WIDTH_CENTER + 1920.f, HEIGHT_CENTER + 638.f);
				vertices[2].Set(WIDTH_CENTER + 1516.f, HEIGHT_CENTER + 632.f);

				data.shape.Set(vertices, SIZE);

				colliders.push_back(data);
			}



			collidersMap.emplace(std::make_pair(20, colliders));
			{
				EnemySpawnPositions enemySpawns;

				{
					sf::Vector2f position(WIDTH_CENTER + 1238.f, HEIGHT_CENTER + 357.f);
					enemySpawns.push_back(position);
				}
				{
					sf::Vector2f position(WIDTH_CENTER + 1215.f, HEIGHT_CENTER + 873.f);
					enemySpawns.push_back(position);
				}
				enemySpawnMap.emplace(std::make_pair(20, enemySpawns));
			}
		}
		///--------- 20 туннель ---------



	}

	static std::map<short, CollidersDataVector> collidersMap;
	static std::map<short, EnemySpawnPositions> enemySpawnMap;

	const float WIDTH_CENTER = -1920.f / 2;
	const float HEIGHT_CENTER = -1080.f / 2;
};