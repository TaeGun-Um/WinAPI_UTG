#include "Soldier_Black.h"

#include <GameEngineBase/GameEngineRandom.h>
#include <GameEngineBase/GameEngineDebug.h>
#include <GameEngineCore/GameEngineResources.h>
#include <GameEngineCore/GameEngineCollision.h>
#include <GameEngineCore/GameEngineRender.h>
#include <GameEngineCore/GameEngineLevel.h>

#include "Soldier_Bullet.h"
#include "Public_Boom.h"
#include "Player.h"
#include "DamageText.h"

#include "ContentsEnum.h"

#include "Gem.h"
#include "Heart.h"

Soldier_Black::Soldier_Black()
{
}

Soldier_Black::~Soldier_Black()
{
}

void Soldier_Black::Start()
{
	// Animation
	RenderSet();

	// Collision
	CollisionSet();

	// state
	ChangeState(Soldier_BlackState::IDLE);
}

void Soldier_Black::Update(float _DeltaTime)
{
	CharacterDirectSetting(_DeltaTime);
	CollisionCheck(_DeltaTime);
	MoveCalculation(_DeltaTime);

	if (true == Blinker)
	{
		AlphaBlinker(_DeltaTime);
	}
}

void Soldier_Black::Render(float _DeltaTime)
{

}

void Soldier_Black::CharacterDirectSetting(float _DeltaTime)
{
	float interval = Player::MainPlayer->GetPos().x - GetPos().x;
	
	if (true == trace)
	{
		if (0.0f >= interval)
		{
			MoveDirect = true;
		}
		else
		{
			MoveDirect = false;
		}
	}
}

std::string Soldier_Black::DirCheck(const std::string_view& _AnimationName)
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

// ?߷?, ????, ??Ÿ??
void Soldier_Black::MoveCalculation(float _DeltaTime)
{
	///////////////////////////////////////////////////  ?߷?  ///////////////////////////////////////////////////

	if (true == IsGravity && MoveDir.y <= 1800)
	{
		MoveDir += float4::Down * 1500.0f * _DeltaTime;
	}

	/////////////////////////////////////////////////// ??Ÿ?? ///////////////////////////////////////////////////

	if (nullptr == ColMap)
	{
		MsgAssert("?浹?? ?? ?̹????? ?????ϴ?.");
	}

	//////// RGB(0, 248, 0) ////////
	// ??
	NextPos = GetPos() + MoveDir * _DeltaTime;
	if (RGB(0, 248, 0) == ColMap->GetPixelColor(NextPos, RGB(0, 0, 0)))
	{
		if (false == HitAction)
		{
			MoveDir.y = 0.0f;
		}
	}

	//////// RGB(74, 65, 42) ////////
	// ??
	if (RGB(74, 65, 42) == ColMap->GetPixelColor(NextPos, RGB(0, 0, 0)))
	{
		if (false == HitAction)
		{
			MoveDir.y = 0.0f;
		}
	}

	/////////////////////////////////////////////////// ??Ÿ ???? ///////////////////////////////////////////////////

	//////// ???? ??ġ ////////

	UpdateState(_DeltaTime);

	SetMove(MoveDir * _DeltaTime);
}

void Soldier_Black::CollisionCheck(float _DeltaTime)
{
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

	HitTime2 += _DeltaTime;

	if (0.2f <= HitTime2 && false == HitAction)
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
				HitTime2 = 0.0f;
				BodyCollision->Off();
				Blinker = true;
				HP -= Player::MainPlayer->GetPlayerDamage();

				CreateText();

				if (0 >= HP)
				{
					HitAction = true;
				}
			}
		}
	}

	if (true == IsDeath)
	{
		Kill();
	}
}

void Soldier_Black::Kill()
{
	GameEngineActor* ColActor = BodyCollision->GetActor();
	ColActor->Off();

	Explosion();
	CreateItem();

	ColActor->Death();
}


void Soldier_Black::Shoot()
{
	Soldier_Bullet* NewBullet = nullptr;
	float4 BulletPos = float4::Zero;

	if ("_L" == DirString)
	{
		BulletPos = GetPos() + (float4::Up * 75) + (float4::Left * 50);
	}
	else
	{
		BulletPos = GetPos() + (float4::Up * 75) + (float4::Right * 85);
	}
	
	NewBullet = GetLevel()->CreateActor<Soldier_Bullet>();
	NewBullet->SetColMap(ColMap);
	NewBullet->SetPos(BulletPos);
	NewBullet->SetOwnerPos(GetPos());
	NewBullet->SetDir(DirString);
}

void Soldier_Black::Explosion()
{
	Public_Boom* Ex = nullptr;
	float4 ExPos = float4::Zero;
	ExPos = GetPos() + (float4::Up * 60);

	Ex = GetLevel()->CreateActor<Public_Boom>();
	Ex->SetPos(ExPos);
	Ex->SetExPlus(1);
}

void Soldier_Black::AlphaBlinker(float _DeltaTime)
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

void Soldier_Black::RenderSet()
{
	AnimationRender = CreateRender(RenderOrder::Monster);
	AnimationRender->SetScale({ 400, 400 });

	// Right
	AnimationRender->CreateAnimation({ .AnimationName = "Idle_R",  .ImageName = "Soldier_Black_R.bmp", .Start = 0, .End = 5, .InterTime = 0.08f });
	AnimationRender->CreateAnimation({ .AnimationName = "Shoot_R",  .ImageName = "Soldier_Black_R.bmp", .Start = 6, .End = 7, .InterTime = 0.1f });
	AnimationRender->CreateAnimation({ .AnimationName = "Reload_R",  .ImageName = "Soldier_Black_R.bmp", .Start = 8, .End = 21, .InterTime = 0.08f });
	AnimationRender->CreateAnimation({ .AnimationName = "Hit_R",  .ImageName = "Soldier_Black_R.bmp", .Start = 22, .End = 22, .InterTime = 0.5f, .Loop = false });

	// Left
	AnimationRender->CreateAnimation({ .AnimationName = "Idle_L",  .ImageName = "Soldier_Black_L.bmp", .Start = 0, .End = 5, .InterTime = 0.08f });
	AnimationRender->CreateAnimation({ .AnimationName = "Shoot_L",  .ImageName = "Soldier_Black_L.bmp", .Start = 6, .End = 7, .InterTime = 0.1f });
	AnimationRender->CreateAnimation({ .AnimationName = "Reload_L",  .ImageName = "Soldier_Black_L.bmp", .Start = 8, .End = 21, .InterTime = 0.08f });
	AnimationRender->CreateAnimation({ .AnimationName = "Hit_L",  .ImageName = "Soldier_Black_L.bmp", .Start = 22, .End = 22, .InterTime = 0.5f, .Loop = false });
}
void Soldier_Black::CollisionSet()
{
	BodyCollision = CreateCollision(CollisionOrder::Monster);
	BodyCollision->SetDebugRenderType(CT_Rect);
	BodyCollision->SetScale({ 130, 150 });
	BodyCollision->SetPosition({ 30, -75 });

	SensorCollision = CreateCollision(CollisionOrder::Trigger);
	SensorCollision->SetDebugRenderType(CT_Rect);
	SensorCollision->SetScale({ 1000, 500 });
	SensorCollision->SetPosition({ 0, -150 });
}

void Soldier_Black::CreateItem()
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

void Soldier_Black::CreateText()
{
	DamageText* NewT = nullptr;
	float4 NewTPos = float4::Zero;

	NewT = GetLevel()->CreateActor<DamageText>();
	NewT->SetPos(GetPos() + float4::Up * 160 + float4::Left * 20);
}