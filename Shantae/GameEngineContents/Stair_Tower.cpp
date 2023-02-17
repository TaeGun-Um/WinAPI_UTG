#include "Stair_Tower.h"

#include <GameEngineCore/GameEngineRender.h>

#include "ContentsEnum.h"

Stair_Tower::Stair_Tower() 
{
}

Stair_Tower::~Stair_Tower() 
{
}

void Stair_Tower::Start()
{
	// 60 184
	GameEngineRender* Render = CreateRender("Stair_Tower.Bmp", RenderOrder::BackGround);
	Render->SetPosition({ 600, 650 });
	Render->SetScale(Render->GetImage()->GetImageScale());
}