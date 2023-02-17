#include "UncleRoom_Sky.h"

#include <GameEngineCore/GameEngineRender.h>

#include "ContentsEnum.h"

UncleRoom_Sky::UncleRoom_Sky() 
{
}

UncleRoom_Sky::~UncleRoom_Sky() 
{
}

void UncleRoom_Sky::Start()
{
	GameEngineRender* Render = CreateRender("Scuttle_Sky.Bmp", RenderOrder::BackGround);
	Render->SetPosition({ 640, 200 });
	Render->SetScale(Render->GetImage()->GetImageScale());
	Render->EffectCameraOff();
}