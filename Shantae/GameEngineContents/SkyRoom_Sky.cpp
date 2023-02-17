#include "SkyRoom_Sky.h"

#include <GameEngineCore/GameEngineRender.h>

#include "ContentsEnum.h"

SkyRoom_Sky::SkyRoom_Sky() 
{
}

SkyRoom_Sky::~SkyRoom_Sky() 
{
}

void SkyRoom_Sky::Start()
{
	GameEngineRender* Render = CreateRender("Scuttle_Sky.Bmp", RenderOrder::BackGround);
	Render->SetPosition({ 640, 300 });
	Render->SetScale(Render->GetImage()->GetImageScale());
	Render->EffectCameraOff();
}