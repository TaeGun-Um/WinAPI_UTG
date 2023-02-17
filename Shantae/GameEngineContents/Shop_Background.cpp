#include "Shop_Background.h"

#include <GameEngineCore/GameEngineRender.h>

#include "ContentsEnum.h"

Shop_Background::Shop_Background() 
{
}

Shop_Background::~Shop_Background() 
{
}

void Shop_Background::Start()
{
	GameEngineRender* Render = CreateRender("Shop_Background.Bmp", RenderOrder::BackGround);
	Render->SetPosition(Render->GetImage()->GetImageScale().half());
	Render->SetScale(Render->GetImage()->GetImageScale());
}