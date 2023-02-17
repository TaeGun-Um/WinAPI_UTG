#include "Move1_Sky.h"

#include <GameEngineCore/GameEngineRender.h>

#include "ContentsEnum.h"

Move1_Sky::Move1_Sky() 
{
}

Move1_Sky::~Move1_Sky() 
{
}

void Move1_Sky::Start()
{
	// 768 417 1.84
	GameEngineRender* Render = CreateRender("Move0_Sky.Bmp", RenderOrder::BackGround);
	Render->SetPosition({ 640, -80 });
	Render->SetScale({ 2200, 1177 });
	Render->EffectCameraOff();
}