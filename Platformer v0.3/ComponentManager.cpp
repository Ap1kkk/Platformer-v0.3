#include "ComponentManager.h"

//std::unordered_map<ComponentId, std::any> ComponentManager::components = {};
std::unordered_map<ComponentId, IComponent*> ComponentManager::components = {};
std::unordered_map<ComponentId, ComponentType> ComponentManager::typeTable = {};
