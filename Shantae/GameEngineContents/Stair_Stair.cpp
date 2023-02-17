#include "Stair_Stair.h"

#include <GameEngineCore/GameEngineRender.h>

#include "ContentsEnum.h"

Stair_Stair::Stair_Stair() 
{
}

Stair_Stair::~Stair_Stair() 
{
}

void Stair_Stair::Start()
{
	// 541 928
	GameEngineRender* Render = CreateRender("Stair_Stair.Bmp", RenderOrder::BackGround);
	Render->SetPosition(Render->GetImage()->GetImageScale().half());
	Render->SetScale(Render->GetImage()->GetImageScale());
}