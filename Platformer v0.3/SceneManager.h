#pragma once

#include <unordered_map>

#include "IScene.h"
#include "Debug.h"

class SceneManager
{
public:
	SceneManager() {}
	~SceneManager();

	void Initialize(SceneId startSceneId);

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

	static void DeleteScene(SceneId sceneId);

	static IScene* GetActiveScene() { return activeScene; }

	static IScene* GetSceneById(SceneId sceneId);

	static void SwitchScene(SceneId fromSceneId, SceneId toSceneId);

	void EarlyUpdate();
	void Update();
	void LateUpdate();

	void Draw(Window* window);

private:
	static std::unordered_map<SceneId, IScene*> scenes;
	static IScene* activeScene;
};

