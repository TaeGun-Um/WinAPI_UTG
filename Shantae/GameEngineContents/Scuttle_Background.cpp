#include "Scuttle_Background.h"

#include <GameEngineCore/GameEngineRender.h>

#include "ContentsEnum.h"

Scuttle_Background::Scuttle_Background() 
{
}

Scuttle_Background::~Scuttle_Background() 
{
}

void Scuttle_Background::Start()
{
	GameEngineRender* Render = CreateRender("Scuttle_Background.Bmp", RenderOrder::BackGround);
	Render->SetPosition(Render->GetImage()->GetImageScale().half());
	Render->SetScale(Render->GetImage()->GetImageScale());
}