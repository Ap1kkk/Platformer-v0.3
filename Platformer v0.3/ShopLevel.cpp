#include "ShopLevel.h"

void ShopLevel::ProcessNotAwoken()
{
	ObjectCollection::ProcessNotAwoken();
	ObjectCollection::ProcessNotAwokenComponents();
}

void ShopLevel::EarlyUpdate()
{
	ObjectCollection::EarlyUpdate();
}

void ShopLevel::Update()
{
	ObjectCollection::Update();
}

void ShopLevel::LateUpdate()
{
	ObjectCollection::LateUpdate();
}

void ShopLevel::UpdateUI()
{
	ObjectCollection::UpdateUI();
}
