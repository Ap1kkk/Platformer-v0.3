#include "FirstLevel.h"

void FirstLevel::ProcessNotAwoken()
{
	ObjectCollection::ProcessNotAwoken();
	ObjectCollection::ProcessNotAwokenComponents();
}

void FirstLevel::EarlyUpdate()
{
	ObjectCollection::EarlyUpdate();
}

void FirstLevel::Update()
{
	ObjectCollection::Update();
}

void FirstLevel::LateUpdate()
{
	ObjectCollection::LateUpdate();
}

void FirstLevel::UpdateUI()
{
	ObjectCollection::UpdateUI();
}
