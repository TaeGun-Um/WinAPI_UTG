#include "Stair_Sky.h"

#include <GameEngineCore/GameEngineRender.h>

#include "ContentsEnum.h"

Stair_Sky::Stair_Sky() 
{
}

Stair_Sky::~Stair_Sky() 
{
}

void Stair_Sky::Start()
{
	// 768 417 1.84
	GameEngineRender* Render = CreateRender("Move0_Sky.Bmp", RenderOrder::BackGround);
	Render->SetPosition({ 640, 200 });
	Render->SetScale({ 2200, 1177 });
	Render->EffectCameraOff();
}