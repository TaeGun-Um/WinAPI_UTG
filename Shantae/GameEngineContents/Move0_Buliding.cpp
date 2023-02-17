#include "Move0_Buliding.h"

#include <GameEngineCore/GameEngineRender.h>

#include "ContentsEnum.h"

Move0_Buliding::Move0_Buliding() 
{
}

Move0_Buliding::~Move0_Buliding() 
{
}

void Move0_Buliding::Start()
{
	// 3921 257 15.26
	GameEngineRender* Render = CreateRender("Move0_Buliding.Bmp", RenderOrder::BackGround);
	Render->SetPosition(Render->GetImage()->GetImageScale().half());
	Render->SetScale(Render->GetImage()->GetImageScale());
}