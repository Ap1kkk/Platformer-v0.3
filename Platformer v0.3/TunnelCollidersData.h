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
	}

	static std::map<short, CollidersDataVector> collidersMap;

	const float WIDTH_CENTER = -1920.f / 2;
	const float HEIGHT_CENTER = -1080.f / 2;
};