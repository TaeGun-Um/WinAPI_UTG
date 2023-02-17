#include "Move1_Buliding.h"

#include <GameEngineCore/GameEngineRender.h>

#include "ContentsEnum.h"

Move1_Buliding::Move1_Buliding() 
{
}

Move1_Buliding::~Move1_Buliding() 
{
}

void Move1_Buliding::Start()
{
	// 3858 302 12.77
	GameEngineRender* Render = CreateRender("Move1_Buliding.Bmp", RenderOrder::BackGround);
	Render->SetPosition(Render->GetImage()->GetImageScale().half());
	Render->SetScale(Render->GetImage()->GetImageScale());
}