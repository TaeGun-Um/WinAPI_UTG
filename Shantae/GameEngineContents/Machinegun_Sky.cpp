#include "Machinegun_Sky.h"

#include <GameEngineCore/GameEngineRender.h>

#include "ContentsEnum.h"

Machinegun_Sky::Machinegun_Sky() 
{
}

Machinegun_Sky::~Machinegun_Sky() 
{
}

void Machinegun_Sky::Start()
{
	GameEngineRender* Render = CreateRender("Move0_Sky.Bmp", RenderOrder::BackGround);
	Render->SetPosition({ 1000, 0 });
	Render->SetScale({ 2200, 1177 });
	Render->EffectCameraOff();
}