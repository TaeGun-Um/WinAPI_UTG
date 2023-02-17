#include "BeforeBoss_Background.h"

#include <GameEngineCore/GameEngineRender.h>

#include "ContentsEnum.h"

BeforeBoss_Background::BeforeBoss_Background() 
{
}

BeforeBoss_Background::~BeforeBoss_Background() 
{
}

void BeforeBoss_Background::Start()
{
	GameEngineRender* Render = CreateRender("BeforeBoss_Background.Bmp", RenderOrder::BackGround);
	Render->SetPosition(Render->GetImage()->GetImageScale().half());
	Render->SetScale(Render->GetImage()->GetImageScale());
}