#include "MainScene.h"

void MainScene::ProcessNotAwoken()
{
	ObjectCollection::ProcessNotAwoken();
	ObjectCollection::ProcessNotAwokenComponents();
}

void MainScene::EarlyUpdate()
{
	ObjectCollection::EarlyUpdate();
}

void MainScene::Update()
{
	ObjectCollection::Update();
}

void MainScene::LateUpdate()
{
	ObjectCollection::LateUpdate();
}

void MainScene::UpdateUI()
{
	ObjectCollection::UpdateUI();
}
