#include "SaveRoom_Sky.h"

#include <GameEngineCore/GameEngineRender.h>

#include "ContentsEnum.h"

SaveRoom_Sky::SaveRoom_Sky() 
{
}

SaveRoom_Sky::~SaveRoom_Sky() 
{
}

void SaveRoom_Sky::Start()
{
	GameEngineRender* Render = CreateRender("Scuttle_Sky.Bmp", RenderOrder::BackGround);
	Render->SetPosition({ 640, 200 });
	Render->SetScale(Render->GetImage()->GetImageScale());
	Render->EffectCameraOff();
}