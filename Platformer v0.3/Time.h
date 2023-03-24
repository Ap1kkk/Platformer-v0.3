#pragma once

#include "SFML/Graphics.hpp"

class Time
{
public:
	Time() {}

	static float DeltaTime() { return deltaTime; }
	static float FixedDeltaTime() { return 1.f / 30.f; }
	static void Restart() {	deltaTime = clock.restart().asSeconds(); }
	static float physicsTimeAccumulator;
private:
	static sf::Clock clock;
	static float deltaTime;
};

