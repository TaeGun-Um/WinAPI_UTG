#include "Player.h"

#include <GameEngineBase/GameEngineString.h>
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/GameEngineCore.h>
#include <GameEngineCore/GameEngineResources.h>
#include <GameEngineCore/GameEngineRender.h>
#include <GameEngineCore/GameEngineCollision.h>

#include "Pistol_Bullet.h"
#include "ContentsEnum.h"

Player* Player::MainPlayer = nullptr;

Player::Player()
{
}

Player::~Player()
{
}

void Player::Start()
{
	MainPlayer = this;

	// NumberRender

	// Animation
	RenderSet();

	// Collision
	CollisionSet();

	// Text(예시; 0206 추가)
	GameEngineRender* Render = CreateRender(RenderOrder::UI);
	Render->SetText("1234");

	// Start Animation
	ChangeState(PlayerState::IDLE);
}

bool FreeMove = false;

void Player::Update(float _DeltaTime)
{
	OverlapTime += _DeltaTime;

	if (true == IsAnimationStart)
	{
		LevelChangeAnimation(_DeltaTime);
		return;
	}

	if (true == IsStartAnimationStart)
	{
		LevelStartAnimation(_DeltaTime);
	}

	if (true == FreeMoveState(_DeltaTime))
	{
		return;
	}
	if (true == GameEngineInput::IsPress("PositionText"))
	{
		if (OverlapTime > 0.5f)
		{
			PosText = !PosText;
			OverlapTime = 0.0;
		}
	}
	if (true == GameEngineInput::IsDown("DebugRenderSwitch"))
	{
		if (OverlapTime > 0.5f)
		{
			GetLevel()->DebugRenderSwitch();
			OverlapTime = 0.0;
		}
	}
	
	// Player_State, Physics, Collision
	CollisionCheck(_DeltaTime);
	MoveCalculation(_DeltaTime);
}

void Player::Render(float _DeltaTime)
{
	if (true == PosText)
	{
		PositionText();
	}
}

bool Player::LevelChangeAnimation(float _DeltaTime)
{
	AnimationTime += _DeltaTime;

	SetMove(float4::Right * MoveSpeed * _DeltaTime);

	if (AnimationEndTime <= AnimationTime)
	{
		AnimationTime = 0.0f;
		return true;
	}

	return false;
}

void Player::LevelStartAnimation(float _DeltaTime)
{
	AnimationRender->ChangeAnimation("Run_R");

	AnimationTime += _DeltaTime;

	SetMove(float4::Right * MoveSpeed * _DeltaTime);
}

void Player::PositionText()
{
	std::string PlayerText = "PlayerPosition : ";
	PlayerText += GetPos().ToString();

	std::string CameraMouseText = "CameraPosition : ";
	CameraMouseText += GetLevel()->GetCameraPos().ToString();

	GameEngineLevel::DebugTextPush(PlayerText);
	GameEngineLevel::DebugTextPush(CameraMouseText);
}

bool Player::FreeMoveState(float _DeltaTime)
{
	if (true == GameEngineInput::IsDown("FreeMoveOn"))
	{
		FreeMove = true;
	}
	if (true == GameEngineInput::IsDown("FreeMoveOff"))
	{
		FreeMove = false;
	}

	if (true == FreeMove)
	{
		if (true == GameEngineInput::IsPress("UpMove"))
		{
			SetMove(float4::Up * 1000.0f * _DeltaTime);
			GetLevel()->SetCameraMove(float4::Up * 1000.0f * _DeltaTime);
		}
		if (true == GameEngineInput::IsPress("DownMove"))
		{
			SetMove(float4::Down * 1000.0f * _DeltaTime);
			GetLevel()->SetCameraMove(float4::Down * 1000.0f * _DeltaTime);
		}
		if (true == GameEngineInput::IsPress("LeftMove"))
		{
			SetMove(float4::Left * 1000.0f * _DeltaTime);
			GetLevel()->SetCameraMove(float4::Left * 1000.0f * _DeltaTime);
		}
		if (true == GameEngineInput::IsPress("RightMove"))
		{
			SetMove(float4::Right * 1000.0f * _DeltaTime);
			GetLevel()->SetCameraMove(float4::Right * 1000.0f * _DeltaTime);
		}
	}

	if (true == FreeMove)
	{
		return true;
	}

	return false;
}

std::string Player::DirCheck(const std::string_view& _AnimationName)
{
	std::string PrevDirString = DirString;
	AnimationRender->ChangeAnimation(_AnimationName.data() + DirString);

	if (GameEngineInput::IsPress("LeftMove") && false == HitAction)
	{
		DirString = "_L";
	}
	else if (GameEngineInput::IsPress("RightMove") && false == HitAction)
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
void Player::MoveCalculation(float _DeltaTime)
{
	///////////////////////////////////////////////////  중력  ///////////////////////////////////////////////////

	if (true == IsGravity && MoveDir.y <= 2000)
	{
		if (true == IsGravityPlus)
		{
			MoveDir += float4::Down * 400.0f;
		}
		if (false == IsGravityPlus)
		{
			MoveDir += float4::Down * 3500.0f *_DeltaTime;
		}
	}

	///////////////////////////////////////////////////  점프  ///////////////////////////////////////////////////

	if (true == GameEngineInput::IsDown("Jump") && true == GameEngineInput::IsPress("DownMove")
		&& RGB(74, 65, 42) == ColMap->GetPixelColor(NextPos, RGB(0, 0, 0)))
	{
		IsGravityPlus = false;
		DownJump = true;
	}

	if (0.05f <= FallTime)
	{
		DownJump = false;
	}

	if (false == IsJump)
	{
		Fall = true;
	}

	/////////////////////////////////////////////////// 맵타일 ///////////////////////////////////////////////////
	
	if (nullptr == ColMap)
	{
		MsgAssert("충돌용 맵 이미지가 없습니다.");
	}

	WallCheck(600.0f);

	// 땅
	NextPos = GetPos() + MoveDir * _DeltaTime;
	if (RGB(0, 248, 0) == ColMap->GetPixelColor(NextPos, RGB(0, 0, 0)))
	{
		IsJump = false;
		Fall = false;
		MoveDir.y = 0.0f;
	}

	if (RGB(74, 65, 42) != ColMap->GetPixelColor(NextPos, RGB(0, 0, 0))
		|| RGB(0, 248, 0) != ColMap->GetPixelColor(NextPos, RGB(0, 0, 0)))
	{
		FallTime += _DeltaTime;
	}

	if (RGB(74, 65, 42) == ColMap->GetPixelColor(NextPos, RGB(0, 0, 0))
		|| RGB(0, 248, 0) == ColMap->GetPixelColor(NextPos, RGB(0, 0, 0)))
	{
		FallTime = 0.0f;
	}

	if (true == CollisionGround)
	{
		IsJump = false;
		Fall = false;
		MoveDir.y = 0.0f;
	}

	if (false == CollisionGround)
	{
		FallTime += _DeltaTime;
	}

	if (true == CollisionGround)
	{
		FallTime = 0.0f;
	}

	//////// RGB(74, 65, 42) ////////
	// 밑점프, 언덕 발판
	if (true == IsJump && 1.0f <= MoveDir.y)
	{
		Pass = 1;
	}

	if (false == DownJump) // 밑점프 조건
	{
		if (RGB(74, 65, 42) == ColMap->GetPixelColor(NextPos, RGB(0, 0, 0)))
		{
			IsGravityPlus = true;

			if (1 == Pass) // 발판 조건
			{
				IsJump = false;
				Fall = false;
				MoveDir.y = 0;

				while (RGB(74, 65, 42) == ColMap->GetPixelColor(GetPos(), RGB(0, 0, 0)))
				{
					MoveDir.y -= 1.0f;
					SetMove(MoveDir);
					if (RGB(74, 65, 42) != ColMap->GetPixelColor(NextPos, RGB(0, 0, 0)))
					{
						break;
					}
				}
			}
			DownJump = false;
		}
	}

	float4 Downs = GetPos() + (float4::Down * 5);

	if (RGB(74, 65, 42) != ColMap->GetPixelColor(Downs, RGB(0, 0, 0)))
	{
		IsGravityPlus = false;
	}

	if (true == IsJump && 1.0f <= MoveDir.y)
	{
		Pass = 1;
	}

	/////////////////////////////////////////////////// 기타 조건 ///////////////////////////////////////////////////

	// 공중공격
	if (true == IsJump || true == Fall)
	{
		AirAttack = true;
	}
	else
	{
		AirAttack = false;
	}

	// Run 시간 축적
	if (RGB(74, 65, 42) == ColMap->GetPixelColor(NextPos, RGB(0, 0, 0))
		|| RGB(0, 248, 0) == ColMap->GetPixelColor(NextPos, RGB(0, 0, 0)))
	{
		if (GameEngineInput::IsPress("LeftMove") || GameEngineInput::IsPress("RightMove"))
		{
			MoveTime += _DeltaTime;
		}
	}

	//////// 최종 위치 ////////
	UpdateState(_DeltaTime);

	SetMove(MoveDir * _DeltaTime);
}

// 콜리전 충돌체크
void Player::CollisionCheck(float _DeltaTime)
{
	// BodyCollision
	// Crouch
	if (GameEngineInput::IsPress("DownMove") || true == CrouchMaintain)
	{
		BodyCollision->SetScale({ 50, 55 });
		BodyCollision->SetPosition({ 0, -27.5f });
		StandingCollision->SetScale({ 50, 55 });
		StandingCollision->SetPosition({ 0, -27.5f });
	}
	else // Normal
	{
		BodyCollision->SetScale({ 50, 90 });
		BodyCollision->SetPosition({ 0, -50 });
		StandingCollision->SetScale({ 50, 90 });
		StandingCollision->SetPosition({ 0, -45 });
	}

	// AttackCollision
	if (true == IsAttackStart)
	{
		// Right
		if (true == AttackDir)
		{
			if (true == IsAirAttack)
			{
				AttackCollision->SetPosition({ 100, -75 });
			}
			else if (true == IsCrouchAttack)
			{
				AttackCollision->SetPosition({ 100, -40 });
			}
			else if (true == IsAttack)
			{
				AttackCollision->SetPosition({ 100, -60 });
			}
		}
		else // Left
		{
			if (true == IsAirAttack)
			{
				AttackCollision->SetPosition({ -100, -75 });
			}
			else if (true == IsCrouchAttack)
			{
				AttackCollision->SetPosition({ -100, -40 });
			}
			else if (true == IsAttack)
			{
				AttackCollision->SetPosition({ -100, -60 });
			}
		}
		AttackCollision->On();
	}

	
	if (false == IsAttackStart)
	{
		AttackCollision->Off();
	}

	// Contact with Monster
	if (nullptr != BodyCollision)
	{
		if (true == BodyCollision->Collision({ .TargetGroup = static_cast<int>(CollisionOrder::Monster), .TargetColType = CT_Rect, .ThisColType = CT_Rect }))
		{
			HP -= 1;
			HitAction = true;
			HitTimeCheck = true;
			BodyCollision->Off();
		}
	}

	// Attack for Monster
	if (nullptr != BodyCollision)
	{
		if (true == BodyCollision->Collision({ .TargetGroup = static_cast<int>(CollisionOrder::MonsterAttack), .TargetColType = CT_Rect, .ThisColType = CT_Rect }))
		{
			HP -= 1;
			HitAction = true;
			HitTimeCheck = true;
			BodyCollision->Off();
		}
	}

	if (nullptr != StandingCollision)
	{
		CollisionGround = false;

		if (true == StandingCollision->Collision({ .TargetGroup = static_cast<int>(CollisionOrder::Ground), .TargetColType = CT_Rect, .ThisColType = CT_Rect }))
		{
			CollisionGround = true;
		}
	}

	if (true == HitTimeCheck && false == IsJumpHit)
	{
		HitTime += _DeltaTime;
	}
	if (2.0f <= HitTime)
	{
		HitTime = 0.0f;
		HitTimeCheck = false;
		BodyCollision->On();
	}
}

void Player::Shoot()
{
	Pistol_Bullet* NewBullet = nullptr;
	float4 BulletPos = float4::Zero;
	BulletPos = GetPos() + (float4::Up * 50);

	NewBullet = GetLevel()->CreateActor<Pistol_Bullet>();
	NewBullet->SetColMap(ColMap);
	NewBullet->SetPos(BulletPos);
	NewBullet->SetOwnerPos(GetPos());
	NewBullet->SetDir(DirString);
}

void Player::Kill()
{
	GameEngineActor* ColActor = BodyCollision->GetActor();
	ColActor->Off();
	ColActor->Death();
}

void Player::WallCheck(float _Speed)
{
	// 좌우
	ForwardPosR_Low = GetPos() + (float4::Up * 5) + (float4::Right * 30);
	ForwardPosL_Low = GetPos() + (float4::Up * 5) + (float4::Left * 30);
	ForwardPosR_High = GetPos() + (float4::Up * 100) + (float4::Right * 30);
	ForwardPosL_High = GetPos() + (float4::Up * 100) + (float4::Left * 30);

	// 위
	UpPos = GetPos() + (float4::Up * 100);
	CrouchUpPos_R = GetPos() + (float4::Up * 100) + (float4::Right * 29);
	CrouchUpPos_L = GetPos() + (float4::Up * 100) + (float4::Left * 29);

	if (RGB(0, 248, 0) == ColMap->GetPixelColor(ForwardPosR_Low, RGB(0, 0, 0)))
	{
		MoveSpeed = 0.0f;
		CrouchSpeed = 0.0f;

		if (GameEngineInput::IsPress("LeftMove"))
		{
			MoveSpeed = _Speed;
			CrouchSpeed = 200.0f;
		}
	}
	else if (RGB(0, 248, 0) == ColMap->GetPixelColor(ForwardPosR_High, RGB(0, 0, 0)) && false == IsCrouch)
	{
		MoveSpeed = 0.0f;

		if (GameEngineInput::IsPress("LeftMove"))
		{
			MoveSpeed = _Speed;
		}
	}
	else if (RGB(0, 248, 0) == ColMap->GetPixelColor(ForwardPosL_Low, RGB(0, 0, 0)))
	{
		MoveSpeed = 0.0f;
		CrouchSpeed = 0.0f;

		if (GameEngineInput::IsPress("RightMove"))
		{
			MoveSpeed = _Speed;
			CrouchSpeed = 200.0f;
		}
	}
	else if (RGB(0, 248, 0) == ColMap->GetPixelColor(ForwardPosL_High, RGB(0, 0, 0)) && false == IsCrouch)
	{
		MoveSpeed = 0.0f;

		if (GameEngineInput::IsPress("RightMove"))
		{
			MoveSpeed = _Speed;
		}
	}
	else
	{
		MoveSpeed = _Speed;
		CrouchSpeed = 200.0f;
	}

	// 위

	if (false == IsCrouch)
	{
		CrouchMaintain = false;
		if (RGB(0, 248, 0) == ColMap->GetPixelColor(UpPos, RGB(0, 0, 0)))
		{
			Fall = true;
			MoveDir.y = 100.0f;
		}
	}
	else if (true == IsCrouch)
	{
		if (RGB(0, 248, 0) == ColMap->GetPixelColor(CrouchUpPos_R, RGB(0, 0, 0))
			|| RGB(0, 248, 0) == ColMap->GetPixelColor(CrouchUpPos_L, RGB(0, 0, 0)))
		{
			CrouchMaintain = true;
		}
		else if (RGB(0, 248, 0) != ColMap->GetPixelColor(CrouchUpPos_R, RGB(0, 0, 0))
			|| RGB(0, 248, 0) != ColMap->GetPixelColor(CrouchUpPos_L, RGB(0, 0, 0)))
		{
			CrouchMaintain = false;
		}
	}
}

void Player::RenderSet()
{
	AnimationRender = CreateRender(RenderOrder::Player);
	AnimationRender->SetScale({ 400, 400 });
	
	// 알파블랜더 AnimationRender->SetAlpha(100);

	// Right
	AnimationRender->CreateAnimation({ .AnimationName = "Idle_R",  .ImageName = "Shantae_R.bmp", .Start = 0, .End = 6, .InterTime = 0.1f });
	AnimationRender->CreateAnimation({ .AnimationName = "IdleDance_R",  .ImageName = "Shantae_R.bmp", .Start = 7, .End = 22, .InterTime = 0.07f });
	AnimationRender->CreateAnimation({ .AnimationName = "IdleRest1_R",  .ImageName = "Shantae_R.bmp", .Start = 23, .End = 46, .InterTime = 0.1f });
	AnimationRender->CreateAnimation({ .AnimationName = "IdleRest2_R",  .ImageName = "Shantae_R.bmp", .Start = 47, .End = 63, .InterTime = 0.1f });
	AnimationRender->CreateAnimation({ .AnimationName = "Run_R",  .ImageName = "Shantae_R.bmp", .Start = 80, .End = 95, .InterTime = 0.03f });
	AnimationRender->CreateAnimation({ .AnimationName = "RunStop_R",  .ImageName = "Shantae_R.bmp", .Start = 96, .End = 106, .InterTime = 0.05f });
	AnimationRender->CreateAnimation({ .AnimationName = "Attack_R",  .ImageName = "Shantae_R.bmp", .Start = 188, .End = 194, .InterTime = 0.04f });
	AnimationRender->CreateAnimation({ .AnimationName = "Hit_R",  .ImageName = "Shantae_R.bmp", .Start = 374, .End = 382, .InterTime = 0.07f });

	AnimationRender->CreateAnimation({ .AnimationName = "Anger_R",  .ImageName = "Shantae_R.bmp", .Start = 64, .End = 71, .InterTime = 0.07f });
	AnimationRender->CreateAnimation({ .AnimationName = "GetItem_R",  .ImageName = "Shantae_R.bmp", .Start = 72, .End = 79, .InterTime = 0.07f });
	AnimationRender->CreateAnimation({ .AnimationName = "LowHP_R",  .ImageName = "Shantae_R.bmp", .Start = 361, .End = 369, .InterTime = 0.08f });
	AnimationRender->CreateAnimation({ .AnimationName = "Enter_R",  .ImageName = "Shantae_R.bmp", .Start = 204, .End = 242, .InterTime = 0.07f });
	AnimationRender->CreateAnimation({ .AnimationName = "Out_R",  .ImageName = "Shantae_R.bmp", .Start = 243, .End = 266, .InterTime = 0.07f });

	AnimationRender->CreateAnimation({ .AnimationName = "Jump_R",  .ImageName = "Shantae_R.bmp", .Start = 107, .End = 110, .InterTime = 0.07f });
	AnimationRender->CreateAnimation({ .AnimationName = "JumpHighest_R",  .ImageName = "Shantae_R.bmp", .Start = 111, .End = 115, .InterTime = 0.07f, .Loop = false });
	AnimationRender->CreateAnimation({ .AnimationName = "BeforeFall_R",  .ImageName = "Shantae_R.bmp", .Start = 113, .End = 115, .InterTime = 0.085f, .Loop = false });
	AnimationRender->CreateAnimation({ .AnimationName = "Fall_R",  .ImageName = "Shantae_R.bmp", .Start = 115, .End = 118, .InterTime = 0.07f });
	AnimationRender->CreateAnimation({ .AnimationName = "Landing_R",  .ImageName = "Shantae_R.bmp", .Start = 119, .End = 124, .InterTime = 0.07f });
	AnimationRender->CreateAnimation({ .AnimationName = "JumpAttack_R",  .ImageName = "Shantae_R.bmp", .Start = 196, .End = 202, .InterTime = 0.04f });
	AnimationRender->CreateAnimation({ .AnimationName = "JumpHit1_R",  .ImageName = "Shantae_R.bmp", .Start = 386, .End = 388, .InterTime = 0.07f });
	AnimationRender->CreateAnimation({ .AnimationName = "JumpHit2_R",  .ImageName = "Shantae_R.bmp", .Start = 388, .End = 390, .InterTime = 0.07f });
	AnimationRender->CreateAnimation({ .AnimationName = "JumpHit3_R",  .ImageName = "Shantae_R.bmp", .Start = 391, .End = 410, .InterTime = 0.06f });

	AnimationRender->CreateAnimation({ .AnimationName = "Crouching_R",  .ImageName = "Shantae_R.bmp", .Start = 125, .End = 131, .InterTime = 0.035f });
	AnimationRender->CreateAnimation({ .AnimationName = "CrouchingMaintain_R",  .ImageName = "Shantae_R.bmp", .Start = 132, .End = 141, .InterTime = 0.07f });
	AnimationRender->CreateAnimation({ .AnimationName = "CrouchingMove_R",  .ImageName = "Shantae_R.bmp", .Start = 170, .End = 179, .InterTime = 0.07f });
	AnimationRender->CreateAnimation({ .AnimationName = "CrouchingAttack_R",  .ImageName = "Shantae_R.bmp", .Start = 162, .End = 169, .InterTime = 0.04f });
	AnimationRender->CreateAnimation({ .AnimationName = "CrouchingHit_R",  .ImageName = "Shantae_R.bmp", .Start = 156, .End = 161, .InterTime = 0.07f });

	// Left
	AnimationRender->CreateAnimation({ .AnimationName = "Idle_L",  .ImageName = "Shantae_L.bmp", .Start = 0, .End = 6, .InterTime = 0.1f });
	AnimationRender->CreateAnimation({ .AnimationName = "IdleDance_L",  .ImageName = "Shantae_L.bmp", .Start = 7, .End = 22, .InterTime = 0.07f });
	AnimationRender->CreateAnimation({ .AnimationName = "IdleRest1_L",  .ImageName = "Shantae_L.bmp", .Start = 23, .End = 46, .InterTime = 0.1f });
	AnimationRender->CreateAnimation({ .AnimationName = "IdleRest2_L",  .ImageName = "Shantae_L.bmp", .Start = 47, .End = 63, .InterTime = 0.1f });
	AnimationRender->CreateAnimation({ .AnimationName = "Run_L",  .ImageName = "Shantae_L.bmp", .Start = 80, .End = 95, .InterTime = 0.03f });
	AnimationRender->CreateAnimation({ .AnimationName = "RunStop_L",  .ImageName = "Shantae_L.bmp", .Start = 96, .End = 106, .InterTime = 0.05f });
	AnimationRender->CreateAnimation({ .AnimationName = "Attack_L",  .ImageName = "Shantae_L.bmp", .Start = 188, .End = 194, .InterTime = 0.04f });
	AnimationRender->CreateAnimation({ .AnimationName = "Hit_L",  .ImageName = "Shantae_L.bmp", .Start = 374, .End = 382, .InterTime = 0.07f });

	AnimationRender->CreateAnimation({ .AnimationName = "Anger_L",  .ImageName = "Shantae_L.bmp", .Start = 64, .End = 71, .InterTime = 0.07f });
	AnimationRender->CreateAnimation({ .AnimationName = "GetItem_L",  .ImageName = "Shantae_L.bmp", .Start = 72, .End = 79, .InterTime = 0.07f });
	AnimationRender->CreateAnimation({ .AnimationName = "LowHP_L",  .ImageName = "Shantae_L.bmp", .Start = 361, .End = 369, .InterTime = 0.08f });
	AnimationRender->CreateAnimation({ .AnimationName = "Enter_L",  .ImageName = "Shantae_L.bmp", .Start = 204, .End = 242, .InterTime = 0.07f });
	AnimationRender->CreateAnimation({ .AnimationName = "Out_L",  .ImageName = "Shantae_L.bmp", .Start = 243, .End = 266, .InterTime = 0.07f });

	AnimationRender->CreateAnimation({ .AnimationName = "Jump_L",  .ImageName = "Shantae_L.bmp", .Start = 107, .End = 110, .InterTime = 0.07f });
	AnimationRender->CreateAnimation({ .AnimationName = "JumpHighest_L",  .ImageName = "Shantae_L.bmp", .Start = 111, .End = 115, .InterTime = 0.07f, .Loop = false });
	AnimationRender->CreateAnimation({ .AnimationName = "BeforeFall_L",  .ImageName = "Shantae_L.bmp", .Start = 113, .End = 115, .InterTime = 0.085f, .Loop = false });
	AnimationRender->CreateAnimation({ .AnimationName = "Fall_L",  .ImageName = "Shantae_L.bmp", .Start = 115, .End = 118, .InterTime = 0.07f });
	AnimationRender->CreateAnimation({ .AnimationName = "Landing_L",  .ImageName = "Shantae_L.bmp", .Start = 119, .End = 124, .InterTime = 0.07f });
	AnimationRender->CreateAnimation({ .AnimationName = "JumpAttack_L",  .ImageName = "Shantae_L.bmp", .Start = 196, .End = 202, .InterTime = 0.04f });
	AnimationRender->CreateAnimation({ .AnimationName = "JumpHit1_L",  .ImageName = "Shantae_L.bmp", .Start = 386, .End = 388, .InterTime = 0.07f });
	AnimationRender->CreateAnimation({ .AnimationName = "JumpHit2_L",  .ImageName = "Shantae_L.bmp", .Start = 388, .End = 390, .InterTime = 0.07f });
	AnimationRender->CreateAnimation({ .AnimationName = "JumpHit3_L",  .ImageName = "Shantae_L.bmp", .Start = 391, .End = 410, .InterTime = 0.06f });

	AnimationRender->CreateAnimation({ .AnimationName = "Crouching_L",  .ImageName = "Shantae_L.bmp", .Start = 125, .End = 131, .InterTime = 0.035f });
	AnimationRender->CreateAnimation({ .AnimationName = "CrouchingMaintain_L",  .ImageName = "Shantae_L.bmp", .Start = 132, .End = 141, .InterTime = 0.07f });
	AnimationRender->CreateAnimation({ .AnimationName = "CrouchingMove_L",  .ImageName = "Shantae_L.bmp", .Start = 170, .End = 179, .InterTime = 0.07f });
	AnimationRender->CreateAnimation({ .AnimationName = "CrouchingAttack_L",  .ImageName = "Shantae_L.bmp", .Start = 162, .End = 169, .InterTime = 0.04f });
	AnimationRender->CreateAnimation({ .AnimationName = "CrouchingHit_L",  .ImageName = "Shantae_L.bmp", .Start = 156, .End = 161, .InterTime = 0.07f });
}

void Player::CollisionSet()
{
	// Standing
	BodyCollision = CreateCollision(CollisionOrder::Player);
	BodyCollision->SetDebugRenderType(CT_Rect);
	BodyCollision->SetScale({ 50, 90 });
	BodyCollision->SetPosition({ 0, -50 });

	StandingCollision = CreateCollision(CollisionOrder::Effect);
	StandingCollision->SetDebugRenderType(CT_Rect);
	StandingCollision->SetScale({ 50, 90 });
	StandingCollision->SetPosition({ 0, -45 });

	// Attack
	AttackCollision = CreateCollision(CollisionOrder::PlayerAttack);
	AttackCollision->SetDebugRenderType(CT_Rect);
	AttackCollision->SetScale({ 160, 50 });
	AttackCollision->SetPosition({ 100, -60 });
	AttackCollision->Off();
}