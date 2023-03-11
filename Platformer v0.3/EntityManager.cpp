#include "EntityManager.h"

EntityManager::EntityManager()
{
	this->world = new b2World(b2Vec2(0, -10));
}

void EntityManager::Add(std::string name, Entity* entity)
{
	auto found = this->entities.find(name);
	while (found != this->entities.end())
	{
		name += "0";
		found = this->entities.find(name);
	}
	this->entities.insert(std::make_pair(name, entity));
}

void EntityManager::Add(std::string name, std::string filename, bool dynamic)
{
	auto found = this->entities.find(name);
	while (found != this->entities.end())
	{
		name += "0";
		found = this->entities.find(name);
	}
	Entity* entity = new Entity(this->world);
	entity->Load(filename, dynamic);
	this->entities.insert(std::make_pair(name, entity));
}

Entity* EntityManager::Get(std::string name)
{
	auto found = this->entities.find(name);

	if (found == this->entities.end())
	{
		return NULL;
	}
	else
	{
		return found->second;
	}
}

unsigned int EntityManager::GetEntityId(Entity& entity)
{
	return 0;
}

void EntityManager::Update(float deltaTime)
{
	std::vector<std::string> toRemove;

	this->world->Step(1.f/60.f, 6, 2);

	for (auto& iterator : this->entities)
	{
		/*switch (iterator.second->Active())
		{
		case 0:
			toRemove.push_back(iterator.first);
			break;
		default:
			iterator.second->Update(deltaTime);
			break;
		}*/

		iterator.second->Update(deltaTime);
	}

	for (auto& iterator : toRemove)
	{
		std::unordered_map<std::string, Entity*>::const_iterator found = this->entities.find(iterator);

		if (found != this->entities.end())
		{
			delete found->second;
			this->entities.erase(iterator);
		}
	}
	toRemove.clear();
}

void EntityManager::LateUpdate(float deltaTime)
{

}

void EntityManager::Draw(Window* window)
{
	for (auto& iterator : this->entities)
	{
		window->Draw(iterator.second);
	}
	Debug::Draw(window);
}

EntityManager::~EntityManager()
{
	for (auto& iterator : this->entities)
	{
		delete iterator.second;
	}
	this->entities.clear();
	delete this->world;
}


