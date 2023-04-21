#include "EventSystem.h"

//std::multimap<EventType, EventHandler*> EventSystementityHandlers::handlers = {};

std::multimap<EventType, std::pair<EntityId, IEventListener*>> EventSystem::entityHandlers = {};
std::multimap<EventType, std::pair<ComponentId, IEventListener*>> EventSystem::componentHandlers = {};