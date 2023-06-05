#pragma once

#include "SFML/Graphics.hpp"
#include "EventData.h"

struct PlayerDataRequestData : public UserEventData
{
	sf::Vector2f position;
	short healthPoints;
};