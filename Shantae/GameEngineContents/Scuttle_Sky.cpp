#include "Scuttle_Sky.h"

#include <GameEngineCore/GameEngineRender.h>

#include "ContentsEnum.h"

Scuttle_Sky::Scuttle_Sky() 
{
}

Scuttle_Sky::~Scuttle_Sky() 
{
}

void Scuttle_Sky::Start()
{
	 GameEngineRender* Render = CreateRender("Scuttle_Sky.Bmp", RenderOrder::BackGround);
	 Render->SetPosition({ 640, -80 });
	 Render->SetScale(Render->GetImage()->GetImageScale());
	 Render->EffectCameraOff();
}