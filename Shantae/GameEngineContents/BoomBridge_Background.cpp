#include "BoomBridge_Background.h"

#include <GameEngineCore/GameEngineRender.h>

#include "ContentsEnum.h"

BoomBridge_Background::BoomBridge_Background() 
{
}

BoomBridge_Background::~BoomBridge_Background() 
{
}

void BoomBridge_Background::Start()
{
	GameEngineRender* Render = CreateRender("BoomBridge_Background.Bmp", RenderOrder::BackGround);
	Render->SetPosition(Render->GetImage()->GetImageScale().half());
	Render->SetScale(Render->GetImage()->GetImageScale());
}