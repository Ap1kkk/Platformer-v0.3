#include "MainMenu.h"

void MainMenu::ProcessNotAwoken()
{
	ObjectCollection::ProcessNotAwoken();
	ObjectCollection::ProcessNotAwokenComponents();
}

void MainMenu::EarlyUpdate()
{
	ObjectCollection::EarlyUpdate();
}

void MainMenu::Update()
{
	ObjectCollection::Update();
}

void MainMenu::LateUpdate()
{
	ObjectCollection::LateUpdate();
}

void MainMenu::UpdateUI()
{
	ObjectCollection::UpdateUI();
}
