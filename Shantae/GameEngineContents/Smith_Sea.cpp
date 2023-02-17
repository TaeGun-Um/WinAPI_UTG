#include "Smith_Sea.h"

#include <GameEngineCore/GameEngineRender.h>

#include "ContentsEnum.h"

Smith_Sea::Smith_Sea() 
{
}

Smith_Sea::~Smith_Sea() 
{
}

void Smith_Sea::Start()
{
	GameEngineRender* Render = CreateRender("Move0_Sea.Bmp", RenderOrder::BackGround);
	Render->SetPosition({ 700, 700 });
	Render->SetScale({ 2000, 400 });
	Render->EffectCameraOff();
}