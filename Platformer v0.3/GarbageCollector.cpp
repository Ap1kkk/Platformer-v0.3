#include "GarbageCollector.h"

void GarbageCollector::DestroyEntity(EntityId entityId)
{
	Debug::LogWarning("Deleting entity with id: " + std::to_string(entityId), typeid(GarbageCollector).name());
	//TODO �������� ������� �� ���� ������
	//TODO ����� ��������� ��������� �������� ��� ����� ���������� ������ ������

	//RenderSystem::DeleteDrawable(entityId);
	//EntityManager::DestroyEntity(entityId);
	//ObjectCollection::DeleteObject(entityId);
}

void GarbageCollector::DestroyComponent(ComponentId componentId)
{
	//ComponentManager::DestroyComponent(componentId);
}