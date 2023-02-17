#include "Shop_ColMap.h"

#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineCore/GameEngineRender.h>

#include "ContentsEnum.h"

GameEngineRender* Shop_ColMap::ColMap = nullptr;

Shop_ColMap::Shop_ColMap() 
{
}

Shop_ColMap::~Shop_ColMap() 
{
}

void Shop_ColMap::Start()
{
	ColMap = CreateRender("Shop_ColMap.Bmp", RenderOrder::Map);
	ColMap->SetPosition(ColMap->GetImage()->GetImageScale().half());
	ColMap->SetScale(ColMap->GetImage()->GetImageScale());
	ColMap->Off();
}