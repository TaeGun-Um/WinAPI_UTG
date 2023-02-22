#include "BoomBridge_Bridge1.h"

#include <GameEngineCore/GameEngineResources.h>
#include <GameEngineCore/GameEngineCollision.h>
#include <GameEngineCore/GameEngineRender.h>
#include <GameEngineCore/GameEngineLevel.h>

#include "Public_Boom.h"
#include "ContentsEnum.h"

BoomBridge_Bridge1::BoomBridge_Bridge1() 
{
}

BoomBridge_Bridge1::~BoomBridge_Bridge1() 
{
}

void BoomBridge_Bridge1::Start()
{
	// Animation
	RenderSet();

	// Collision
	CollisionSet();
}

void BoomBridge_Bridge1::Update(float _DeltaTime)
{
	if (1 == CurrentPosCount)
	{
		CurrentPosCount = 0;
		CurrentPos = GetPos();
	}

	if (7.6f <= AccTime)
	{
		if (1 == SoundCount)
		{
			SoundCount = 0;

			BGMPlayer = GameEngineResources::GetInst().SoundPlayToControl("Explode_bridge.wav");
			BGMPlayer.Volume(0.2f);
			BGMPlayer.LoopCount(1);
		}

		MoveStart = true;
	}

	if (true == MoveStart)
	{
		BodyCollision->Off();
		MoveCalculation(_DeltaTime);
		DirectCheckForKill();
	}
}
void BoomBridge_Bridge1::Render(float _DeltaTime)
{
}

void BoomBridge_Bridge1::MoveCalculation(float _DeltaTime)
{
	MoveDir += float4::Down * 2000.0f * _DeltaTime;

	SetMove(float4::Left * 200.0f * _DeltaTime);

	SetMove(MoveDir * _DeltaTime);
}

void BoomBridge_Bridge1::DirectCheckForKill()
{
	float4 Pos = CurrentPos + (float4::Down * 1500);

	if (GetPos().y >= Pos.y)
	{
		Kill();
	}
}

void BoomBridge_Bridge1::Kill()
{
	GameEngineActor* ColActor = BodyCollision->GetActor();
	ColActor->Off();
	ColActor->Death();
}

void BoomBridge_Bridge1::RenderSet()
{
	AnimationRender = CreateRender("BoomBridge_Bridge1.Bmp", RenderOrder::Map);
	AnimationRender->SetScale({ 350, 50 });
}

void BoomBridge_Bridge1::CollisionSet()
{
	BodyCollision = CreateCollision(CollisionOrder::Ground);
	BodyCollision->SetDebugRenderType(CT_Rect);
	BodyCollision->SetScale({ 350, 20 });
	BodyCollision->SetPosition({ 0, -15 });
}