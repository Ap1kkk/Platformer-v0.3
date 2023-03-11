#pragma once

#include <iostream>
#include "SFML/Graphics.hpp"
#include "AssetAllocator.h"
#include "Window.h"
#include "EntityManager.h"

//TODO добавить указатель на менеджера сущностей

class Game
{
public:
	Game();

	void ProcessInput();
	void EarlyUpdate();
	void Update();
	void LateUpdate();
	void Draw();
	void CalculateDeltaTime();

	bool IsRunning() { return window.IsOpen(); }

private:
	Window window;
	AssetAllocator* assetAllocator;
	EntityManager* entityManger;

	sf::Clock clock;
	float deltaTime;
};

