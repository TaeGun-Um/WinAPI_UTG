#include "SaveRoom_Sea.h"

#include <GameEngineCore/GameEngineRender.h>

#include "ContentsEnum.h"

SaveRoom_Sea::SaveRoom_Sea() 
{
}

SaveRoom_Sea::~SaveRoom_Sea() 
{
}

void SaveRoom_Sea::Start()
{
	GameEngineRender* Render = CreateRender("Move0_Sea.Bmp", RenderOrder::BackGround);
	Render->SetPosition({ 1000, 750 });
	Render->SetScale({ 2000, 400 });
	Render->EffectCameraOff();
}