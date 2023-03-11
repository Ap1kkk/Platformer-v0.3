#pragma once

#include "EntityManager2.h"
#include "ComponentManager.h"

class GarbageCollector
{
public:
	// ������ ��� ������� ������� �� ���� ��������

	static void DestroyEntity(EntityId entityId)
	{
		//TODO �������� ������� �� ���� ������
		EntityManager2::DestroyEntity(entityId);
	}

	static void DestroyComponent(ComponentId componentId)
	{
		ComponentManager::DestroyComponent(componentId);
	}

	//TODO �������� ���������� � ��������� ������� � ������� ������ � ���������
};