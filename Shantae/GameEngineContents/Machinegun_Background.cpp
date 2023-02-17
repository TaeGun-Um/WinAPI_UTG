#include "Machinegun_Background.h"

#include <GameEngineCore/GameEngineRender.h>

#include "ContentsEnum.h"

Machinegun_Background::Machinegun_Background() 
{
}

Machinegun_Background::~Machinegun_Background() 
{
}

void Machinegun_Background::Start()
{
	// 409 841
	GameEngineRender* Render = CreateRender("Machinegun_Background.Bmp", RenderOrder::BackGround);
	Render->SetPosition(Render->GetImage()->GetImageScale().half());
	Render->SetScale(Render->GetImage()->GetImageScale());
}