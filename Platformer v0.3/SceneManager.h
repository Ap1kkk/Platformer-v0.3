#pragma once

#include <unordered_map>

#include "IScene.h"
#include "ISceneManager.h"
#include "Debug.h"

class SceneManager : public ISceneManager
{
public:
	SceneManager() {}
	~SceneManager();

	void Initialize(SceneId startSceneId) override;

	void SetPauseScene(SceneId pauseSceneId) override;

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

	void SwitchToScene(SceneId newSceneId) override
	{
		SwitchScene(activeScene->GetSceneId(), newSceneId);
	}

	void ShowPauseScene() override;
	void HidePauseScene() override;

	void ProcessNotAwoken() override;
	void CaptureEvents() override;
	void EarlyUpdate() override;
	void Update() override;
	void LateUpdate() override;
	void UpdateUI() override;

	void UpdatePauseScene() override;

	void Draw(Window* window) override;

private:
	static std::unordered_map<SceneId, IScene*> scenes;
	static IScene* activeScene;
	static IScene* pauseScene;
};

