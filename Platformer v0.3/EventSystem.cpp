#include "EventSystem.h"

//std::multimap<EventType, EventHandler*> EventSystementityHandlers::handlers = {};

std::multimap<EventType, std::pair<EntityId, IEventListener*>> EventSystem::handlers = {};
//std::multimap<EventType, std::pair<ComponentId, IEventListener*>> EventSystem::componentHandlers = {};