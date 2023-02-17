#include "Spa_Background.h"

#include <GameEngineCore/GameEngineRender.h>

#include "ContentsEnum.h"

Spa_Background::Spa_Background() 
{
}

Spa_Background::~Spa_Background() 
{
}

void Spa_Background::Start()
{
	GameEngineRender* Render = CreateRender("Spa_Background.Bmp", RenderOrder::BackGround);
	Render->SetPosition(Render->GetImage()->GetImageScale().half());
	Render->SetScale(Render->GetImage()->GetImageScale());
}