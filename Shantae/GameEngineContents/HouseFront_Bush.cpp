#include "HouseFront_Bush.h"

#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineCore/GameEngineRender.h>

#include "ContentsEnum.h"

HouseFront_Bush::HouseFront_Bush() 
{
}

HouseFront_Bush::~HouseFront_Bush() 
{
}

void HouseFront_Bush::Start()
{
	// 630 268 2.35
	GameEngineRender* Render = CreateRender("HouseFront_Bush.Bmp", RenderOrder::BackGround);
	Render->SetPosition({ 620, 680 });
	Render->SetScale({ 1880, 800 });
}