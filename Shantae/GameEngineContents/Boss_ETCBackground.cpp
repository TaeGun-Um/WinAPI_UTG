#include "Boss_ETCBackground.h"

#include <GameEngineCore/GameEngineRender.h>

#include "ContentsEnum.h"

Boss_ETCBackground::Boss_ETCBackground() 
{
}

Boss_ETCBackground::~Boss_ETCBackground() 
{
}

void Boss_ETCBackground::Start()
{
	GameEngineRender* Bush0 = CreateRender("Boss_Bush1.Bmp", RenderOrder::BackGround);
	Bush0->SetPosition({ 910, 490 });
	Bush0->SetScale(Bush0->GetImage()->GetImageScale());

	GameEngineRender* Bush1 = CreateRender("Boss_Bush2.Bmp", RenderOrder::BackGround);
	Bush1->SetPosition({ 550, 50 });
	Bush1->SetScale(Bush1->GetImage()->GetImageScale());

	GameEngineRender* Building0 = CreateRender("Building1.Bmp", RenderOrder::BackGround);
	Building0->SetPosition({ 585, 570 });
	Building0->SetScale(Building0->GetImage()->GetImageScale());
}