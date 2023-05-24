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
			scenes.insert(std::make_pair(newSceneId, static_cast<IScene*>(scene)));
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

	void SwitchToScene(GameLevels nexteLevel) override
	{
		//SwitchScene(activeScene->GetSceneId(), newSceneId);
		isToSwitch = true;
		sceneIdToSwitch = (int)nexteLevel;
	}

	//void SwitchToScene(SceneId newSceneId) override
	//{
	//	//SwitchScene(activeScene->GetSceneId(), newSceneId);
	//	isToSwitch = true;
	//	sceneIdToSwitch = newSceneId;
	//}

	void ShowPauseScene() override;
	void HidePauseScene() override;

	//void ExitToMainMenu() override
	//{
	//	if (pauseScene != nullptr)
	//	{
	//		pauseScene->Destroy(false, true);
	//	}
	//	activeScene->Destroy(false, false);
	//}

	void ProcessNotAwoken() override;
	void CaptureEvents() override;
	void EarlyUpdate() override;
	void Update() override;
	void LateUpdate() override;
	void UpdateUI() override;

	void UpdatePauseScene() override;

	void UpdateSwitchBuffer() override
	{
		if (isToSwitch)
		{
			SwitchScene(activeScene->GetSceneId(), sceneIdToSwitch);
			isToSwitch = false;
		}
	}


	void Draw(Window* window) override;

private:
	static std::map<SceneId, IScene*> scenes;
	static IScene* activeScene;
	static IScene* pauseScene;

	static bool isToSwitch;
	static SceneId sceneIdToSwitch;
};

