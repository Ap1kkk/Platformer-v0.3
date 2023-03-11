#include <SFML/Graphics.hpp>
#include <iostream>
#include <box2d/box2d.h>
#include "Game.h"


#include "EntityManager2.h"
#include "Entity2.h"
#include "TransformComponent.h"
#include "GameObject.h"

#include "Debug.h"

int main()
{
 //   Game game;
 //   
	//while (game.IsRunning())
	//{
	//	game.ProcessInput();
	//	game.EarlyUpdate();
	//	game.Update();
	//	game.LateUpdate();
	//	game.Draw();
	//	game.CalculateDeltaTime();
	//}

	EntityManager2* em2 = new EntityManager2;

	auto gameObj = EntityManager2::CreateEntity<GameObject>();

	std::string str = "string";

	ComponentManager::CreateComponent<DrawableComponent>();
	//gameObj->AddComponent<TransformComponent>();

	//auto transform = gameObj->GetComponent<TransformComponent>();
	//transform->Foo();
	//gameObj->DeleteComponent(transform->GetComponentId());
	//gameObj->Destroy();

	delete em2;
}