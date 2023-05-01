#pragma once

#include <map>

#include "IEventSystem.h"

#include "Debug.h"

class EventSystem : public IEventSystem
{
public:

	void HandleEvent(const EventData& eventData) override
	{
		Debug::Log("Handle event from event system");

		for (auto itr = handlers.lower_bound(eventData.eventType); itr != handlers.upper_bound(eventData.eventType); ++itr)
		{
			itr->second.second->OnEventHappened(eventData);
		}
	}

	void AddEventListener(EventType eventType, ListenerId listenerId, IEventListener* listener) override
	{
		bool isExists = false;

		for (auto itr = handlers.lower_bound(eventType); itr != handlers.upper_bound(eventType); ++itr)
		{
			if (listenerId == itr->second.first)
			{
				isExists = true;
				break;
			}
		}

		if (isExists)
		{
			Debug::LogError("Can't add event listener\nListener to event type: " + eventType + " is already added with ListenerId:" + std::to_string(listenerId));
		}
		else
		{
			handlers.emplace(std::make_pair(eventType, std::make_pair(listenerId, listener)));
			Debug::LogInfo("Event listener with type: " + eventType + " added with ListenerId: " + std::to_string(listenerId));
		}
	}

	void RemoveEventListener(EventType eventType, ListenerId listenerId) override
	{
		bool isExists = false;

		for (auto itr = handlers.lower_bound(eventType); itr != handlers.upper_bound(eventType); ++itr)
		{
			if (listenerId == itr->second.first)
			{
				isExists = true;
				Debug::LogInfo("Event listener with type: " + eventType + " removed with ListenerId: " + std::to_string(listenerId));
				handlers.erase(itr);
				break;
			}
		}

		if (!isExists)
		{
			Debug::LogError("Can't add event listener\nListener to event type: " + eventType + " is already added with ListenerId:" + std::to_string(listenerId));
		}
	}

private:
	static std::multimap<EventType, std::pair<ListenerId, IEventListener*>> handlers;
};

