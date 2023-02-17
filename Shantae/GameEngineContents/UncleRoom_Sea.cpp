#include "UncleRoom_Sea.h"

#include <GameEngineCore/GameEngineRender.h>

#include "ContentsEnum.h"

UncleRoom_Sea::UncleRoom_Sea() 
{
}

UncleRoom_Sea::~UncleRoom_Sea() 
{
}

void UncleRoom_Sea::Start()
{
	GameEngineRender* Render = CreateRender("Move0_Sea.Bmp", RenderOrder::BackGround);
	Render->SetPosition({ 700, 750 });
	Render->SetScale({ 2000, 400 });
	Render->EffectCameraOff();
}