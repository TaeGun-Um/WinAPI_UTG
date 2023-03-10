#include "Soldier_Red.h"

#include <GameEngineBase/GameEngineRandom.h>
#include <GameEngineCore/GameEngineResources.h>
#include <GameEngineCore/GameEngineCollision.h>
#include <GameEngineCore/GameEngineRender.h>
#include <GameEngineCore/GameEngineLevel.h>

#include "ContentsEnum.h"

#include "Public_Boom.h"
#include "Player.h"
#include "DamageText.h"

#include "Heart.h"
#include "Gem.h"
#include "Splash.h"

Soldier_Red::Soldier_Red()
{
}

Soldier_Red::~Soldier_Red()
{
}

void Soldier_Red::Start()
{
	// Animation
	RenderSet();

	// Collision
	CollisionSet();

	// Text(예시; 0206 추가)
	//GameEngineRender* Render = CreateRender(RenderOrder::Monster);
	//Render->SetText("1234");
}

void Soldier_Red::Update(float _DeltaTime)
{
	AmbushTime += _DeltaTime;

	if (1 == State)
	{
		SetAmbush();
	}

	CollisionCheck();
	MoveCalculation(_DeltaTime);

	if (true == Blinker)
	{
		AlphaBlinker(_DeltaTime);
	}
}
void Soldier_Red::Render(float _DeltaTime)
{

}

void Soldier_Red::SetAmbush()
{
	if (true == IsAmbush)
	{
		ChangeState(Soldier_RedState::AMBUSH);
		BodyCollision->Off();
	}
	else
	{
		ChangeState(Soldier_RedState::MOVE);
	}

	State = 0;
}

std::string Soldier_Red::DirCheck(const std::string_view& _AnimationName)
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
void Soldier_Red::MoveCalculation(float _DeltaTime)
{
	///////////////////////////////////////////////////  중력  ///////////////////////////////////////////////////

	if (true == IsGravity && MoveDir.y <= 1800)
	{
		if (true == IsGravityPlus && false == IsJump)
		{
			MoveDir += float4::Down * 510.0f;
		}
		else
		{
			MoveDir += float4::Down * 1500.0f * _DeltaTime;
		}
	}

	/////////////////////////////////////////////////// 맵타일 ///////////////////////////////////////////////////

	if (false == IsAmbush)
	{
		if (nullptr == ColMap)
		{
			MsgAssert("충돌용 맵 이미지가 없습니다.");
		}

		//////// RGB(0, 248, 0) ////////
		// 좌우 Turn
		ForwardPosL_Low = GetPos() + (float4::Up * 5) + (float4::Left * 35);
		ForwardPosL_High = GetPos() + (float4::Up * 50) + (float4::Left * 35);
		ForwardPosR_Low = GetPos() + (float4::Up * 5) + (float4::Right * 35);
		ForwardPosR_High = GetPos() + (float4::Up * 50) + (float4::Right * 35);

		if (false == IsJump)
		{
			if (RGB(0, 248, 0) == ColMap->GetPixelColor(ForwardPosL_High, RGB(0, 248, 0)) && true == MoveDirect)
			{
				MoveSpeed = 0.0f;
				MoveDirect = false;
				IsTurn = true;
			}
			else if (RGB(0, 248, 0) == ColMap->GetPixelColor(ForwardPosR_High, RGB(0, 248, 0)) && false == MoveDirect)
			{
				MoveSpeed = 0.0f;
				MoveDirect = true;
				IsTurn = true;
			}
			else
			{
				MoveSpeed = 350.0f;
				IsTurn = false;
			}
		}

		if (true == IsJump)
		{
			if (RGB(0, 248, 0) == ColMap->GetPixelColor(ForwardPosR_Low, RGB(0, 248, 0)) && false == MoveDirect)
			{
				MoveSpeed = 0.0f;
			}
			else if (RGB(0, 248, 0) == ColMap->GetPixelColor(ForwardPosR_High, RGB(0, 248, 0)) && false == MoveDirect)
			{
				MoveSpeed = 0.0f;
			}
			else if (RGB(0, 248, 0) == ColMap->GetPixelColor(ForwardPosL_Low, RGB(0, 248, 0)) && true == MoveDirect)
			{
				MoveSpeed = 0.0f;
			}
			else if (RGB(0, 248, 0) == ColMap->GetPixelColor(ForwardPosR_High, RGB(0, 248, 0)) && false == MoveDirect)
			{
				MoveSpeed = 0.0f;
			}
		}

		// 땅
		NextPos = GetPos() + MoveDir * _DeltaTime;
		if (RGB(0, 248, 0) == ColMap->GetPixelColor(NextPos, RGB(0, 0, 0)))
		{
			IsGravityPlus = false;
			if (false == HitAction || 0 != HP)
			{
				MoveDir.y = 0.0f;
			}
		}

		//////// RGB(74, 65, 42) ////////
		if (RGB(74, 65, 42) == ColMap->GetPixelColor(NextPos, RGB(0, 0, 0)))
		{
			if (false == HitAction || 0 != HP)
			{
				IsGravityPlus = true;

				MoveDir.y = 0.0f;

				while (RGB(74, 65, 42) == ColMap->GetPixelColor(GetPos(), RGB(0, 0, 0)))
				{
					MoveDir.y -= 1.0f;
					SetMove(MoveDir);
					if (RGB(74, 65, 42) != ColMap->GetPixelColor(GetPos(), RGB(0, 0, 0)))
					{
						break;
					}
				}
			}

			// 끝에서 점프 조건
			if ("_L" == DirString)
			{
				JumpP = GetPos() + (float4::Left * 2) + (float4::Down * 5);
			}
			else
			{
				JumpP = GetPos() + (float4::Right * 2) + (float4::Down * 5);
			}

			if (RGB(74, 65, 42) != ColMap->GetPixelColor(JumpP, RGB(0, 0, 0)))
			{
				IsJump = true;
			}
		}

		float4 Downs = GetPos() + (float4::Down * 5);

		if (RGB(74, 65, 42) != ColMap->GetPixelColor(Downs, RGB(0, 0, 0)))
		{
			IsGravityPlus = false;
		}
	}

	/////////////////////////////////////////////////// 기타 조건 ///////////////////////////////////////////////////

	//////// 최종 위치 ////////

	UpdateState(_DeltaTime);

	SetMove(MoveDir * _DeltaTime);
}

void Soldier_Red::CollisionCheck()
{
	if (true == MoveDirect)
	{
		BodyCollision->SetScale({ 130, 150 });
		BodyCollision->SetPosition({ 30, -75 });
	}
	else
	{
		BodyCollision->SetScale({ 130, 150 });
		BodyCollision->SetPosition({ -15, -75 });
	}

	if (nullptr != BodyCollision)
	{
		if (true == BodyCollision->Collision({ .TargetGroup = static_cast<int>(CollisionOrder::PlayerAttack), .TargetColType = CT_Rect, .ThisColType = CT_Rect }))
		{
			BGMPlayer = GameEngineResources::GetInst().SoundPlayToControl("Strike_enemy.mp3");
			BGMPlayer.Volume(0.075f);
			BGMPlayer.LoopCount(1);

			Blinker = true;

			HP -= Player::MainPlayer->GetPlayerDamage();
			
			CreateText();

			if (0 <= HP)
			{
				HitAction = true;
			}
			else if (0 < HP)
			{
				HitAction = true;
			}
		}
	}
}

void Soldier_Red::Kill()
{
	GameEngineActor* ColActor = BodyCollision->GetActor();
	ColActor->Off();

	Explosion();
	CreateItem();

	ColActor->Death();
}

void Soldier_Red::Explosion()
{
	Public_Boom* Ex = nullptr;
	float4 ExPos = float4::Zero;
	ExPos = GetPos() + (float4::Up * 60);

	Ex = GetLevel()->CreateActor<Public_Boom>();
	Ex->SetPos(ExPos);
	Ex->SetExPlus(1);
}

void Soldier_Red::AlphaBlinker(float _DeltaTime)
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

void Soldier_Red::RenderSet()
{
	AnimationRender = CreateRender(RenderOrder::Monster);
	AnimationRender->SetScale({ 400, 400 });

	// Right
	AnimationRender->CreateAnimation({ .AnimationName = "Move_R",  .ImageName = "Soldier_Red_R.bmp", .Start = 0, .End = 9, .InterTime = 0.08f });
	AnimationRender->CreateAnimation({ .AnimationName = "Turn_L",  .ImageName = "Soldier_Red_R.bmp", .Start = 13, .End = 18, .InterTime = 0.08f, .Loop = false });
	AnimationRender->CreateAnimation({ .AnimationName = "Jump_R",  .ImageName = "Soldier_Red_R.bmp", .Start = 10, .End = 12, .InterTime = 0.08f, .Loop = false });
	AnimationRender->CreateAnimation({ .AnimationName = "Fall_R",  .ImageName = "Soldier_Red_R.bmp", .Start = 12, .End = 12, .InterTime = 0.5f, .Loop = false });
	AnimationRender->CreateAnimation({ .AnimationName = "Hit_R",  .ImageName = "Soldier_Red_R.bmp", .Start = 22, .End = 22, .InterTime = 0.5f, .Loop = false });

	// Left
	AnimationRender->CreateAnimation({ .AnimationName = "Move_L",  .ImageName = "Soldier_Red_L.bmp", .Start = 0, .End = 9, .InterTime = 0.08f });
	AnimationRender->CreateAnimation({ .AnimationName = "Turn_R",  .ImageName = "Soldier_Red_L.bmp", .Start = 13, .End = 18, .InterTime = 0.08f, .Loop = false });
	AnimationRender->CreateAnimation({ .AnimationName = "Jump_L",  .ImageName = "Soldier_Red_L.bmp", .Start = 10, .End = 12, .InterTime = 0.08f, .Loop = false });
	AnimationRender->CreateAnimation({ .AnimationName = "Fall_L",  .ImageName = "Soldier_Red_L.bmp", .Start = 12, .End = 12, .InterTime = 0.5f, .Loop = false });
	AnimationRender->CreateAnimation({ .AnimationName = "Hit_L",  .ImageName = "Soldier_Red_L.bmp", .Start = 22, .End = 22, .InterTime = 0.5f, .Loop = false });

	// Public
	AnimationRender->CreateAnimation({ .AnimationName = "Ambush",  .ImageName = "Soldier_Red_L.bmp", .Start = 19, .End = 21, .InterTime = 0.5f, .Loop = false });
}

void Soldier_Red::CollisionSet() 
{
	BodyCollision = CreateCollision(CollisionOrder::Monster);
	BodyCollision->SetDebugRenderType(CT_Rect);
	BodyCollision->SetScale({ 130, 150 });
	BodyCollision->SetPosition({ 30, -75 });
}

void Soldier_Red::CreateItem()
{
	int RandC = GameEngineRandom::MainRandom.RandomInt(1, 3);

	if (1 == RandC)
	{
		Gem* Gems = nullptr;

		Gems = GetLevel()->CreateActor<Gem>();
		Gems->SetPos(GetPos());
		Gems->SetColMap(ColMap);
		Gems->SetJarSize("small");
	}
}

void Soldier_Red::CreateText()
{
	DamageText* NewT = nullptr;
	float4 NewTPos = float4::Zero;

	NewT = GetLevel()->CreateActor<DamageText>();
	NewT->SetPos(GetPos() + float4::Up * 160 + float4::Left * 20);
}

void Soldier_Red::CreateSplash()
{
	Splash* Ex = nullptr;

	Ex = GetLevel()->CreateActor<Splash>();
	Ex->SetPos(GetPos());

	BGMPlayer = GameEngineResources::GetInst().SoundPlayToControl("Splash_water.wav");
	BGMPlayer.Volume(0.1f);
	BGMPlayer.LoopCount(1);
}