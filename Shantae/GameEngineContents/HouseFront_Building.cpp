#include "HouseFront_Building.h"

#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineCore/GameEngineRender.h>

#include "ContentsEnum.h"

HouseFront_Building::HouseFront_Building() 
{
}

HouseFront_Building::~HouseFront_Building() 
{
}

void HouseFront_Building::Start()
{
	// 144 66 2.19
	GameEngineRender* Render = CreateRender("HouseFront_Building.Bmp", RenderOrder::BackGround);
	Render->SetPosition({ 1200, 450 });
	Render->SetScale({ 550, 250 });
}