#include "SmallPoof.h"

#include <GameEngineCore/GameEngineResources.h>
#include <GameEngineCore/GameEngineCollision.h>
#include <GameEngineCore/GameEngineRender.h>
#include <GameEngineCore/GameEngineLevel.h>

#include "ContentsEnum.h"

SmallPoof::SmallPoof() 
{
}

SmallPoof::~SmallPoof() 
{
}

void SmallPoof::Start()
{
	// Animation
	AnimationRender = CreateRender(RenderOrder::Effect);
	AnimationRender->SetScale({ 400, 400 });
	AnimationRender->CreateAnimation({ .AnimationName = "Poof",  .ImageName = "SmallPoof.bmp", .Start = 0, .End = 5, .InterTime = 0.08f });
	AnimationRender->ChangeAnimation("Poof");
}

void SmallPoof::Update(float _DeltaTime)
{
	if (true == AnimationRender->IsAnimationEnd())
	{
		GameEngineActor* Act = AnimationRender->GetActor();
		Act->Death();
	}
}

void SmallPoof::Render(float _DeltaTime)
{

}
