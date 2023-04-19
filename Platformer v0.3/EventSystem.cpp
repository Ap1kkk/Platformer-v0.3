#include "EventSystem.h"

//std::multimap<EventType, EventHandler*> EventSystementityHandlers::handlers = {};

std::multimap<EventType, std::pair<EntityId, IEntity*>> EventSystem::entityHandlers = {};
std::multimap<EventType, std::pair<ComponentId, IComponent*>> EventSystem::componentHandlers = {};