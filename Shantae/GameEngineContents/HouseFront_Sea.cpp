#include "HouseFront_Sea.h"

#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineCore/GameEngineRender.h>

#include "ContentsEnum.h"

HouseFront_Sea::HouseFront_Sea() 
{
}

HouseFront_Sea::~HouseFront_Sea() 
{
}

void HouseFront_Sea::Start()
{
	// 801 288 2.78
	GameEngineRender* Render = CreateRender("HouseFront_Sea.Bmp", RenderOrder::BackGround);
	Render->SetPosition({ 550, 360 });
	Render->SetScale({ 2780, 1000 });
}