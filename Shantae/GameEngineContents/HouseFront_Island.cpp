#include "HouseFront_Island.h"

#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineCore/GameEngineRender.h>

#include "ContentsEnum.h"

HouseFront_Island::HouseFront_Island() 
{
}

HouseFront_Island::~HouseFront_Island() 
{
}

void HouseFront_Island::Start()
{
	// 141 63 2.24
	GameEngineRender* Render = CreateRender("HouseFront_Island.Bmp", RenderOrder::BackGround);
	Render->SetPosition({ 1230, 540 });
	Render->SetScale({ 600, 213 });
}