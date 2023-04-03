#pragma once

#include "DataTypes.h"
#include "Window.h"
#include "SharedContext.h"
#include "ObjectCollection.h"
#include "Debug.h"

class IScene
{
public:
	IScene(SharedContext sharedContext) : sceneId(sceneIdCounter++), sharedContext(sharedContext) 
	{
		objectContext.window = sharedContext.window;
	}
	virtual ~IScene() 
	{
		Debug::LogWarning("Scene with id: " + std::to_string(sceneId) + " destroyed");
	}

	virtual void Initialize() = 0;
	
	virtual void ProcessNotAwoken() = 0;
	virtual void CaptureEvents() = 0;
	virtual void EarlyUpdate() = 0;
	virtual void Update() = 0;
	virtual void LateUpdate() = 0;

	virtual void UpdateUI() = 0;

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

	void Destroy(bool shouldClearMemory, bool clearNotBufferedOnly)
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

	inline const SceneId GetSceneId() const { return sceneId; }

protected:
	SceneId sceneId;
	SharedContext sharedContext;
	ObjectContext objectContext;

private:
	static SceneId sceneIdCounter;
};