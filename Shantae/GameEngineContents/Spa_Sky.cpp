#include "Spa_Sky.h"

#include <GameEngineCore/GameEngineRender.h>

#include "ContentsEnum.h"

Spa_Sky::Spa_Sky() 
{
}

Spa_Sky::~Spa_Sky() 
{
}

void Spa_Sky::Start()
{
	GameEngineRender* Render = CreateRender("Scuttle_Sky.Bmp", RenderOrder::BackGround);
	Render->SetPosition({ 640, 200 });
	Render->SetScale(Render->GetImage()->GetImageScale());
	Render->EffectCameraOff();
}