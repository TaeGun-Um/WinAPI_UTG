#include "UncleRoom_Background.h"

#include <GameEngineCore/GameEngineRender.h>

#include "ContentsEnum.h"

UncleRoom_Background::UncleRoom_Background() 
{
}

UncleRoom_Background::~UncleRoom_Background() 
{
}

void UncleRoom_Background::Start()
{
	GameEngineRender* Render = CreateRender("UncleRoom_Background.Bmp", RenderOrder::BackGround);
	Render->SetPosition(Render->GetImage()->GetImageScale().half());
	Render->SetScale(Render->GetImage()->GetImageScale());
}