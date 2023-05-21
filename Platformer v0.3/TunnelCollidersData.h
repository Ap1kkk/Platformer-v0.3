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
				vertices[1].Set(WIDTH_CENTER + 1920 - 715.f, HEIGHT_CENTER + 1080 - 0.f);
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
		}
		///--------- 16 туннель ---------

	}

	static std::map<short, CollidersDataVector> collidersMap;

	const float WIDTH_CENTER = -1920.f / 2;
	const float HEIGHT_CENTER = -1080.f / 2;
};