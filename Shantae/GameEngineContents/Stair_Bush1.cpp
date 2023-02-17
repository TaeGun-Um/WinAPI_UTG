#include "Stair_Bush1.h"

#include <GameEngineCore/GameEngineRender.h>

#include "ContentsEnum.h"

Stair_Bush1::Stair_Bush1() 
{
}

Stair_Bush1::~Stair_Bush1() 
{
}

void Stair_Bush1::Start()
{
	// 409 841
	GameEngineRender* Render = CreateRender("Stair_Bush1.Bmp", RenderOrder::BackGround);
	Render->SetPosition({ 800, 2200 });
	Render->SetScale(Render->GetImage()->GetImageScale());
}