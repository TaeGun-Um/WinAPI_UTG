#include "Mermaid.h"

#include <GameEngineBase/GameEngineRandom.h>
#include <GameEngineCore/GameEngineCollision.h>
#include <GameEngineCore/GameEngineRender.h>
#include <GameEngineCore/GameEngineLevel.h>

#include "Player.h"
#include "DamageText.h"

#include "ContentsEnum.h"
#include "Mermaid_Attack.h"

#include "Gem.h"
#include "Heart.h"

Mermaid::Mermaid() 
{
}

Mermaid::~Mermaid() 
{
}

void Mermaid::Start()
{
	RenderSet();

	CollisionSet();

	ChangeState(MermaidState::IDLE);
}

void Mermaid::Update(float _DeltaTime)
{
	CollisionCheck(_DeltaTime);
	MoveCalculation(_DeltaTime);

	if (true == Blinker)
	{
		AlphaBlinker(_DeltaTime);
	}
}

void Mermaid::Render(float _DeltaTime)
{

}

std::string Mermaid::DirCheck(const std::string_view& _AnimationName)
{
	std::string PrevDirString = DirString;
	AnimationRender->ChangeAnimation(_AnimationName.data() + DirString);

	if (true == MoveDirect)
	{
		DirString = "_L";
	}
	else if (false == MoveDirect)
	{
		DirString = "_R";
	}

	if (PrevDirString != DirString)
	{
		AnimationRender->ChangeAnimation(_AnimationName.data() + DirString);
	}

	return DirString;
}

// 중력, 점프, 맵타일
void Mermaid::MoveCalculation(float _DeltaTime)
{
	///////////////////////////////////////////////////  중력  ///////////////////////////////////////////////////

	if (true == IsGravity && MoveDir.y <= 1800)
	{
		MoveDir += float4::Down * 1500.0f * _DeltaTime;
	}

	/////////////////////////////////////////////////// 맵타일 ///////////////////////////////////////////////////

	if (nullptr == ColMap)
	{
		MsgAssert("충돌용 맵 이미지가 없습니다.");
	}

	//////// RGB(0, 248, 0) ////////
	// 땅
	NextPos = GetPos() + MoveDir * _DeltaTime;
	if (RGB(0, 248, 0) == ColMap->GetPixelColor(NextPos, RGB(0, 0, 0)))
	{
		MoveDir.y = 0.0f;
	}

	//////// RGB(74, 65, 42) ////////
	// 땅
	if (RGB(74, 65, 42) == ColMap->GetPixelColor(NextPos, RGB(0, 0, 0)))
	{
		MoveDir.y = 0.0f;
	}

	/////////////////////////////////////////////////// 기타 조건 ///////////////////////////////////////////////////

	//////// 최종 위치 ////////

	UpdateState(_DeltaTime);

	SetMove(MoveDir * _DeltaTime);
}

void Mermaid::CollisionCheck(float _DeltaTime)
{
	if (false == MoveDirect)
	{
		SensorCollision->SetScale({ 500, 300 });
		SensorCollision->SetPosition({ 300, -75 });
	}

	if (nullptr != SensorCollision)
	{
		if (true == SensorCollision->Collision({ .TargetGroup = static_cast<int>(CollisionOrder::Player), .TargetColType = CT_Rect, .ThisColType = CT_Rect }))
		{
			IsAttack = true;
		}
		else
		{
			IsAttack = false;
		}
	}

	if (nullptr != BodyCollision)
	{
		if (true == BodyCollision->Collision({ .TargetGroup = static_cast<int>(CollisionOrder::PlayerAttack), .TargetColType = CT_Rect, .ThisColType = CT_Rect }))
		{
			BGMPlayer = GameEngineResources::GetInst().SoundPlayToControl("Strike_enemy.mp3");
			BGMPlayer.Volume(0.075f);
			BGMPlayer.LoopCount(1);

			HitAction = true;
			BodyCollision->Off();
			Blinker = true;
			HP -= Player::MainPlayer->GetPlayerDamage();

			CreateText();

			if (0 >= HP)
			{
				IsDeath = true;
			}
		}
	}
}

void Mermaid::Kill()
{
	GameEngineActor* ColActor = BodyCollision->GetActor();
	ColActor->Off();

	CreateItem();

	ColActor->Death();
}


void Mermaid::Shoot()
{
	Mermaid_Attack* NewBullet = nullptr;
	float4 BulletPos = float4::Zero;

	if ("_L" == DirString)
	{
		BulletPos = GetPos() + (float4::Up * 50) + (float4::Left * 85);
	}
	else
	{
		BulletPos = GetPos() + (float4::Up * 50) + (float4::Right * 85);
	}

	NewBullet = GetLevel()->CreateActor<Mermaid_Attack>();
	NewBullet->SetColMap(ColMap);
	NewBullet->SetPos(BulletPos);
	NewBullet->SetOwnerPos(GetPos());
	NewBullet->SetDir(DirString);
}

void Mermaid::AlphaBlinker(float _DeltaTime)
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

void Mermaid::RenderSet()
{
	AnimationRender = CreateRender(RenderOrder::Monster);
	AnimationRender->SetScale({ 750, 750 });

	AnimationRender->CreateAnimation({ .AnimationName = "Idle_l",  .ImageName = "Mermaid_L.bmp", .Start = 0, .End = 7, .InterTime = 0.1f });
	AnimationRender->CreateAnimation({ .AnimationName = "Lure_L",  .ImageName = "Mermaid_L.bmp", .Start = 8, .End = 27, .InterTime = 0.1f });
	AnimationRender->CreateAnimation({ .AnimationName = "Ready_L",  .ImageName = "Mermaid_L.bmp", .Start = 28, .End = 36, .InterTime = 0.1f });
	AnimationRender->CreateAnimation({ .AnimationName = "Hold_L",  .ImageName = "Mermaid_L.bmp", .Start = 37, .End = 39, .InterTime = 0.1f });
	AnimationRender->CreateAnimation({ .AnimationName = "Dive_L",  .ImageName = "Mermaid_L.bmp", .Start = 40, .End = 56, .InterTime = 0.1f, .Loop = false });
	AnimationRender->CreateAnimation({ .AnimationName = "Emerge_L",  .ImageName = "Mermaid_L.bmp", .Start = 57, .End = 67, .InterTime = 0.1f, .Loop = false });
	AnimationRender->CreateAnimation({ .AnimationName = "Attack_L",  .ImageName = "Mermaid_L.bmp", .Start = 68, .End = 77, .InterTime = 0.1f });
	AnimationRender->CreateAnimation({ .AnimationName = "Hurt_L",  .ImageName = "Mermaid_L.bmp", .Start = 78, .End = 82, .InterTime = 0.1f });
	AnimationRender->CreateAnimation({ .AnimationName = "Die_L",  .ImageName = "Mermaid_L.bmp", .Start = 83, .End = 103, .InterTime = 0.1f });

	AnimationRender->CreateAnimation({ .AnimationName = "Idle_R",  .ImageName = "Mermaid_R.bmp", .Start = 0, .End = 7, .InterTime = 0.1f });
	AnimationRender->CreateAnimation({ .AnimationName = "Lure_R",  .ImageName = "Mermaid_R.bmp", .Start = 8, .End = 27, .InterTime = 0.1f });
	AnimationRender->CreateAnimation({ .AnimationName = "Ready_R",  .ImageName = "Mermaid_R.bmp", .Start = 28, .End = 36, .InterTime = 0.1f });
	AnimationRender->CreateAnimation({ .AnimationName = "Hold_R",  .ImageName = "Mermaid_R.bmp", .Start = 37, .End = 39, .InterTime = 0.1f });
	AnimationRender->CreateAnimation({ .AnimationName = "Dive_R",  .ImageName = "Mermaid_R.bmp", .Start = 40, .End = 56, .InterTime = 0.1f, .Loop = false });
	AnimationRender->CreateAnimation({ .AnimationName = "Emerge_R",  .ImageName = "Mermaid_R.bmp", .Start = 57, .End = 67, .InterTime = 0.1f, .Loop = false });
	AnimationRender->CreateAnimation({ .AnimationName = "Attack_R",  .ImageName = "Mermaid_R.bmp", .Start = 68, .End = 77, .InterTime = 0.1f });
	AnimationRender->CreateAnimation({ .AnimationName = "Hurt_R",  .ImageName = "Mermaid_R.bmp", .Start = 78, .End = 82, .InterTime = 0.1f });
	AnimationRender->CreateAnimation({ .AnimationName = "Die_R",  .ImageName = "Mermaid_R.bmp", .Start = 83, .End = 103, .InterTime = 0.1f });

}
void Mermaid::CollisionSet()
{
	BodyCollision = CreateCollision(CollisionOrder::Monster);
	BodyCollision->SetDebugRenderType(CT_Rect);
	BodyCollision->SetScale({ 100, 110 });
	BodyCollision->SetPosition({ 0, -50 });

	SensorCollision = CreateCollision(CollisionOrder::Trigger);
	SensorCollision->SetDebugRenderType(CT_Rect);
	SensorCollision->SetScale({ 500, 300 });
	SensorCollision->SetPosition({ -250, -75 });
}

void Mermaid::CreateItem()
{
	int RandC = GameEngineRandom::MainRandom.RandomInt(1, 3);

	if (1 == RandC)
	{
		Gem* Gems = nullptr;

		Gems = GetLevel()->CreateActor<Gem>();
		Gems->SetPos(GetPos());
		Gems->SetColMap(ColMap);
		Gems->SetJarSize("Large");
	}
}

void Mermaid::CreateText()
{
	DamageText* NewT = nullptr;
	float4 NewTPos = float4::Zero;

	NewT = GetLevel()->CreateActor<DamageText>();
	NewT->SetPos(GetPos() + float4::Up * 120 + float4::Left * 20);
}