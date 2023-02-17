#include "Move1_Sea.h"

#include <GameEngineCore/GameEngineRender.h>

#include "ContentsEnum.h"

Move1_Sea::Move1_Sea() 
{
}

Move1_Sea::~Move1_Sea() 
{
}

void Move1_Sea::Start()
{
	// 768 417 1.84
	GameEngineRender* Render = CreateRender("Move0_Sea.Bmp", RenderOrder::BackGround);
	Render->SetPosition({ 640, 550 });
	Render->SetScale({ 2000, 400 });
	Render->EffectCameraOff();
}