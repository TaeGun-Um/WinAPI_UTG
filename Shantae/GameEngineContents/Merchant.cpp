#include "Merchant.h"

#include <GameEngineCore/GameEngineRender.h>
#include <GameEngineCore/GameEngineCollision.h>

#include "ContentsEnum.h"

Merchant::Merchant() 
{
}

Merchant::~Merchant() 
{
}

void Merchant::Start()
{
	AnimationRender = CreateRender(RenderOrder::Monster);
	AnimationRender->SetScale({ 400, 400 });

	AnimationRender->CreateAnimation({ .AnimationName = "Idle",  .ImageName = "Merchant.bmp", .Start = 0, .End = 4, .InterTime = 0.1f });
	AnimationRender->CreateAnimation({ .AnimationName = "Run",  .ImageName = "Merchant.bmp", .Start = 5, .End = 9, .InterTime = 0.1f });

	BodyCollision = CreateCollision(CollisionOrder::Trigger);
	BodyCollision->SetDebugRenderType(CT_Rect);
	BodyCollision->SetScale({ 120, 100 });
	BodyCollision->SetPosition({ 0, -50 });

	AnimationRender->ChangeAnimation("Idle");
}
void Merchant::Update(float _DeltaTime)
{
	if (1 == CurrentPosCount)
	{
		CurrentPosCount = 0;
		CurrentPos = GetPos();
	}

	if (true == IsRun)
	{
		Run(_DeltaTime);
	}

}
void Merchant::Render(float _DeltaTime)
{

}

void Merchant::CollisionCheck()
{
	if (nullptr != BodyCollision)
	{
		if (true == BodyCollision->Collision({ .TargetGroup = static_cast<int>(CollisionOrder::Player), .TargetColType = CT_Rect, .ThisColType = CT_Rect }))
		{
			int a = 0;
		}
	}
}

void Merchant::Run(float _DeltaTime)
{
	AnimationRender->ChangeAnimation("Run");
	SetMove(float4::Left * 400.0f * _DeltaTime);
}

void Merchant::DirectCheckForKill()
{
	float4 Pos = CurrentPos + (float4::Down * 1500);

	if (GetPos().y >= Pos.y)
	{
		Kill();
	}
}

void Merchant::Kill()
{
	GameEngineActor* ColActor = AnimationRender->GetActor();
	ColActor->Off();
	ColActor->Death();
}