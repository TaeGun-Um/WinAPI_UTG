#include "Smith_Background.h"

#include <GameEngineCore/GameEngineRender.h>

#include "ContentsEnum.h"

Smith_Background::Smith_Background() 
{
}

Smith_Background::~Smith_Background() 
{
}

void Smith_Background::Start()
{
	GameEngineRender* Render = CreateRender("Smith_Background.Bmp", RenderOrder::BackGround);
	Render->SetPosition(Render->GetImage()->GetImageScale().half());
	Render->SetScale(Render->GetImage()->GetImageScale());
}