#include "WorldContactListener.h"

std::multimap<Bitmask, std::pair<EntityId, IEntity*>> WorldContactListener::entityHandlers = {};
std::multimap<Bitmask, std::pair<ComponentId, IComponent*>> WorldContactListener::componentHandlers = {};