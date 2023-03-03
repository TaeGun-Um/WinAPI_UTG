#include "Player.h"

#include <GameEngineBase/GameEngineString.h>
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/GameEngineCore.h>
#include <GameEngineCore/GameEngineResources.h>
#include <GameEngineCore/GameEngineRender.h>
#include <GameEngineCore/GameEngineCollision.h>

#include "Inventory.h"
#include "Scarecrow.h"
#include "Meat.h"
#include "Impact.h"
#include "Pistol_Bullet.h"
#include "ContentsEnum.h"
#include "PikeBallEffect.h"
#include "BubbleEffect.h"

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
	//GameEngineRender* Render = CreateRender(RenderOrder::UI);
	//Render->SetText("1234");

	// Start Animation
	ChangeState(PlayerState::IDLE);
}

void Player::Update(float _DeltaTime)
{
	int PlayerH = HP;
	int PlayerGe = PlayerGem;

	OverlapTime += _DeltaTime;

	//////////////////  디버깅  //////////////////
	// 텍스트
	if (true == GameEngineInput::IsDown("PositionText"))
	{
		if (OverlapTime > 0.5f)
		{
			PosText = !PosText;
			OverlapTime = 0.0;
		}
	}
	// 콜리전
	if (true == GameEngineInput::IsDown("DebugRenderSwitch"))
	{
		if (OverlapTime > 0.5f)
		{
			GetLevel()->DebugRenderSwitch();
			OverlapTime = 0.0;
		}
	}
	// 프리무브
	if (true == FreeMoveState(_DeltaTime))
	{
		return;
	}
	// 더미몬스터
	if (GameEngineInput::IsDown("CreateMonster"))
	{
		CreateDummy();
	}

	//////////////////  레벨이동 애니메이션  //////////////////
	// 레벨 시작 애니메이션
	if (true == IsAnimationStart)
	{
		LevelChangeAnimation(_DeltaTime);
		return;
	}
	// 포탈 이동 애니메이션
	if (true == IsRoomAnimationStart)
	{
		RoomChangeAnimation(_DeltaTime);
		return;
	}
	// 레벨 끝 애니메이션
	if (true == IsStartAnimationStart)
	{
		LevelStartAnimation(_DeltaTime);
	}

	//////////////////  콜리전 체크, 무적시간 깜빡임  //////////////////
	// 콜리전 체크
	CollisionCheck(_DeltaTime);
	
	// 깜빡임 효과
	if (true == Blinker)
	{
		AlphaBlinker(_DeltaTime);
	}
	
	//////////////////  이동 계산, 카메라  //////////////////
	// 카메라흔들림
	if (true == CameraShaking)
	{
		CameraShake(_DeltaTime);
	}
	if (true == CameraShakinghard)
	{
		CameraShakehard(_DeltaTime);
	}
	
	if (true == IsHouse)
	{
		return;
	}

	// 이동계산
	MoveCalculation(_DeltaTime);

	//////////////////  인벤토리 및 아이템 사용  //////////////////

	if (GameEngineInput::IsDown("Inventory"))
	{
		InvenOnOff = !InvenOnOff;

		if (true == InvenOnOff)
		{
			BGMPlayer = GameEngineResources::GetInst().SoundPlayToControl("Inventory_in.wav");
			BGMPlayer.Volume(0.15f);
			BGMPlayer.LoopCount(1);

			Inventory::PlayerInven->AnimationRender->On();
		}
		else
		{
			BGMPlayer = GameEngineResources::GetInst().SoundPlayToControl("Inventory_out.wav");
			BGMPlayer.Volume(0.15f);
			BGMPlayer.LoopCount(1);

			Inventory::PlayerInven->AnimationRender->Off();
		}
	}
	if (true == IsItemUse)
	{
		ItemUse(_DeltaTime);
	}
	
	if (GameEngineInput::IsDown("Select"))
	{
		Player::MainPlayer->SetItemUse("PikeBall");
	}

}

void Player::Render(float _DeltaTime)
{
	if (true == PosText)
	{
		PositionText();
	}
}

// <나열 순서>
// 1. 디버깅
// 2. 이동
// 3. 콜리전
// 4. 레벨이동 애니메이션
// 5. 추가 조작
// 6. 세팅

////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////// 1. 디버깅  //////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// 디버깅에 필요한 함수들입니다.

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

void Player::PositionText()
{
	std::string PlayerText = "PlayerPosition : ";
	
	PlayerText += GetPos().ToString();

	std::string CameraMouseText = "CameraPosition : ";
	CameraMouseText += GetLevel()->GetCameraPos().ToString();

	float4 Angle = GetLevel()->GetMousePos() - GetPos();
	float Deg = Angle.GetAnagleDeg();
	std::string AngleText = "Angle : ";
	AngleText += std::to_string(Deg);

	GameEngineLevel::DebugTextPush(AngleText);
	GameEngineLevel::DebugTextPush(PlayerText);
	GameEngineLevel::DebugTextPush(CameraMouseText);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////  2. 이동  //////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// 키 입력에 따른 플레이어블 캐릭터의 이동을 계산하고, 애니메이션을 변경합니다.

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
	//////////////////  중력  //////////////////

	if (true == IsGravity && MoveDir.y <= 2000)
	{
		if (true == IsGravityPlus)
		{
			MoveDir += float4::Down * 400.0f;
		}
		if (false == IsGravityPlus)
		{
			MoveDir += float4::Down * 3500.0f * _DeltaTime;
		}
	}

	//////////////////  점프  //////////////////

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

	////////////////// 맵타일 //////////////////

	if (nullptr == ColMap)
	{
		MsgAssert("충돌용 맵 이미지가 없습니다.");
	}

	if (false == IsStartAnimationStart)
	{
		WallCheck(600.0f);
	}

	// 땅
	NextPos = GetPos() + MoveDir * _DeltaTime;
	if (RGB(0, 248, 0) == ColMap->GetPixelColor(NextPos, RGB(0, 0, 0)))
	{
		IsJump = false;
		Fall = false;
		MoveDir.y = 0.0f;
		UpCol = 1;
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

	////////////////// 기타 조건 //////////////////

	// 공중공격
	if (true == IsJump || true == Fall)
	{
		AirAttack = true;
	}
	else
	{
		AirAttack = false;
	}

	////////////////// State //////////////////

	if (false == IsStartAnimationStart)
	{
		UpdateState(_DeltaTime);
	}
	
	SetMove(MoveDir * _DeltaTime);
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
			// 벽뚫버그 여기
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

			if (1 == UpCol && true == IsJump)
			{
				UpCol = 0;
				BGMPlayer = GameEngineResources::GetInst().SoundPlayToControl("Player_crouch.mp3");
				BGMPlayer.Volume(0.1f);
				BGMPlayer.LoopCount(1);
			}
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

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////  3. 콜리전  //////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// 플레이어블 캐릭터의 콜리전 상태와 충돌조건을 체크합니다.

void Player::CollisionCheck(float _DeltaTime)
{
	// BodyCollision
	// Crouch
	if (false == IsJump && GameEngineInput::IsPress("DownMove") || true == CrouchMaintain)
	{
		BodyCollision->SetScale({ 50, 55 });
		BodyCollision->SetPosition({ 0, -27.5f });
		StandingCollision->SetScale({ 40, 45 });
		StandingCollision->SetPosition({ 0, -22.5f });
	}
	else // Normal
	{
		BodyCollision->SetScale({ 50, 90 });
		BodyCollision->SetPosition({ 0, -45 });
		StandingCollision->SetScale({ 40, 80 });
		StandingCollision->SetPosition({ 0, -40 });
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
				ImpactPos = GetPos() + (float4::Right * 150) + (float4::Up * 70);
			}
			else if (true == IsCrouchAttack)
			{
				AttackCollision->SetPosition({ 100, -40 });
				ImpactPos = GetPos() + (float4::Right * 150) + (float4::Up * 25);
			}
			else if (true == IsAttack)
			{
				AttackCollision->SetPosition({ 100, -60 });
				ImpactPos = GetPos() + (float4::Right * 150) + (float4::Up * 55);
			}
		}
		else // Left
		{
			if (true == IsAirAttack)
			{
				AttackCollision->SetPosition({ -100, -75 });
				ImpactPos = GetPos() + (float4::Left * 150) + (float4::Up * 70);
			}
			else if (true == IsCrouchAttack)
			{
				AttackCollision->SetPosition({ -100, -40 });
				ImpactPos = GetPos() + (float4::Left * 150) + (float4::Up * 25);
			}
			else if (true == IsAttack)
			{
				AttackCollision->SetPosition({ -100, -60 });
				ImpactPos = GetPos() + (float4::Left * 150) + (float4::Up * 55);
			}
		}
		AttackCollision->On();
	}
	
	if (false == IsAttackStart)
	{
		AttackCollision->Off();
	}

	if (nullptr != BodyCollision)
	{   
		// Contact with Monster
		if (true == BodyCollision->Collision({ .TargetGroup = static_cast<int>(CollisionOrder::Monster), .TargetColType = CT_Rect, .ThisColType = CT_Rect }))
		{
			HP -= 1;
			HitAction = true;
			HitTimeCheck = true;
			BodyCollision->Off();

			Blinker = true;
		}
		// Attack for Monster
		if (true == BodyCollision->Collision({ .TargetGroup = static_cast<int>(CollisionOrder::MonsterAttack), .TargetColType = CT_Rect, .ThisColType = CT_Rect }))
		{
			HP -= 1;
			HitAction = true;
			HitTimeCheck = true;
			BodyCollision->Off();

			Blinker = true;
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

	if (0 == ImpactCreate)
	{
		ImpactRe += _DeltaTime;
		if (0.1 <= ImpactRe)
		{
			ImpactRe = 0.0f;
			ImpactCreate = 1;
		}
	}

	if (nullptr != AttackCollision)
	{
		if (true == AttackCollision->Collision({ .TargetGroup = static_cast<int>(CollisionOrder::Monster), .TargetColType = CT_Rect, .ThisColType = CT_Rect }))
		{
			if (1 == ImpactCreate)
			{
				ImpactCreate = 0;
				CreateImpact();
			}
		}
	}

	if (nullptr != AttackCollision)
	{
		if (true == AttackCollision->Collision({ .TargetGroup = static_cast<int>(CollisionOrder::Item), .TargetColType = CT_Rect, .ThisColType = CT_Rect }))
		{
			if (1 == ImpactCreate)
			{
				ImpactCreate = 0;
				CreateImpact();
			}
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
		Blinker = false;
		AnimationRender->SetAlpha(255);
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////  4. 애니메이션  ///////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// 플레이어블 캐릭터가 레벨에 진입하거나, 레벨을 이동할 때 실시하는 애니메이션입니다.

void Player::LevelStartAnimation(float _DeltaTime)
{
	AnimationRender->ChangeAnimation("Run_R");

	AnimationTime += _DeltaTime;

	SetMove(float4::Right * MoveSpeed * _DeltaTime);

	WalkSoundSet(_DeltaTime);
}

bool Player::LevelChangeAnimation(float _DeltaTime)
{
	AnimationTime += _DeltaTime;

	SetMove(float4::Right * MoveSpeed * _DeltaTime);

	if (2.0f <= AnimationTime)
	{
		AnimationTime = 0.0f;
		return true;
	}

	return false;
}

bool Player::RoomChangeAnimation(float _DeltaTime)
{
	AnimationTime += _DeltaTime;

	SetMove(float4::Left * MoveSpeed * _DeltaTime);

	if (2.0f <= AnimationTime)
	{
		AnimationTime = 0.0f;
		return true;
	}

	return false;
}

void Player::WalkSoundSet(float _DeltaTime)
{
	MoveSoundTime += _DeltaTime;

	if (0.24f <= MoveSoundTime)
	{
		if (2 == MoveSoundCount)
		{
			BGMPlayer = GameEngineResources::GetInst().SoundPlayToControl("Player_move3.wav");
			BGMPlayer.Volume(0.3f);
			BGMPlayer.LoopCount(1);

			MoveSoundTime = 0.0f;
			MoveSoundCount = 1;
		}
		else if (1 == MoveSoundCount)
		{
			BGMPlayer = GameEngineResources::GetInst().SoundPlayToControl("Player_move2.wav");
			BGMPlayer.Volume(0.3f);
			BGMPlayer.LoopCount(1);

			MoveSoundTime = 0.0f;
			MoveSoundCount = 2;
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////  5. 추가 조작  ///////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// 플레이어블 캐릭터의 추가 조작 (총알 발사, 캐릭터 사망 등)의 함수들 입니다.

void Player::SetCameraShaking(float _SetShakingTime, float _SetShakingValue)
{
	// 사용법 == player 헤더 참조 후 Player::Mainpayer->SetCameraShaking() 호출
	CameraShaking = true;
	SetShakingTime = _SetShakingTime;
	SetShakingValue = _SetShakingValue;
}

void Player::CameraShake(float _DeltaTime)
{
	float4 MCam = GetLevel()->GetCameraPos();
	float4 UpCam = MCam + (float4::Up * (SetShakingValue));
	float4 DownCam = MCam + (float4::Down * (SetShakingValue));
	float4 DownCamX2 = MCam + (float4::Down * (SetShakingValue*2));

	ShakingTime += _DeltaTime;

	if (SetShakingTime >= ShakingTime)
	{
		if (0 == ShakingCount || 1 == ShakingCount)
		{
			GetLevel()->SetCameraPos(UpCam);
			ShakingCount++;
		}
		else if (2 == ShakingCount || 3 == ShakingCount)
		{
			GetLevel()->SetCameraPos(MCam);
			ShakingCount++;
		}
		else if (4 == ShakingCount || 5 == ShakingCount)
		{
			GetLevel()->SetCameraPos(DownCam);
			ShakingCount++;
		}
		else if (6 == ShakingCount)
		{
			GetLevel()->SetCameraPos(MCam);
			ShakingCount = 0;
		}
	}

	if (SetShakingTime <= ShakingTime)
	{
		ShakingTime = 0.0f;
		CameraShaking = false;

	}

	// 복구
	if (false == CameraShaking)
	{
		if (1 == ShakingCount || 5 == ShakingCount)
		{
			GetLevel()->SetCameraPos(DownCam);
		}
		else if (2 == ShakingCount || 3 == ShakingCount || 4 == ShakingCount)
		{
			GetLevel()->SetCameraPos(DownCamX2);
		}

		ShakingCount = 0;
	}
}

void Player::SetCameraShakinghard(float _SetShakingTime, float _SetShakingValue)
{
	// 사용법 == player 헤더 참조 후 Player::Mainpayer->SetCameraShaking() 호출
	CameraShakinghard = true;
	SetShakingTime = _SetShakingTime;
	SetShakingValuehard = _SetShakingValue;
}

void Player::CameraShakehard(float _DeltaTime)
{
	float4 MCam = GetLevel()->GetCameraPos();
	float4 UpCam = MCam + (float4::Up * (SetShakingValuehard));
	float4 DownCam = MCam + (float4::Down * (SetShakingValuehard));

	ShakingTime += _DeltaTime;

	if (SetShakingTime >= ShakingTime)
	{
		if (0 == HardShakingCount)
		{
			GetLevel()->SetCameraPos(UpCam);
			HardShakingCount++;
		}
		else if (1 == HardShakingCount)
		{
			GetLevel()->SetCameraPos(MCam);
			HardShakingCount++;
		}
		else if (2 == HardShakingCount)
		{
			GetLevel()->SetCameraPos(DownCam);
			HardShakingCount++;
		}
		else if (3 == HardShakingCount)
		{
			GetLevel()->SetCameraPos(MCam);
			HardShakingCount = 0;
		}
	}

	if (SetShakingTime <= ShakingTime)
	{
		ShakingTime = 0.0f;
		CameraShakinghard = false;
	}

	// 복구
	if (false == CameraShakinghard)
	{
		if (1 == HardShakingCount || 2 == HardShakingCount)
		{
			GetLevel()->SetCameraPos(DownCam);
		}

		HardShakingCount = 0;
	}
}

void Player::AlphaBlinker(float _DeltaTime)
{
	BlinkTime += _DeltaTime;

	if (0.15f <= BlinkTime)
	{
		BlinkTime = 0.0f;
	}

	if (0.10f <= BlinkTime)
	{
		AnimationRender->SetAlpha(120);
	}
	else if (0.05f <= BlinkTime)
	{
		AnimationRender->SetAlpha(180);
	}
	else if (0.05f >= BlinkTime)
	{
		AnimationRender->SetAlpha(240);
	}
}

void Player::CreateDummy()
{
	Scarecrow* NewDummy = nullptr;
	float4 DummyPos = float4::Zero;
	DummyPos = GetPos() + (float4::Right * 250) + (float4::Up * 50);

	NewDummy = GetLevel()->CreateActor<Scarecrow>();
	NewDummy->SetColMap(ColMap);
	NewDummy->SetPos(DummyPos);
}

void Player::CreateImpact()
{
	Impact* NewImpact = nullptr;

	NewImpact = GetLevel()->CreateActor<Impact>();
	NewImpact->SetPos(ImpactPos);
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

////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////  6. 세팅  ///////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// 플레이어블 캐릭터 생성 시 필요한 데이터를 업데이트 합니다.

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
	AnimationRender->CreateAnimation({ .AnimationName = "Enter_R",  .ImageName = "Shantae_R.bmp", .Start = 204, .End = 242, .InterTime = 0.07f, .Loop = false });
	AnimationRender->CreateAnimation({ .AnimationName = "Portaling_R",  .ImageName = "Shantae_R.bmp", .Start = 242, .End = 242, .InterTime = 0.07f, .Loop = false });
	AnimationRender->CreateAnimation({ .AnimationName = "Out_R",  .ImageName = "Shantae_R.bmp", .Start = 243, .End = 266, .InterTime = 0.07f, .Loop = false });

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
	AnimationRender->CreateAnimation({ .AnimationName = "CrouchingHit_R",  .ImageName = "Shantae_R.bmp", .Start = 156, .End = 161, .InterTime = 0.08f });

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
	AnimationRender->CreateAnimation({ .AnimationName = "Enter_L",  .ImageName = "Shantae_L.bmp", .Start = 204, .End = 242, .InterTime = 0.07f, .Loop = false });
	AnimationRender->CreateAnimation({ .AnimationName = "Portaling_L",  .ImageName = "Shantae_L.bmp", .Start = 242, .End = 242, .InterTime = 0.07f, .Loop = false });
	AnimationRender->CreateAnimation({ .AnimationName = "Out_L",  .ImageName = "Shantae_L.bmp", .Start = 243, .End = 266, .InterTime = 0.07f, .Loop = false });

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
	AnimationRender->CreateAnimation({ .AnimationName = "CrouchingHit_L",  .ImageName = "Shantae_L.bmp", .Start = 156, .End = 161, .InterTime = 0.08f });
}

void Player::CollisionSet()
{
	// Standing
	BodyCollision = CreateCollision(CollisionOrder::Player);
	BodyCollision->SetDebugRenderType(CT_Rect);
	BodyCollision->SetScale({ 50, 90 });
	BodyCollision->SetPosition({ 0, -45 });

	StandingCollision = CreateCollision(CollisionOrder::PlayerEffect);
	StandingCollision->SetDebugRenderType(CT_Rect);
	StandingCollision->SetScale({ 40, 80 });
	StandingCollision->SetPosition({ 0, -40 });

	// Attack
	AttackCollision = CreateCollision(CollisionOrder::PlayerAttack);
	AttackCollision->SetDebugRenderType(CT_Rect);
	AttackCollision->SetScale({ 160, 50 });
	AttackCollision->SetPosition({ 100, -60 });
	AttackCollision->Off();
}

void Player::ItemUse(float _DeltaTiem)
{
	std::string Name = GetUseItemName();

	std::string UpperName = GameEngineString::ToUpper(GetUseItemName());

	std::string UpperName_comparison1 = GameEngineString::ToUpper("MonsterMilk");
	std::string UpperName_comparison2 = GameEngineString::ToUpper("Meat");
	std::string UpperName_comparison3 = GameEngineString::ToUpper("Bubble");
	std::string UpperName_comparison4 = GameEngineString::ToUpper("PikeBall");
	std::string UpperName_comparison5 = GameEngineString::ToUpper("Octopus");
	std::string UpperName_comparison6 = GameEngineString::ToUpper("IDCard");

	if (UpperName_comparison1 == UpperName)
	{
		if (1 == InventorySoundCount)
		{
			InventorySoundCount = 0;
			BGMPlayer = GameEngineResources::GetInst().SoundPlayToControl("Player_monstermilk.wav");
			BGMPlayer.Volume(0.1f);
			BGMPlayer.LoopCount(1);
			MonsterMilkEnd = false;
			MonsterMilkSet = 1;
		}

		UseMonsterMilk(_DeltaTiem);
	}

	if (UpperName_comparison2 == UpperName)
	{
		if (1 == InventorySoundCount)
		{
			InventorySoundCount = 0;
			BGMPlayer = GameEngineResources::GetInst().SoundPlayToControl("Player_hp_large.wav");
			BGMPlayer.Volume(0.1f);
			BGMPlayer.LoopCount(1);
			MeatEnd = false;
		}

		UseMeat();
	}

	if (UpperName_comparison3 == UpperName)
	{
		if (1 == InventorySoundCount)
		{
			InventorySoundCount = 0;
			BGMPlayer = GameEngineResources::GetInst().SoundPlayToControl("Player_bubble.wav");
			BGMPlayer.Volume(0.1f);
			BGMPlayer.LoopCount(1);
			BubbleEnd = false;
			BubbleSet = 1;
		}

		UseBubble(_DeltaTiem);
	}

	if (UpperName_comparison4 == UpperName)
	{
		if (1 == InventorySoundCount)
		{
			InventorySoundCount = 0;
			BGMPlayer = GameEngineResources::GetInst().SoundPlayToControl("Player_pikeball.wav");
			BGMPlayer.Volume(0.1f);
			BGMPlayer.LoopCount(1);
			PikeBallEnd = false;
			PikeBallSet = 1;
		}

		UsePikeBall(_DeltaTiem);
	}

	if (true == MonsterMilkEnd && true == PikeBallEnd && true == BubbleEnd)
	{
		MonsterMilkEnd = false;
		PikeBallEnd = false;
		BubbleEnd = false;
		MeatEnd = false;
		IsItemUse = false;
	}
}

void Player::UseMonsterMilk(float _DeltaTiem)
{
	if (1 == MonsterMilkSet)
	{
		MonsterMilkTime = 0.0f;
	}

	if (false == MonsterMilkEnd)
	{
		MonsterMilkTime += _DeltaTiem;

		if (15.0f >= MonsterMilkTime)
		{
			if (1 == MonsterMilkSet)
			{
				MonsterMilkSet = 0;
				SetPlayerDamage(5);
			}
		}
		else if (15.0f < MonsterMilkTime)
		{
			MonsterMilkTime = 0.0f;
			MonsterMilkEnd = true;
			SetPlayerDamage(-5);
		}
	}
}

void Player::UseMeat()
{
	if (false == IsItemUse)
	{
		SetPlayerHP(GetPlayerMaxHP());
		IsItemUse = true;
	}
}

void Player::UseBubble(float _DeltaTiem)
{
	if (1 == BubbleSet)
	{
		BubbleTime = 0.0f;
	}

	if (false == BubbleEnd)
	{
		BubbleTime += _DeltaTiem;

		if (13.0f >= BubbleTime)
		{
			if (1 == BubbleSet)
			{
				BubbleSet = 0;
				BodyCollision->Off();

				Bub = GetLevel()->CreateActor<BubbleEffect>();
				Bub->SetPos(GetPos());
			}
			
		}
		else if (13.0f < BubbleTime)
		{
			BodyCollision->On();
			BubbleTime = 0.0f;
			BubbleEnd = true;
			Bub->Kill();
			Bub = nullptr;
		}
	}
}

void Player::UsePikeBall(float _DeltaTiem)
{
	if (1 == PikeBallSet)
	{
		PikeBallTime = 0.0f;
	}

	if (false == PikeBallEnd)
	{
		PikeBallTime += _DeltaTiem;

		if (15.0f >= PikeBallTime)
		{
			if (1 == PikeBallSet)
			{
				PikeBallSet = 0;

				Pik = GetLevel()->CreateActor<PikeBallEffect>();
				Pik->SetPos(GetPos());
			}
		}
		else if (15.0f < PikeBallTime)
		{
			PikeBallTime = 0.0f;
			PikeBallEnd = true;
			Pik->Kill();
			Pik = nullptr;
		}
	}
}