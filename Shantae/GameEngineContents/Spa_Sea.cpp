#include "Spa_Sea.h"

#include <GameEngineCore/GameEngineRender.h>

#include "ContentsEnum.h"

Spa_Sea::Spa_Sea() 
{
}

Spa_Sea::~Spa_Sea() 
{
}

void Spa_Sea::Start()
{
	GameEngineRender* Render = CreateRender("Move0_Sea.Bmp", RenderOrder::BackGround);
	Render->SetPosition({ 700, 750 });
	Render->SetScale({ 2000, 400 });
	Render->EffectCameraOff();
}