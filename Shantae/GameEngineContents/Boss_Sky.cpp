#include "Boss_Sky.h"

#include <GameEngineCore/GameEngineRender.h>

#include "ContentsEnum.h"

Boss_Sky::Boss_Sky() 
{
}

Boss_Sky::~Boss_Sky() 
{
}

void Boss_Sky::Start()
{
	GameEngineRender* Render = CreateRender("Move0_Sky.Bmp", RenderOrder::BackGround);
	Render->SetPosition({ 1000, 0 });
	Render->SetScale({ 2200, 1177 });
	Render->EffectCameraOff();
}