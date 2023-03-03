#include "AmmoBaron.h"

#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineResources.h>
#include <GameEngineCore/GameEngineCollision.h>
#include <GameEngineCore/GameEngineRender.h>
#include <GameEngineCore/GameEngineLevel.h>

#include "ContentsEnum.h"
#include "Impact.h"
#include "Player.h"
#include "DamageText.h"

AmmoBaron::AmmoBaron() 
{
}

AmmoBaron::~AmmoBaron() 
{
}

void AmmoBaron::Start()
{
	RenderSet();
	CollisionSet();

	AnimationRender->ChangeAnimation("Idle");
}

void AmmoBaron::Update(float _DeltaTime)
{
	CollisionCheck(_DeltaTime);
	MoveCalculation(_DeltaTime);

	if (true == Blinker)
	{
		AlphaBlinker(_DeltaTime);
	}
}
void AmmoBaron::Render(float _DeltaTime)
{

}

void AmmoBaron::MoveCalculation(float _DeltaTime)
{
	if (true == IsStart)
	{
		MoveDir += float4::Down * 1500.0f * _DeltaTime;
	}

	NextPos = GetPos() + MoveDir * _DeltaTime;
	if (RGB(0, 248, 0) == ColMap->GetPixelColor(NextPos, RGB(0, 0, 0)))
	{
		MoveDir.y = 0.0f;
	}

	UpdateState(_DeltaTime);

	SetMove(MoveDir * _DeltaTime);
}

void AmmoBaron::CollisionCheck(float _DeltaTime)
{
	HitTime += _DeltaTime;

	if (0.2f <= HitTime && true == IsStruggle)
	{
		Hitonoff = true;
		BodyCollision->On();
	}

	if (nullptr != BodyCollision)
	{
		if (true == Hitonoff)
		{
			if (true == BodyCollision->Collision({ .TargetGroup = static_cast<int>(CollisionOrder::PlayerAttack), .TargetColType = CT_Rect, .ThisColType = CT_Rect }))
			{
				BGMPlayer = GameEngineResources::GetInst().SoundPlayToControl("Strike_enemy.mp3");
				BGMPlayer.Volume(0.075f);
				BGMPlayer.LoopCount(1);

				Hitonoff = false;
				HitTime = 0.0f;
				BodyCollision->Off();

				CreateImpact();
				CreateText();
				Blinker = true;
				BaronHP -= Player::MainPlayer->GetPlayerDamage();
			}
		}
	}
}

void AmmoBaron::CreateImpact()
{
	Impact* NewImpact = nullptr;
	float4 ImpactPos = GetPos() + (float4::Up * 20) + (float4::Left * 10);

	NewImpact = GetLevel()->CreateActor<Impact>();
	NewImpact->SetPos(ImpactPos);
}

void AmmoBaron::AlphaBlinker(float _DeltaTime)
{
	BlinkTime += _DeltaTime;

	if (true == Blinker)
	{
		if (0.15f <= BlinkTime)
		{
			BlinkTime = 0.0f;
			Blinker = false;
			AnimationRender->SetAlpha(255);
		}
		if (0.10f <= BlinkTime && true == Blinker)
		{
			AnimationRender->SetAlpha(120);
		}
		else if (0.05f <= BlinkTime && true == Blinker)
		{
			AnimationRender->SetAlpha(180);
		}
		else if (0.05f >= BlinkTime && true == Blinker)
		{
			AnimationRender->SetAlpha(240);
		}
	}
}

void AmmoBaron::RenderSet()
{
	AnimationRender = CreateRender(RenderOrder::Monster);
	AnimationRender->SetScale({ 400, 400 });
	AnimationRender->Off();

	AnimationRender->CreateAnimation({ .AnimationName = "Idle",  .ImageName = "AmmoBaron_L.bmp", .Start = 0, .End = 9, .InterTime = 0.08f });
	AnimationRender->CreateAnimation({ .AnimationName = "Run",  .ImageName = "AmmoBaron_R.bmp", .Start = 10, .End = 13, .InterTime = 0.08f });
	AnimationRender->CreateAnimation({ .AnimationName = "Move",  .ImageName = "AmmoBaron_R.bmp", .Start = 14, .End = 21, .InterTime = 0.08f });
	AnimationRender->CreateAnimation({ .AnimationName = "Jump_R",  .ImageName = "AmmoBaron_R.bmp", .Start = 22, .End = 23, .InterTime = 0.08f });
	AnimationRender->CreateAnimation({ .AnimationName = "Jump_L",  .ImageName = "AmmoBaron_L.bmp", .Start = 22, .End = 23, .InterTime = 0.08f });
	AnimationRender->CreateAnimation({ .AnimationName = "Fly",  .ImageName = "AmmoBaron_L.bmp", .Start = 24, .End = 29, .InterTime = 0.08f });
	AnimationRender->CreateAnimation({ .AnimationName = "Down",  .ImageName = "AmmoBaron_L.bmp", .Start = 30, .End = 35, .InterTime = 0.08f });
	AnimationRender->CreateAnimation({ .AnimationName = "Downing",  .ImageName = "AmmoBaron_L.bmp", .Start = 35, .End = 35, .InterTime = 0.08f, .Loop = false });
	AnimationRender->CreateAnimation({ .AnimationName = "Standup",  .ImageName = "AmmoBaron_L.bmp", .Start = 37, .End = 43, .InterTime = 0.08f });
	AnimationRender->CreateAnimation({ .AnimationName = "Struggle",  .ImageName = "AmmoBaron_L.bmp", .Start = 44, .End = 51, .InterTime = 0.08f });
	AnimationRender->CreateAnimation({ .AnimationName = "Dustoff",  .ImageName = "AmmoBaron_L.bmp", .Start = 59, .End = 71, .InterTime = 0.08f });
}

void AmmoBaron::CollisionSet()
{
	BodyCollision = CreateCollision(CollisionOrder::Trigger);
	BodyCollision->SetDebugRenderType(CT_Rect);
	BodyCollision->SetScale({ 50, 40 });
	BodyCollision->SetPosition({ 0, -10 });
	BodyCollision->Off();
}

void AmmoBaron::CreateText()
{
	DamageText* NewT = nullptr;
	float4 NewTPos = float4::Zero;

	NewT = GetLevel()->CreateActor<DamageText>();
	NewT->SetPos(GetPos() + float4::Up * 110 + float4::Left * 40);
}