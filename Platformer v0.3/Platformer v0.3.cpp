#include <SFML/Graphics.hpp>
#include <iostream>
#include <box2d/box2d.h>
#include "Game.h"

// ----FOR TEST-----
//#include "EntityManager.h"
//#include "Entity.h"
//#include "TransformComponent.h"
//#include "GameObject.h"

#include "Debug.h"

int main()
{
    Game game(b2Vec2(0, 10));
    
	while (game.IsRunning())
	{
		game.ProcessInput();
		game.EarlyUpdate();
		game.Update();
		game.LateUpdate();
		game.Draw();
		game.CalculateDeltaTime();
	}

	// ----FOR TEST-----

	//EntityManager* em2 = new EntityManager;

	//auto gameObj = EntityManager::CreateEntity<GameObject>();

	//std::string str = "string";

	//ComponentManager::CreateComponent<DrawableComponent>();
	////gameObj->AddComponent<TransformComponent>();

	////auto transform = gameObj->GetComponent<TransformComponent>();
	////transform->Foo();
	////gameObj->DeleteComponent(transform->GetComponentId());
	////gameObj->Destroy();

	//delete em2;
}