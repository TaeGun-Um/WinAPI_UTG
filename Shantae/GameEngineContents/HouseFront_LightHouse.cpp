#include "HouseFront_LightHouse.h"

#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineCore/GameEngineRender.h>

#include "ContentsEnum.h"

HouseFront_LightHouse::HouseFront_LightHouse() 
{
}

HouseFront_LightHouse::~HouseFront_LightHouse() 
{
}

void HouseFront_LightHouse::Start()
{
	// 724 196 3.7
	GameEngineRender* Render = CreateRender("HouseFront_LightHouse.Bmp", RenderOrder::BackGround);
	Render->SetPosition({ 400, 405 });
	Render->SetScale({ 2257, 610 });
}