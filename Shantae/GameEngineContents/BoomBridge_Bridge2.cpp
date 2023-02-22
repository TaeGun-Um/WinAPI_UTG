#include "BoomBridge_Bridge2.h"

#include <GameEngineCore/GameEngineResources.h>
#include <GameEngineCore/GameEngineCollision.h>
#include <GameEngineCore/GameEngineRender.h>
#include <GameEngineCore/GameEngineLevel.h>

#include "Public_Boom.h"
#include "ContentsEnum.h"

BoomBridge_Bridge2::BoomBridge_Bridge2()
{
}

BoomBridge_Bridge2::~BoomBridge_Bridge2()
{
}

void BoomBridge_Bridge2::Start()
{
	// Animation
	RenderSet();

	// Collision
	CollisionSet();
}

void BoomBridge_Bridge2::Update(float _DeltaTime)
{
	if (1 == CurrentPosCount)
	{
		CurrentPosCount = 0;
		CurrentPos = GetPos();
	}

	if (7.6f <= AccTime)
	{
		MoveStart = true;
	}

	if (true == MoveStart)
	{
		BodyCollision->Off();
		MoveCalculation(_DeltaTime);
		DirectCheckForKill();
	}
}
void BoomBridge_Bridge2::Render(float _DeltaTime)
{
}

void BoomBridge_Bridge2::MoveCalculation(float _DeltaTime)
{
	if (true == IsJump)
	{
		IsJump = false;
		MoveDir.y -= 100.0f;
	}

	MoveDir += float4::Down * 2000.0f * _DeltaTime;

	SetMove(float4::Right * 180.0f * _DeltaTime);

	SetMove(MoveDir * _DeltaTime);
}

void BoomBridge_Bridge2::DirectCheckForKill()
{
	float4 Pos = CurrentPos + (float4::Down * 1500);

	if (GetPos().y >= Pos.y)
	{
		Kill();
	}
}

void BoomBridge_Bridge2::Kill()
{
	GameEngineActor* ColActor = BodyCollision->GetActor();
	ColActor->Off();
	ColActor->Death();
}

void BoomBridge_Bridge2::RenderSet()
{
	AnimationRender = CreateRender("BoomBridge_Bridge2.Bmp", RenderOrder::Map);
	AnimationRender->SetScale({ 350, 50 });
}

void BoomBridge_Bridge2::CollisionSet()
{
	BodyCollision = CreateCollision(CollisionOrder::Ground);
	BodyCollision->SetDebugRenderType(CT_Rect);
	BodyCollision->SetScale({ 350, 20 });
	BodyCollision->SetPosition({ 0, -15 });
}