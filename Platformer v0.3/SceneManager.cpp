#include "SceneManager.h"

std::unordered_map<SceneId, IScene*> SceneManager::scenes = {};
IScene* SceneManager::activeScene = nullptr;
IScene* SceneManager::pauseScene = nullptr;

SceneManager::~SceneManager()
{
	if (activeScene != nullptr)
	{
		activeScene->Destroy(true, false);
	}
}

void SceneManager::Initialize(SceneId startSceneId)
{
	auto startScene = GetSceneById(startSceneId);
	activeScene = startScene;
	startScene->Initialize();
}

void SceneManager::SetPauseScene(SceneId pauseSceneId)
{
	auto scene = GetSceneById(pauseSceneId);
	pauseScene = scene;
}

void SceneManager::DeleteScene(SceneId sceneId)
{
	auto itr = scenes.find(sceneId);
	if (itr != scenes.end())
	{
		itr->second->Destroy(true, false);
		scenes.erase(itr);
	}
	else
	{
		Debug::LogWarning("Scene with SceneId: " + std::to_string(sceneId) + " was already deleted", typeid(SceneManager).name());
	}
}

IScene* SceneManager::GetSceneById(SceneId sceneId)
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

void SceneManager::SwitchScene(SceneId fromSceneId, SceneId toSceneId)
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
			previousScene->Destroy(true, false);
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

void SceneManager::ShowPauseScene()
{
	if (pauseScene != nullptr)
	{
		pauseScene->Initialize();
	}
}

void SceneManager::HidePauseScene()
{
	if (pauseScene != nullptr)
	{
		pauseScene->Destroy(false, true);
	}
}

void SceneManager::ProcessNotAwoken()
{
	activeScene->ProcessNotAwoken();
}

void SceneManager::CaptureEvents()
{
	activeScene->CaptureEvents();
}

void SceneManager::EarlyUpdate()
{
	activeScene->EarlyUpdate();
}

void SceneManager::Update()
{
	activeScene->Update();
}

void SceneManager::LateUpdate()
{
	activeScene->LateUpdate();
}

void SceneManager::UpdateUI()
{
	activeScene->UpdateUI();
}

void SceneManager::UpdatePauseScene()
{
	if (pauseScene != nullptr)
	{
		pauseScene->ProcessNotAwoken();
		pauseScene->CaptureEvents();
		pauseScene->EarlyUpdate();
		pauseScene->Update();
		pauseScene->LateUpdate();
		pauseScene->UpdateUI();
	}
}

void SceneManager::Draw(Window* window)
{
	activeScene->Draw(window);
}
