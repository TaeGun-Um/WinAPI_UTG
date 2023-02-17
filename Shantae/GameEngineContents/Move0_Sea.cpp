#include "Move0_Sea.h"

#include <GameEngineCore/GameEngineRender.h>

#include "ContentsEnum.h"

Move0_Sea::Move0_Sea() 
{
}

Move0_Sea::~Move0_Sea() 
{
}

void Move0_Sea::Start()
{
	GameEngineRender* Render = CreateRender("Move0_Sea.Bmp", RenderOrder::BackGround);
	Render->SetPosition({ 640, 550 });
	Render->SetScale({ 2000, 400 });
	Render->EffectCameraOff();
}