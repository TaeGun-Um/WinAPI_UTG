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





	// 98 189 0.519

}