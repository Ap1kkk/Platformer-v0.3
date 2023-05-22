#include "FourthLevel.h"

void FourthLevel::ProcessNotAwoken()
{
	ObjectCollection::ProcessNotAwoken();
	ObjectCollection::ProcessNotAwokenComponents();
}

void FourthLevel::EarlyUpdate()
{
	ObjectCollection::EarlyUpdate();
}

void FourthLevel::Update()
{
	ObjectCollection::Update();
}

void FourthLevel::LateUpdate()
{
	ObjectCollection::LateUpdate();
}

void FourthLevel::UpdateUI()
{
	ObjectCollection::UpdateUI();
}
