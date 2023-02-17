#include "HouseFront_ColMap.h"

#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineCore/GameEngineRender.h>

#include "ContentsEnum.h"

GameEngineRender* HouseFront_ColMap::ColMap = nullptr;

HouseFront_ColMap::HouseFront_ColMap() 
{
}

HouseFront_ColMap::~HouseFront_ColMap() 
{
}

void HouseFront_ColMap::Start()
{
	ColMap = CreateRender("HouseFront_ColMap.Bmp", RenderOrder::Map);
	ColMap->SetPosition(ColMap->GetImage()->GetImageScale().half());
	ColMap->SetScale(ColMap->GetImage()->GetImageScale());
	ColMap->Off();
}