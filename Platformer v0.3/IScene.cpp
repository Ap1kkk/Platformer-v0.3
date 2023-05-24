#include "IScene.h"

SceneId IScene::sceneIdCounter = 0;

IScene::IScene(SharedContext sharedContext) : sceneId(sceneIdCounter++), sharedContext(sharedContext)
{
	objectContext.window = sharedContext.window;
	objectContext.eventSystem = sharedContext.eventSystem;
	objectContext.sceneManager = sharedContext.sceneManager;
	objectContext.gameStateMachine = sharedContext.gameStateMachine;
}

IScene::~IScene()
{
	Debug::LogWarning("Scene with id: " + std::to_string(sceneId) + " destroyed");
}

void IScene::Reload()
{
	OnReload();
	ObjectCollection::Clear();
}

void IScene::Destroy(bool shouldClearMemory, bool clearNotBufferedOnly)
{
	OnDestroy();
	if (clearNotBufferedOnly)
	{
		ObjectCollection::ClearNotBuffured();
	}
	else
	{
		ObjectCollection::Clear();
	}
	if (shouldClearMemory)
	{
		delete this;
	}
}
