#pragma once

#include <unordered_map>
#include <vector>

#include "box2d/box2d.h"

#include "Entity.h"
#include "Window.h"
#include "Debug.h"

class EntityManager
{
public:
	EntityManager();

	void Add(std::string name, Entity* entity);
	void Add(std::string name, std::string filename, bool dynamic);
	Entity* Get(std::string name);

	unsigned int GetEntityId(Entity& entity);

	//void EarlyUpdate(float deltaTime);
	void Update(float deltaTime);
	void LateUpdate(float deltaTime);
	void Draw(Window* window);

	~EntityManager();
private:
	//TODO заменить на хранение индексов сущностей
	std::unordered_map<std::string, Entity*> entities;

	b2World* world;
};

//class EntityManager
//{
//public:
//	EntityManager();
//
//	void Add(std::string name, Entity* entity);
//	void Add(std::string name, std::string filename, bool dynamic);
//
//	unsigned int GetEntityById(unsigned int id);
//
//	//void EarlyUpdate(float deltaTime);
//	void Update(float deltaTime);
//	void LateUpdate(float deltaTime);
//	void Draw(Window* window);
//
//	~EntityManager();
//private:
//	std::unordered_map<unsigned int, std::unique_ptr<Entity>> entities;
//
//	b2World* world;
//};
