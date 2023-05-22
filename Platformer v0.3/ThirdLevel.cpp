#include "ThirdLevel.h"

void ThirdLevel::ProcessNotAwoken()
{
	ObjectCollection::ProcessNotAwoken();
	ObjectCollection::ProcessNotAwokenComponents();
}

void ThirdLevel::EarlyUpdate()
{
	ObjectCollection::EarlyUpdate();
}

void ThirdLevel::Update()
{
	ObjectCollection::Update();
}

void ThirdLevel::LateUpdate()
{
	ObjectCollection::LateUpdate();
}

void ThirdLevel::UpdateUI()
{
	ObjectCollection::UpdateUI();
}
