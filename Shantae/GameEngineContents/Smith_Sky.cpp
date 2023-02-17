#include "Smith_Sky.h"

#include <GameEngineCore/GameEngineRender.h>

#include "ContentsEnum.h"

Smith_Sky::Smith_Sky() 
{
}

Smith_Sky::~Smith_Sky() 
{
}

void Smith_Sky::Start()
{
	GameEngineRender* Render = CreateRender("Scuttle_Sky.Bmp", RenderOrder::BackGround);
	Render->SetPosition({ 640, 300 });
	Render->SetScale(Render->GetImage()->GetImageScale());
	Render->EffectCameraOff();
}