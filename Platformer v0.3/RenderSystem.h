#pragma once

#include <unordered_map>
#include <map>
#include <vector>

#include "Window.h"
#include "DrawableComponent.h"

#include "EventListener.h"
#include "OnEntityDestroyedEvent.h"

/// <summary>
/// Responsible for rendering objects to the window
/// </summary>
class RenderSystem : public EventListener
{
public:
	RenderSystem(Window* window);
	~RenderSystem()
	{
		//TODO добавить логику для очистки всех списков
	}

	void SubscribeOnEvents()
	{
		SubscribeOnEvent<OnEntityDestroyedEvent>();
	}

	void Draw();

	static void AddDrawable(EntityId entityId, DrawableComponent* drawable, bool isEnabled);

	static void DeleteDrawable(EntityId entityId);

	static void EnableDrawable(EntityId entityId);
	static void DisableDrawable(EntityId entityId);

	static void MoveActiveToPauseBuffer();
	static void RetrieveActiveFromPauseBuffer();

	void OnEventHappened(EventData& data) override
	{
		if (data.eventType == OnEntityDestroyedEvent::GetType())
		{
			Debug::Log("Deleting entity with id: " + std::to_string(data.id), typeid(*this).name());
			DeleteDrawable(data.id);
		}
	}

private:

	static void AddToDrawMap(EntityId entityId, DrawableComponent* drawable);

	static void DeleteFromDrawMap(EntityId entityId);

	static std::multimap<DrawLayer, std::pair< EntityId, DrawableComponent*>> drawMap;
	//TODO совместить все в один буфер
	static std::multimap<DrawLayer, std::pair< EntityId, DrawableComponent*>> drawPauseBuffer;

	static std::unordered_map<EntityId, DrawableComponent*> enabledDrawables;
	static std::unordered_map<EntityId, DrawableComponent*> disabledDrawables;
	static std::unordered_map<EntityId, DrawableComponent*> pauseBuffer;

	Window* window;
};

