#include "Mermaid_AttackBoom.h"

#include <GameEngineCore/GameEngineResources.h>
#include <GameEngineCore/GameEngineCollision.h>
#include <GameEngineCore/GameEngineRender.h>
#include <GameEngineCore/GameEngineLevel.h>

#include "ContentsEnum.h"

Mermaid_AttackBoom::Mermaid_AttackBoom()
{
}

Mermaid_AttackBoom::~Mermaid_AttackBoom()
{
}

void Mermaid_AttackBoom::Start()
{
	// Animation
	AnimationRender = CreateRender(RenderOrder::Effect);
	AnimationRender->SetScale({ 400, 400 });
	AnimationRender->CreateAnimation({ .AnimationName = "Mermaid_AttackBoom",  .ImageName = "Mermaid_AttackBoom.bmp", .Start = 0, .End = 5, .InterTime = 0.1f });
	AnimationRender->ChangeAnimation("Mermaid_AttackBoom");
}

void Mermaid_AttackBoom::Update(float _DeltaTime)
{
	if (true == AnimationRender->IsAnimationEnd())
	{
		GameEngineActor* Act = AnimationRender->GetActor();
		Act->Death();
	}
}

void Mermaid_AttackBoom::Render(float _DeltaTime)
{

}
