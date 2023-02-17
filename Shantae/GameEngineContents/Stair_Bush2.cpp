#include "Stair_Bush2.h"

#include <GameEngineCore/GameEngineRender.h>

#include "ContentsEnum.h"

Stair_Bush2::Stair_Bush2() 
{
}

Stair_Bush2::~Stair_Bush2() 
{
}

void Stair_Bush2::Start()
{
	// 358 736
	GameEngineRender* Render = CreateRender("Stair_Bush2.Bmp", RenderOrder::BackGround);
	Render->SetPosition({ 800, 2200 });
	Render->SetScale(Render->GetImage()->GetImageScale());
}