#include "SecondLevel.h"

void SecondLevel::ProcessNotAwoken()
{
	ObjectCollection::ProcessNotAwoken();
	ObjectCollection::ProcessNotAwokenComponents();
}

void SecondLevel::EarlyUpdate()
{
	ObjectCollection::EarlyUpdate();
}

void SecondLevel::Update()
{
	ObjectCollection::Update();
}

void SecondLevel::LateUpdate()
{
	ObjectCollection::LateUpdate();
}

void SecondLevel::UpdateUI()
{
	ObjectCollection::UpdateUI();
}
