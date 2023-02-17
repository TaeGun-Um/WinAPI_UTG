#include "Soldier_Pile.h"

#include <GameEngineCore/GameEngineResources.h>
#include <GameEngineCore/GameEngineRender.h>

#include "ContentsEnum.h"

Soldier_Pile::Soldier_Pile() 
{
}

Soldier_Pile::~Soldier_Pile() 
{
}

void Soldier_Pile::Start()
{
	AnimationRender = CreateRender(RenderOrder::BackGround);
	AnimationRender->SetScale({ 1500, 1400 });
	AnimationRender->SetPosition({ 1090, 6614 });
	AnimationRender->CreateAnimation({ .AnimationName = "Pile",  .ImageName = "Soldier_Pile.bmp", .Start = 0, .End = 23, .InterTime = 0.08f });
	AnimationRender->ChangeAnimation("Pile");
}

void Soldier_Pile::Update(float _DeltaTime)
{
}
void Soldier_Pile::Render(float _DeltaTime)
{

}