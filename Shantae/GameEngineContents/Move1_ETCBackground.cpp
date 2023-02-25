#include "Move1_ETCBackground.h"

#include <GameEngineCore/GameEngineRender.h>

#include "ContentsEnum.h"

Move1_ETCBackground::Move1_ETCBackground() 
{
}

Move1_ETCBackground::~Move1_ETCBackground() 
{
}

void Move1_ETCBackground::Start()
{
	GameEngineRender* Bush0 = CreateRender("Move1_Bush.Bmp", RenderOrder::BackGround);
	Bush0->SetPosition({ 5375, 800 });
	Bush0->SetScale(Bush0->GetImage()->GetImageScale());

	GameEngineRender* Building4 = CreateRender("Building1.Bmp", RenderOrder::BackGround);
	Building4->SetPosition({ 9250, 500 });
	Building4->SetScale(Building4->GetImage()->GetImageScale());

	GameEngineRender* Building5 = CreateRender("Building1.Bmp", RenderOrder::BackGround);
	Building5->SetPosition({ 11150, 350 });
	Building5->SetScale(Building5->GetImage()->GetImageScale());
}