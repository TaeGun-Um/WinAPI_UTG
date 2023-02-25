#include "Sea.h"

#include <GameEngineCore/GameEngineRender.h>

#include "ContentsEnum.h"

Sea::Sea()
{
}

Sea::~Sea()
{
}

void Sea::Start()
{
	GameEngineRender* Render = CreateRender("Sea.Bmp", RenderOrder::BackGround);
	Render->SetPosition({ 640, 550 });
	Render->SetScale({ 2000, 400 });
	Render->EffectCameraOff();
}