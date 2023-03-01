#include "ItemSelect.h"

#include <GameEngineCore/GameEngineRender.h>

#include "ContentsEnum.h"

ItemSelect::ItemSelect() 
{
}

ItemSelect::~ItemSelect() 
{
}

void ItemSelect::Start()
{
	AnimationRender = CreateRender(RenderOrder::UI);
	AnimationRender->SetScale({ 300, 300 });
	AnimationRender->CreateAnimation({ .AnimationName = "Icon",  .ImageName = "ItemSelect.bmp", .Start = 1, .End = 1, .InterTime = 10.0f, .Loop = false });
	AnimationRender->ChangeAnimation("Icon");
	AnimationRender->EffectCameraOff();
}

void ItemSelect::Update(float _DeltaTime)
{

}

void ItemSelect::Render(float _DeltaTime)
{

}