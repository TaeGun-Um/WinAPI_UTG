#include "Move0_ETCBackground.h"

#include <GameEngineCore/GameEngineRender.h>

#include "ContentsEnum.h"

Move0_ETCBackground::Move0_ETCBackground() 
{
}

Move0_ETCBackground::~Move0_ETCBackground() 
{
}

void Move0_ETCBackground::Start()
{
	// 1190 x 397 3
	GameEngineRender* Bush0 = CreateRender("Move0_Bush.Bmp", RenderOrder::BackGround);
	Bush0->SetPosition({ 3800, 750 });
	Bush0->SetScale(Bush0->GetImage()->GetImageScale());

	// 220 155 1.42
	GameEngineRender* Ship0 = CreateRender("Ship.Bmp", RenderOrder::BackGround);
	Ship0->SetPosition({ 1250, 400 });
	Ship0->SetScale(Ship0->GetImage()->GetImageScale());

	GameEngineRender* Ship1 = CreateRender("Ship.Bmp", RenderOrder::BackGround);
	Ship1->SetPosition({ 5850, 400 });
	Ship1->SetScale(Ship1->GetImage()->GetImageScale());

	// 97 188 0.516
	GameEngineRender* Building0 = CreateRender("Building1.Bmp", RenderOrder::BackGround);
	Building0->SetPosition({ 3000, 100 });
	Building0->SetScale(Building0->GetImage()->GetImageScale());

	GameEngineRender* Building1 = CreateRender("Building1.Bmp", RenderOrder::BackGround);
	Building1->SetPosition({ 5030, 350 });
	Building1->SetScale(Building1->GetImage()->GetImageScale());

	// 98 189 0.519
	GameEngineRender* Building2 = CreateRender("Building2.Bmp", RenderOrder::BackGround);
	Building2->SetPosition({ 9550, 300 });
	Building2->SetScale(Building2->GetImage()->GetImageScale());
}