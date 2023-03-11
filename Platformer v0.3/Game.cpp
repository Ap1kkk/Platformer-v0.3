#include "Game.h"

Game::Game() : window("Test window")
{
	assetAllocator = new AssetAllocator;
	entityManger = new EntityManager;
	deltaTime = clock.restart().asSeconds();

	this->entityManger->Add("floor", "floor.png", false);
	this->entityManger->Get("floor")->body->SetTransform(b2Vec2(0, -480), 0);

	this->entityManger->Add("ball", "ship.png", true);
	this->entityManger->Get("ball")->body->SetTransform(b2Vec2(24, 0), 0);

	this->entityManger->Add("ball2", "ship.png", true);
	this->entityManger->Get("ball2")->body->SetTransform(b2Vec2(84, 0), 0);
	this->entityManger->Add("ball3", "ship.png", true);
	this->entityManger->Get("ball3")->body->SetTransform(b2Vec2(75, -40), 0);
}

void Game::ProcessInput()
{
}

void Game::EarlyUpdate()
{
}

void Game::Update()
{
	window.Update();
	entityManger->Update(deltaTime);
}

void Game::LateUpdate()
{
}

void Game::Draw()
{
	window.BeginDraw();

	entityManger->Draw(&window);
	////TODO вызов отрисовки у объектов

	window.EndDraw();
}

void Game::CalculateDeltaTime()
{
	deltaTime = clock.restart().asSeconds();
}
