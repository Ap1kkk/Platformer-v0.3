#pragma once

#include "SFML/Graphics.hpp"
#include "DataTypes.h"

class Time
{
public:
	Time() {}

	static float DeltaTime() { return deltaTime; }
	static float FixedDeltaTime() { return FIXED_DELTA_TIME; }
	static void Restart() {	deltaTime = clock.restart().asSeconds(); }
	static float physicsTimeAccumulator;
private:
	static sf::Clock clock;
	static float deltaTime;
};

