#include "Building2.h"

#include <GameEngineCore/GameEngineCollision.h>
#include <GameEngineCore/GameEngineRender.h>

#include "ContentsEnum.h"
#include "Player.h"

Building2::Building2() 
{
}

Building2::~Building2() 
{
}

void Building2::Start()
{
	AnimationRender = CreateRender("Building2.Bmp", RenderOrder::BackGround);
	AnimationRender->SetRotFilter("Building2_F.bmp");
	AnimationRender->SetScale(AnimationRender->GetImage()->GetImageScale());

	// Collision
	BodyCollision = CreateCollision(CollisionOrder::Trigger);
	BodyCollision->SetDebugRenderType(CT_Rect);
	BodyCollision->SetScale({ 10, 700 });
	BodyCollision->SetPosition({ -350, 300 });
}

void Building2::Update(float _DeltaTime)
{
	if (1 == InitCount)
	{
		InitCount = 0;
		InitPos = GetPos();
	}

	CollisionCheck();

	if (true == Break)
	{
		BuildingBreak(_DeltaTime);

		BreakDelay += _DeltaTime;

		if (0.5f <= BreakDelay)
		{
			MoveCalculation(_DeltaTime);
		}

		DirectCheckForKill();
	}
}
void Building2::Render(float _DeltaTime)
{

}

void Building2::MoveCalculation(float _DeltaTime)
{
	MoveDir += float4::Down * 100.0f * _DeltaTime;

	SetMove(MoveDir * _DeltaTime);
}

void Building2::DirectCheckForKill()
{
	float4 Pos = InitPos + (float4::Down * 500);

	if (GetPos().y >= Pos.y)
	{
		Kill();
	}
}

void Building2::Kill()
{
	GameEngineActor* ColActor = AnimationRender->GetActor();
	ColActor->Off();
	ColActor->Death();
}

void Building2::BuildingBreak(float _DeltaTime)
{
	BTime += _DeltaTime;

	if (0.25f <= BTime)
	{
		B += 0.01f;

		AnimationRender->SetAngle(B);
	}
}

void Building2::CollisionCheck()
{
	if (nullptr != BodyCollision)
	{
		if (true == BodyCollision->Collision({ .TargetGroup = static_cast<int>(CollisionOrder::Player), .TargetColType = CT_Rect, .ThisColType = CT_Rect }))
		{
			BodyCollision->Off();
			Break = true;
			Player::MainPlayer->SetCameraShaking(3.0f, 3.0f);
			if (1 == SoundCount || 2 == SoundCount)
			{
				--SoundCount;
				BGMPlayer = GameEngineResources::GetInst().SoundPlayToControl("Explosion_deep.wav");
				BGMPlayer.Volume(0.1f);
				BGMPlayer.LoopCount(1);
			}
		}
	}
}