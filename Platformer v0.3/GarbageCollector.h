#pragma once

#include "EntityManager.h"
#include "ComponentManager.h"

class GarbageCollector
{
public:
	// ������ ��� ������� ������� �� ���� ��������

	static void DestroyEntity(EntityId entityId)
	{
		//TODO �������� ������� �� ���� ������
		EntityManager::DestroyEntity(entityId);
	}

	static void DestroyComponent(ComponentId componentId)
	{
		ComponentManager::DestroyComponent(componentId);
	}

	//TODO �������� ���������� � ��������� ������� � ������� ������ � ���������
};