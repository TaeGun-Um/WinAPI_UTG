#include "HouseFront_Map.h"

#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineCore/GameEngineRender.h>

#include "ContentsEnum.h"

HouseFront_Map::HouseFront_Map()
{
}

HouseFront_Map::~HouseFront_Map()
{
}

void HouseFront_Map::Start()
{
	// 724 159 4.55  // 724 70 10.34
	GameEngineRender* Render = CreateRender("HouseFront_Map.Bmp", RenderOrder::Map);
	Render->SetPosition({ 400, 780 });
	Render->SetScale({ 2275, 500 });
}