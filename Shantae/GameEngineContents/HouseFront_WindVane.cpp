#include "HouseFront_WindVane.h"

#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineCore/GameEngineRender.h>

#include "ContentsEnum.h"

HouseFront_WindVane::HouseFront_WindVane() 
{
}

HouseFront_WindVane::~HouseFront_WindVane() 
{
}

void HouseFront_WindVane::Start()
{
	GameEngineRender* Render = CreateRender(RenderOrder::Monster);
	Render->CreateAnimation({ .AnimationName = "WindVane",  .ImageName = "HouseFront_WindVane.bmp", .Start = 0, .End = 13 });
	Render->SetPosition({ 230, 80 });
	Render->SetScale({ 50, 50 });

	Render->ChangeAnimation("WindVane");
}