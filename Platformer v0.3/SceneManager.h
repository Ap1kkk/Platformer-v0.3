#pragma once

#include <unordered_map>

#include "IScene.h"
#include "Debug.h"

class SceneManager
{
public:
	SceneManager() {}
	~SceneManager()
	{
		if (activeScene != nullptr)
		{
			activeScene->Destroy();
		}
	}

	void Initialize(SceneId startSceneId)
	{
		auto startScene = GetSceneById(startSceneId);
		activeScene = startScene;
		startScene->Initialize();
	}

	template<class S>
	static S* const AddScene(SharedContext context)
	{
		auto scene = new S(context);
		SceneId newSceneId = scene->GetSceneId();
		auto itr = scenes.find(newSceneId);
		if (itr == scenes.end())
		{
			scenes.emplace(newSceneId, scene);
			return scene;
		}
		else
		{
			Debug::LogWarning("Scene with SceneId: " + std::to_string(newSceneId) + " is already added", typeid(SceneManager).name());
		}
	}

	static void DeleteScene(SceneId sceneId)
	{
		auto itr = scenes.find(sceneId);
		if (itr != scenes.end())
		{
			scenes.erase(itr);
		}
		else
		{
			Debug::LogWarning("Scene with SceneId: " + std::to_string(sceneId) + " was already deleted", typeid(SceneManager).name());
		}
	}

	static IScene* GetActiveScene() { return activeScene; }

	static IScene* GetSceneById(SceneId sceneId)
	{
		auto itr = scenes.find(sceneId);
		if (itr != scenes.end())
		{
			return itr->second;
		}
		else
		{
			Debug::LogError("Scene with SceneId: " + std::to_string(sceneId) + " was not found", typeid(SceneManager).name());
		}
	}

	static void SwitchScene(SceneId fromSceneId, SceneId toSceneId)
	{
		auto fromItr = scenes.find(fromSceneId);
		auto toItr = scenes.find(toSceneId);
		
		if (fromItr != scenes.end() && toItr != scenes.end())
		{
			Debug::Log("Switching from scene (" + std::to_string(fromSceneId) + ") to scene (" + std::to_string(toSceneId) + ")", typeid(SceneManager).name());
			auto previousScene = GetSceneById(fromSceneId);
			auto nextScene = GetSceneById(toSceneId);

			if (fromSceneId != toSceneId)
			{
				previousScene->Destroy();
			}
			else
			{
				previousScene->Reload();
			}
			nextScene->Initialize();

			activeScene = nextScene;
			Debug::Log("Switched from scene (" + std::to_string(fromSceneId) + ") to scene (" + std::to_string(toSceneId) + ")", typeid(SceneManager).name());
		}
		else
		{
			Debug::LogError("Cannot switch scene", typeid(SceneManager).name());
			if (fromItr == scenes.end())
			{
				Debug::LogError("Scene with SceneId: " + std::to_string(fromSceneId) + " was not found", typeid(SceneManager).name());
			}
			else
			{
				Debug::LogError("Scene with SceneId: " + std::to_string(toSceneId) + " was not found", typeid(SceneManager).name());
			}
		}
	}

	void EarlyUpdate(float deltaTime)
	{
		activeScene->EarlyUpdate(deltaTime);
	}

	void Update(float deltaTime)
	{
		activeScene->Update(deltaTime);
	}

	void LateUpdate(float deltaTime)
	{
		activeScene->LateUpdate(deltaTime);
	}

	void Draw(Window* window) 
	{
		activeScene->Draw(window);
	}

private:
	static std::unordered_map<SceneId, IScene*> scenes;
	static IScene* activeScene;
};

