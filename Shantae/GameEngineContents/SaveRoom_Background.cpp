#include "SaveRoom_Background.h"

#include <GameEngineCore/GameEngineRender.h>

#include "ContentsEnum.h"

SaveRoom_Background::SaveRoom_Background() 
{
}

SaveRoom_Background::~SaveRoom_Background() 
{
}

void SaveRoom_Background::Start()
{
	GameEngineRender* Render = CreateRender("SaveRoom_Background.Bmp", RenderOrder::BackGround);
	Render->SetPosition(Render->GetImage()->GetImageScale().half());
	Render->SetScale(Render->GetImage()->GetImageScale());
}