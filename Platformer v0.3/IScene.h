#pragma once

#include "DataTypes.h"
#include "Window.h"
#include "SharedContext.h"
#include "ObjectCollection.h"
//#include "GarbageCollector.h"
#include "Debug.h"

class IScene
{
public:
	IScene(SharedContext sharedContext) : sceneId(sceneIdCounter++), sharedContext(sharedContext) {}
	virtual ~IScene() 
	{
		Debug::LogWarning("Scene with id: " + std::to_string(sceneId) + " destroyed");
	}

	virtual void Initialize() = 0;

	virtual void EarlyUpdate(float deltaTime) = 0;
	virtual void Update(float deltaTime) = 0;
	virtual void LateUpdate(float deltaTime) = 0;

	// ���������� ��� ����������� ��������� ����, ��� �� ������ � ������� �������
	virtual void Draw(Window* window) {}

	// ���������� ����� ������������ �����
	virtual void OnDestroy() {}
	// ���������� ����� ������������� �����
	virtual void OnReload() {}

	virtual void Reload()
	{
		OnReload();
		ObjectCollection::Clear();
	}

	void Destroy()
	{
		OnDestroy();
		ObjectCollection::Clear();
		delete this;
	}

	inline const SceneId GetSceneId() const { return sceneId; }

protected:
	SceneId sceneId;
	SharedContext sharedContext;

private:
	static SceneId sceneIdCounter;
};