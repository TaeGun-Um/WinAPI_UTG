#include "SkyRoom_Background.h"

#include <GameEngineCore/GameEngineRender.h>

#include "ContentsEnum.h"

SkyRoom_Background::SkyRoom_Background() 
{
}

SkyRoom_Background::~SkyRoom_Background() 
{
}

void SkyRoom_Background::Start()
{
	GameEngineRender* Render = CreateRender("SkyRoom_Background.Bmp", RenderOrder::BackGround);
	Render->SetPosition(Render->GetImage()->GetImageScale().half());
	Render->SetScale(Render->GetImage()->GetImageScale());
}