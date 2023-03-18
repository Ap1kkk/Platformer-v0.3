#include "IEntity.h"

EntityId IEntity::entityIdCounter = 0;

IEntity::~IEntity()
{
	Debug::LogWarning("Deleted with id: " + std::to_string(entityId), typeid(*this).name());
}