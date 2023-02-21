#include "Impact.h"

#include <GameEngineCore/GameEngineResources.h>
#include <GameEngineCore/GameEngineCollision.h>
#include <GameEngineCore/GameEngineRender.h>
#include <GameEngineCore/GameEngineLevel.h>

#include "ContentsEnum.h"

Impact::Impact() 
{
}

Impact::~Impact() 
{
}

void Impact::Start()
{
	// Animation
	AnimationRender = CreateRender(RenderOrder::Effect);
	AnimationRender->SetScale({ 300, 300 });
	AnimationRender->CreateAnimation({ .AnimationName = "Impact",  .ImageName = "Impact.bmp", .Start = 0, .End = 5, .InterTime = 0.035f });
	AnimationRender->ChangeAnimation("Impact");
}

void Impact::Update(float _DeltaTime)
{
	if (true == AnimationRender->IsAnimationEnd())
	{
		GameEngineActor* Act = AnimationRender->GetActor();
		Act->Death();
	}
}

void Impact::Render(float _DeltaTime)
{

}