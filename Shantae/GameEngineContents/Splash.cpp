#include "Splash.h"

#include <GameEngineCore/GameEngineResources.h>
#include <GameEngineCore/GameEngineCollision.h>
#include <GameEngineCore/GameEngineRender.h>
#include <GameEngineCore/GameEngineLevel.h>

#include "ContentsEnum.h"

Splash::Splash() 
{
}

Splash::~Splash() 
{
}

void Splash::Start()
{
	// Animation
	AnimationRender = CreateRender(RenderOrder::Effect);
	AnimationRender->SetScale({ 300, 300 });
	AnimationRender->CreateAnimation({ .AnimationName = "Splash",  .ImageName = "Splash.bmp", .Start = 0, .End = 8, .InterTime = 0.08f });
	AnimationRender->ChangeAnimation("Splash");
}

void Splash::Update(float _DeltaTime)
{
	if (true == AnimationRender->IsAnimationEnd())
	{
		GameEngineActor* Act = AnimationRender->GetActor();
		Act->Death();
	}
}

void Splash::Render(float _DeltaTime)
{

}