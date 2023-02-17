#include "Machinegun_Bulletmarks.h"

#include <GameEngineCore/GameEngineResources.h>
#include <GameEngineCore/GameEngineCollision.h>
#include <GameEngineCore/GameEngineRender.h>
#include <GameEngineCore/GameEngineLevel.h>

#include "ContentsEnum.h"

Machinegun_Bulletmarks::Machinegun_Bulletmarks() 
{
}

Machinegun_Bulletmarks::~Machinegun_Bulletmarks() 
{
}

void Machinegun_Bulletmarks::Start()
{
	AnimationRender = CreateRender(RenderOrder::Monster);
	AnimationRender->SetScale({ 400, 400 });
	AnimationRender->CreateAnimation({ .AnimationName = "Mark",  .ImageName = "Machinegun_Bulletmarks.bmp", .Start = 0, .End = 11, .InterTime = 0.05f });
	AnimationRender->ChangeAnimation("Mark");

	BodyCollision = CreateCollision(CollisionOrder::MonsterAttack);
	BodyCollision->SetDebugRenderType(CT_Rect);
	BodyCollision->SetScale({ 120, 110 });
	BodyCollision->SetPosition({ 0, -55 });
}
void Machinegun_Bulletmarks::Update(float _DeltaTime)
{
	if (true == AnimationRender->IsAnimationEnd())
	{
		GameEngineActor* Act = BodyCollision->GetActor();
		BodyCollision->Off();
		Act->Death();
	}
}

void Machinegun_Bulletmarks::Render(float _DeltaTime)
{
}
