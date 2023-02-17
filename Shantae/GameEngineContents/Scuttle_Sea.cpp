#include "Scuttle_Sea.h"

#include <GameEngineCore/GameEngineRender.h>

#include "ContentsEnum.h"

Scuttle_Sea::Scuttle_Sea() 
{
}

Scuttle_Sea::~Scuttle_Sea() 
{
}

void Scuttle_Sea::Start()
{
	GameEngineRender* Render = CreateRender("Move0_Sea.Bmp", RenderOrder::BackGround);
	Render->SetPosition({ 1000, 700 });
	Render->SetScale({ 2000, 400 });
	Render->EffectCameraOff();
}