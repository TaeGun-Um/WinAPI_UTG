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

	GameEngineRender* Building0 = CreateRender("Building1.Bmp", RenderOrder::BackGround);
	Building0->SetPosition({ 1700, 20 });
	Building0->SetScale(Building0->GetImage()->GetImageScale());

	GameEngineRender* Building1 = CreateRender("Building1.Bmp", RenderOrder::BackGround);
	Building1->SetPosition({ 3950, 15 });
	Building1->SetScale(Building1->GetImage()->GetImageScale());

	GameEngineRender* Building2 = CreateRender("Building1.Bmp", RenderOrder::BackGround);
	Building2->SetPosition({ 8350, 70 });
	Building2->SetScale(Building2->GetImage()->GetImageScale());

	GameEngineRender* Building3 = CreateRender("Building1.Bmp", RenderOrder::BackGround);
	Building3->SetPosition({ 8800, -65 });
	Building3->SetScale(Building3->GetImage()->GetImageScale());

	GameEngineRender* Building4 = CreateRender("Building1.Bmp", RenderOrder::BackGround);
	Building4->SetPosition({ 9250, 500 });
	Building4->SetScale(Building4->GetImage()->GetImageScale());

	GameEngineRender* Building5 = CreateRender("Building1.Bmp", RenderOrder::BackGround);
	Building5->SetPosition({ 11150, 350 });
	Building5->SetScale(Building5->GetImage()->GetImageScale());

	GameEngineRender* Ship0 = CreateRender("Ship.Bmp", RenderOrder::BackGround);
	Ship0->SetPosition({ 6475, 425 });
	Ship0->SetScale(Ship0->GetImage()->GetImageScale());
}