#include "Player.h"

#include <GameEngineBase/GameEnginePath.h>
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineRender.h>
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/GameEngineCollision.h>
#include <GameEngineBase/GameEngineRandom.h>

#include "ContentsEnum.h"

// IsGravityPlus == false state
// JUMP, JUMPFALL, FALL, CROUCH, AIRATT, LAND(조건), Move(조건)


// Player State 변경
void Player::ChangeState(PlayerState _State)
{
	PlayerState NextState = _State;
	PlayerState PrevState = StateValue;

	StateValue = NextState;

	switch (NextState)
	{
	case PlayerState::IDLE:
		IdleStart();
		break;
	case PlayerState::REST:
		IdleRestStart();
		break;
	case PlayerState::MOVE:
		MoveStart();
		break;
	case PlayerState::MOVESTOP:
		MoveStopStart();
		break;
	case PlayerState::JUMP:
		IsGravityPlus = false;
		JumpStart();
		break;
	case PlayerState::JUMPFALL:
		JumpFallStart();
		break;
	case PlayerState::FALL:
		FallStart();
		break;
	case PlayerState::ATT:
		AttackStart();
		break;
	case PlayerState::CROUCHATT:
		CrouchAttackStart();
		break;
	case PlayerState::AIRATT:
		IsGravityPlus = false;
		AirAttackStart();
		break;
	case PlayerState::CROUCH:
		IsGravityPlus = false;
		CrouchingStart();
		break;
	case PlayerState::LAND:
		LandingStart();
		IsGravityPlus = false;
		break;
	case PlayerState::HIT:
		IsGravityPlus = false;
		HitStart();
		break;
	case PlayerState::JUMPHIT:
		IsGravityPlus = false;
		JumpHitStart();
		break;
	case PlayerState::JUMPHIT2:
		IsGravityPlus = false;
		JumpHitStart2();
		break;
	case PlayerState::CROUCHHIT:
		IsGravityPlus = false;
		CrouchHitStart();
		break;
	default:
		break;
	}

	switch (PrevState)
	{
	case PlayerState::IDLE:
		IdleEnd();
		break;
	case PlayerState::REST:
		IdleRestEnd();
		break;
	case PlayerState::MOVE:
		MoveEnd();
		break;
	case PlayerState::MOVESTOP:
		MoveStopEnd();
		break;
	case PlayerState::JUMP:
		JumpEnd();
		break;
	case PlayerState::JUMPFALL:
		JumpFallEnd();
		break;
	case PlayerState::FALL:
		FallEnd();
		break;
	case PlayerState::ATT:
		AttackEnd();
		break;
	case PlayerState::CROUCHATT:
		CrouchAttackEnd();
		break;
	case PlayerState::AIRATT:
		IsGravityPlus = false;
		AirAttackEnd();
		break;
	case PlayerState::CROUCH:
		IsGravityPlus = false;
		CrouchingEnd();
		break;
	case PlayerState::LAND:
		LandingEnd();
		break;
	case PlayerState::HIT:
		IsGravityPlus = false;
		HitEnd();
		break;
	case PlayerState::JUMPHIT:
		IsGravityPlus = false;
		JumpHitEnd();
		break;
	case PlayerState::JUMPHIT2:
		IsGravityPlus = false;
		JumpHitEnd2();
		break;
	case PlayerState::CROUCHHIT:
		IsGravityPlus = false;
		CrouchHitEnd();
		break;
	default:
		break;
	}
}

void Player::UpdateState(float _Time)
{
	if (true == CrouchMaintain)
	{
		StateValue = PlayerState::CROUCH;
	}

	switch (StateValue)
	{
	case PlayerState::IDLE:
		IdleUpdate(_Time);
		break;
	case PlayerState::REST:
		IdleRestUpdate(_Time);
		break;
	case PlayerState::MOVE:
		MoveUpdate(_Time);
		break;
	case PlayerState::MOVESTOP:
		MoveStopUpdate(_Time);
		break;
	case PlayerState::JUMP:
		IsGravityPlus = false;
		JumpUpdate(_Time);
		break;
	case PlayerState::JUMPFALL:
		IsGravityPlus = false;
		JumpFallUpdate(_Time);
		break;
	case PlayerState::FALL:
		IsGravityPlus = false;
		FallUpdate(_Time);
		break;
	case PlayerState::ATT:
		IsGravityPlus = false;
		AttackUpdate(_Time);
		break;
	case PlayerState::CROUCHATT:
		CrouchAttackUpdate(_Time);
		break;
	case PlayerState::AIRATT:
		IsGravityPlus = false;
		AirAttackUpdate(_Time);
		break;
	case PlayerState::CROUCH:
		IsGravityPlus = false;
		CrouchingUpdate(_Time);
		break;
	case PlayerState::LAND:
		LandingUpdate(_Time);
		break;
	case PlayerState::HIT:
		IsGravityPlus = false;
		HitUpdate(_Time);
		break;
	case PlayerState::JUMPHIT:
		IsGravityPlus = false;
		JumpHitUpdate(_Time);
		break;
	case PlayerState::JUMPHIT2:
		IsGravityPlus = false;
		JumpHitUpdate2(_Time);
		break;
	case PlayerState::CROUCHHIT:
		IsGravityPlus = false;
		CrouchHitUpdate(_Time);
		break;
	default:
		break;
	}
}

/////////////////////////////////////////////////////// States ///////////////////////////////////////////////////////

///////////////////////////////////////////////////////  Idle  ///////////////////////////////////////////////////////

void Player::IdleStart()
{
	if (3 <= HP && 6 >= HP)
	{
		DirCheck("Idle");
	}
	else if (3 > HP)
	{
		DirCheck("LowHP");
	}
	else if (6 < HP)
	{
		DirCheck("IdleDance");
	}
}
void Player::IdleUpdate(float _Time)
{
	IdleTime += _Time;

	if (true == HitAction)
	{
		ChangeState(PlayerState::HIT);
		return;
	}

	if (GameEngineInput::IsPress("LeftMove") || GameEngineInput::IsPress("RightMove"))
	{
		ChangeState(PlayerState::MOVE);
		return;
	}

	if (GameEngineInput::IsDown("Jump") && false == IsJump)
	{
		ChangeState(PlayerState::JUMP);
		return;
	}
	else if (GameEngineInput::IsDown("Attack"))
	{
		ChangeState(PlayerState::ATT);
		return;
	}
	else if (GameEngineInput::IsPress("DownMove"))
	{
		ChangeState(PlayerState::CROUCH);
		return;
	}

	if (true == Fall /*&& 0.1f <= FallTime*/)
	{
		IsGravityPlus = false;
		ChangeState(PlayerState::FALL);
		return;
	}
	else if (GameEngineInput::IsDown("Jump") && false == IsJump /*&& false == Fall*/)
	{
		ChangeState(PlayerState::JUMP);
		return;
	}

	if (6.0f <= IdleTime && 3 <= HP)
	{
		IdleTime = 0.0f;
		ChangeState(PlayerState::REST);
		return;
	}
}
void Player::IdleEnd()
{
	IdleTime = 0.0f;
}

///////////////////////////////////////////////////////  Rest  ///////////////////////////////////////////////////////

bool RestSet = true;

void Player::IdleRestStart()
{
	if (true == RestSet)
	{
		DirCheck("IdleRest1");
		RestSet = false;
	}
	else if (false == RestSet)
	{
		DirCheck("IdleRest2");
		RestSet = true;
	}
}
void Player::IdleRestUpdate(float _Time)
{
	if (true == HitAction)
	{
		ChangeState(PlayerState::HIT);
		return;
	}

	if (GameEngineInput::IsPress("LeftMove") || GameEngineInput::IsPress("RightMove"))
	{
		ChangeState(PlayerState::MOVE);
		return;
	}

	if (GameEngineInput::IsDown("Jump") && false == IsJump)
	{
		ChangeState(PlayerState::JUMP);
		return;
	}
	else if (GameEngineInput::IsDown("Attack"))
	{
		ChangeState(PlayerState::ATT);
		return;
	}
	else if (GameEngineInput::IsPress("DownMove"))
	{
		ChangeState(PlayerState::CROUCH);
		return;
	}

	if (true == Fall && 0.1f <= FallTime)
	{
		ChangeState(PlayerState::FALL);
		return;
	}
	else if (GameEngineInput::IsDown("Jump") && false == IsJump && false == Fall)
	{
		ChangeState(PlayerState::JUMP);
		return;
	}

	if (true == AnimationRender->IsAnimationEnd())
	{
		ChangeState(PlayerState::IDLE);
		return;
	}

}
void Player::IdleRestEnd()
{
}

///////////////////////////////////////////////////////  Move  ///////////////////////////////////////////////////////

void Player::MoveStart()
{
	IsGravityPlus = true;
	// Animation Start
	DirCheck("Run");

	if ("_L" == DirString)
	{
		AttackDir = false;
	}
	if ("_R" == DirString)
	{
		AttackDir = true;
	}

	if (2 == MoveSoundCount)
	{
		BGMPlayer = GameEngineResources::GetInst().SoundPlayToControl("Player_move3.wav");
		BGMPlayer.Volume(0.3f);
		BGMPlayer.LoopCount(1);

		MoveSoundCount = 1;
	}
	else if (1 == MoveSoundCount)
	{
		BGMPlayer = GameEngineResources::GetInst().SoundPlayToControl("Player_move2.wav");
		BGMPlayer.Volume(0.3f);
		BGMPlayer.LoopCount(1);

		MoveSoundCount = 2;
	}
}
void Player::MoveUpdate(float _Time)
{
	MoveSoundTime += _Time;

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

	if (true == HitAction)
	{
		ChangeState(PlayerState::HIT);
		return;
	}

	if (false == GameEngineInput::IsPress("LeftMove") && false == GameEngineInput::IsPress("RightMove") && 1.0f <= MoveTime && 3 < HP)
	{
		ChangeState(PlayerState::MOVESTOP);
		return;
	}

	if (false == GameEngineInput::IsPress("LeftMove") && false == GameEngineInput::IsPress("RightMove"))
	{
		ChangeState(PlayerState::IDLE);
		return;
	}

	// Move 이동 계산
	if (false == IsStartAnimationStart)
	{
		if (true == GameEngineInput::IsPress("LeftMove"))
		{
			if (true == ShantaeMove)
			{
				SetMove(float4::Left * MoveSpeed * _Time);
			}
			if (true == CameraMove)
			{
				GetLevel()->SetCameraMove(float4::Left * MoveSpeed * _Time);
			}
		}
		else if (true == GameEngineInput::IsPress("RightMove"))
		{
			if (true == ShantaeMove)
			{
				SetMove(float4::Right * MoveSpeed * _Time);
			}
			if (true == CameraMove)
			{
				GetLevel()->SetCameraMove(float4::Right * MoveSpeed * _Time);
			}
		}
	}

	if (true == GameEngineInput::IsDown("Attack"))
	{
		ChangeState(PlayerState::ATT);
		return;
	}
	if (true == GameEngineInput::IsPress("DownMove"))
	{
		ChangeState(PlayerState::CROUCH);
		return;
	}

	if (true == Fall && 0.15f <= FallTime)
	{
		ChangeState(PlayerState::FALL);
		return;
	}
	else if (GameEngineInput::IsDown("Jump") && false == IsJump && false == Fall)
	{
		ChangeState(PlayerState::JUMP);
		return;
	}

	DirCheck("Run");
}
void Player::MoveEnd()
{
	MoveTime = 0.0f;
	MoveSoundTime = 0.0f;
}

///////////////////////////////////////////////////////  Jump  ///////////////////////////////////////////////////////

bool Check = false;

void Player::JumpStart()
{
	int RandC = GameEngineRandom::MainRandom.RandomInt(1, 10);

	if (1 == RandC)
	{
		BGMPlayer = GameEngineResources::GetInst().SoundPlayToControl("Player_jump.wav");
		BGMPlayer.Volume(0.1f);
		BGMPlayer.LoopCount(1);
	}

	Pass = 0;
	Fall = false;
	IsJump = true;
	IsGravityPlus = false;
	JumpPos = GetPos().y;

	if (GameEngineInput::IsUp("Jump"))
	{
		MoveDir.y -= 600.0f;
	} 
	{
		MoveDir.y -= 1250.0f;
	}

	DirCheck("Jump");
}
void Player::JumpUpdate(float _Time)
{	
	if (JumpTime < 0.1f)
	{
		JumpTime += _Time;
	}

	if (true == HitAction)
	{
		Highest = false;
		Fall = true;
		ChangeState(PlayerState::JUMPHIT);
		return;
	}

	// Jump 이동 계산
	if (true == GameEngineInput::IsPress("LeftMove"))
	{
		if (true == ShantaeMove)
		{
			SetMove(float4::Left * MoveSpeed * _Time);
		}
		if (true == CameraMove)
		{
			GetLevel()->SetCameraMove(float4::Left * MoveSpeed * _Time);
		}
	}
	else if (true == GameEngineInput::IsPress("RightMove"))
	{
		if (true == ShantaeMove)
		{
			SetMove(float4::Right * MoveSpeed * _Time);
		}
		if (true == CameraMove)
		{
			GetLevel()->SetCameraMove(float4::Right * MoveSpeed * _Time);
		}
	}

	if (true == GameEngineInput::IsDown("Attack"))
	{
		ChangeState(PlayerState::AIRATT);
		return;
	}

	if (JumpPos - 190.0f > GetPos().y)
	{
		DirCheck("JumpHighest");
	}

	if (JumpPos - 220.0f > GetPos().y)
	{
		Highest = true;
	}

	if (true == Highest || true == Fall)
	{
		Highest = false;
		Fall = true;
		ChangeState(PlayerState::JUMPFALL);
	}

	DirCheck("Jump");
}
void Player::JumpEnd()
{
	JumpTime = 0.0f;
}

///////////////////////////////////////////////////////  Fall  ///////////////////////////////////////////////////////

void Player::JumpFallStart()
{
	IsJump = true;
}
void Player::JumpFallUpdate(float _Time)
{
	if (true == HitAction)
	{
		Fall = false;
		IsJump = false;
		ChangeState(PlayerState::JUMPHIT);
		return;
	}

	// Fall 이동 계산
	if (true == GameEngineInput::IsPress("LeftMove"))
	{
		if (true == ShantaeMove)
		{
			SetMove(float4::Left * MoveSpeed * _Time);
		}
		if (true == CameraMove)
		{
			GetLevel()->SetCameraMove(float4::Left * MoveSpeed * _Time);
		}
	}
	else if (true == GameEngineInput::IsPress("RightMove"))
	{
		if (true == ShantaeMove)
		{
			SetMove(float4::Right * MoveSpeed * _Time);
		}
		if (true == CameraMove)
		{
			GetLevel()->SetCameraMove(float4::Right * MoveSpeed * _Time);
		}
	}

	if (true == GameEngineInput::IsDown("Attack"))
	{
		ChangeState(PlayerState::AIRATT);
		return;
	}

	if (false == DownJump)
	{
		if (RGB(0, 248, 0) == ColMap->GetPixelColor(NextPos, RGB(0, 0, 0)))
		{
			Fall = false;
			IsJump = false;
			ChangeState(PlayerState::LAND);
			return;
		}

		if (RGB(74, 65, 42) == ColMap->GetPixelColor(NextPos, RGB(0, 0, 0)))
		{
			Fall = false;
			IsJump = false;
			ChangeState(PlayerState::LAND);
			return;
		}

		if (true == CollisionGround)
		{
			Fall = false;
			IsJump = false;
			ChangeState(PlayerState::LAND);
			return;
		}
	}

	DirCheck("BeforeFall");

	if (115 == AnimationRender->GetFrame() && true == Fall)
	{
		DirCheck("Fall");
	}
}
void Player::JumpFallEnd()
{
}

void Player::FallStart()
{
	IsJump = true;
	// Animation Start
}
void Player::FallUpdate(float _Time)
{
	if (true == HitAction)
	{
		Fall = false;
		IsJump = false;
		ChangeState(PlayerState::JUMPHIT);
		return;
	}

	// Fall 이동 계산
	if (true == GameEngineInput::IsPress("LeftMove"))
	{
		if (true == ShantaeMove)
		{
			SetMove(float4::Left * MoveSpeed * _Time);
		}
		if (true == CameraMove)
		{
			GetLevel()->SetCameraMove(float4::Left * MoveSpeed * _Time);
		}
	}
	else if (true == GameEngineInput::IsPress("RightMove"))
	{
		if (true == ShantaeMove)
		{
			SetMove(float4::Right * MoveSpeed * _Time);
		}
		if (true == CameraMove)
		{
			GetLevel()->SetCameraMove(float4::Right * MoveSpeed * _Time);
		}
	}

	if (true == GameEngineInput::IsDown("Attack"))
	{
		ChangeState(PlayerState::AIRATT);
		return;
	}

	if (false == DownJump)
	{
		if (RGB(74, 65, 42) == ColMap->GetPixelColor(NextPos, RGB(0, 0, 0))
			|| RGB(0, 248, 0) == ColMap->GetPixelColor(NextPos, RGB(0, 0, 0)))
		{
			if (RGB(74, 65, 42) != ColMap->GetPixelColor(GetPos(), RGB(0, 0, 0)))
			{
				Fall = false;
				IsJump = false;
				ChangeState(PlayerState::LAND);
				return;
			}
		}
	}

	if (true == CollisionGround)
	{
		Fall = false;
		IsJump = false;
		ChangeState(PlayerState::LAND);
		return;
	}

	DirCheck("BeforeFall");

	if (115 == AnimationRender->GetFrame() && true == Fall)
	{
		DirCheck("Fall");
	}

}
void Player::FallEnd()
{
}

///////////////////////////////////////////////////////  Attack  ///////////////////////////////////////////////////////

void Player::AttackStart()
{
	BGMPlayer = GameEngineResources::GetInst().SoundPlayToControl("Player_attack.wav");
	BGMPlayer.Volume(0.1f);
	BGMPlayer.LoopCount(1);

	int RandC = GameEngineRandom::MainRandom.RandomInt(1, 10);

	if (1 == RandC)
	{
		BGMPlayer = GameEngineResources::GetInst().SoundPlayToControl("Player_attack_voice2.wav");
		BGMPlayer.Volume(0.1f);
		BGMPlayer.LoopCount(1);
	}


	DirCheck("Attack");

	if ("_L" == DirString)
	{
		AttackDir = false;
	}
	if ("_R" == DirString)
	{
		AttackDir = true;
	}
}
void Player::AttackUpdate(float _Time)
{
	if (true == HitAction)
	{
		// Highest = false;
		// Fall = true;
		ChangeState(PlayerState::HIT);
		return;
	}

	if (192 <= AnimationRender->GetFrame())
	{
		IsAttackStart = true;
		IsAttack = true;
	}

	if (true == AnimationRender->IsAnimationEnd())
	{
		IsAttackStart = false;
		IsAttack = false;
		IsJump = false;
		ChangeState(PlayerState::IDLE);
		return;
	}
}
void Player::AttackEnd()
{
}

void Player::CrouchAttackStart()
{
	BGMPlayer = GameEngineResources::GetInst().SoundPlayToControl("Player_attack.wav");
	BGMPlayer.Volume(0.1f);
	BGMPlayer.LoopCount(1);

	int RandC = GameEngineRandom::MainRandom.RandomInt(1, 10);

	if (1 == RandC)
	{
		BGMPlayer = GameEngineResources::GetInst().SoundPlayToControl("Player_attack_voice1.wav");
		BGMPlayer.Volume(0.1f);
		BGMPlayer.LoopCount(1);
	}

	IsCrouch = true;
	
	DirCheck("CrouchingAttack");

	if ("_L" == DirString)
	{
		AttackDir = false;
	}
	if ("_R" == DirString)
	{
		AttackDir = true;
	}
}
void Player::CrouchAttackUpdate(float _Time)
{
	if (true == HitAction)
	{
		// Highest = false;
		// Fall = true;
		ChangeState(PlayerState::CROUCHHIT);
		return;
	}

	CrouchMaintain = true;

	if (166 <= AnimationRender->GetFrame())
	{
		IsAttackStart = true;
		IsCrouchAttack = true;
	}

	if (true == AnimationRender->IsAnimationEnd())
	{
		IsAttackStart = false;
		IsCrouchAttack = false;
		ChangeState(PlayerState::CROUCH);
		return;
	}
}
void Player::CrouchAttackEnd()
{
}

bool Movestop = false;

void Player::AirAttackStart()
{	
	BGMPlayer = GameEngineResources::GetInst().SoundPlayToControl("Player_attack.wav");
	BGMPlayer.Volume(0.1f);
	BGMPlayer.LoopCount(1);

	int RandC = GameEngineRandom::MainRandom.RandomInt(1, 10);

	if (1 == RandC)
	{
		BGMPlayer = GameEngineResources::GetInst().SoundPlayToControl("Player_attack_voice1.wav");
		BGMPlayer.Volume(0.1f);
		BGMPlayer.LoopCount(1);
	}

	DirCheck("JumpAttack");

	if (true == AirAttack)
	{
		if ("_L" == DirString)
		{
			AttackDir = false;
		}
		if ("_R" == DirString)
		{
			AttackDir = true;
		}
	}
}
void Player::AirAttackUpdate(float _Time)
{
	if (true == HitAction)
	{
		// Highest = false;
		// Fall = true;
		ChangeState(PlayerState::JUMPHIT);
		return;
	}

	if (200 <= AnimationRender->GetFrame())
	{
		IsAttackStart = true;
		IsAirAttack = true;
	}

	if (RGB(74, 65, 42) == ColMap->GetPixelColor(NextPos, RGB(0, 0, 0))
		|| RGB(0, 248, 0) == ColMap->GetPixelColor(NextPos, RGB(0, 0, 0)))
	{
		Movestop = true;
	}

	if (true == CollisionGround)
	{
		Movestop = true;
	}

	if (false == Movestop)
	{
		if (true == GameEngineInput::IsPress("LeftMove"))
		{
			if (true == ShantaeMove)
			{
				SetMove(float4::Left * MoveSpeed * _Time);
			}
			if (true == CameraMove)
			{
				GetLevel()->SetCameraMove(float4::Left * MoveSpeed * _Time);
			}
		}
		else if (true == GameEngineInput::IsPress("RightMove"))
		{
			if (true == ShantaeMove)
			{
				SetMove(float4::Right * MoveSpeed * _Time);
			}
			if (true == CameraMove)
			{
				GetLevel()->SetCameraMove(float4::Right * MoveSpeed * _Time);
			}
		}
	}

	if (true == AnimationRender->IsAnimationEnd())
	{
		IsAttackStart = false;
		IsAirAttack = false;
		DownJump = false;
		ChangeState(PlayerState::FALL);
		return;
	}
}
void Player::AirAttackEnd()
{
	Movestop = false;
}

///////////////////////////////////////////////////////  Crounching  ///////////////////////////////////////////////////////

void Player::CrouchingStart()
{
	IsCrouch = true;
	
	DirCheck("CrouchingMaintain");
}
void Player::CrouchingUpdate(float _Time)
{
	if (true == HitAction)
	{
		// Highest = false;
		// Fall = true;
		ChangeState(PlayerState::CROUCHHIT);
		return;
	}

	if (RGB(74, 65, 42) == ColMap->GetPixelColor(NextPos, RGB(0, 0, 0)))
	{
		if (true == GameEngineInput::IsPress("DownMove") && true == GameEngineInput::IsDown("Jump"))
		{
			DownJump = true;
			ChangeState(PlayerState::FALL);
			return;
		}
	}

	if (false == GameEngineInput::IsPress("DownMove") && false == CrouchMaintain)
	{
		ChangeState(PlayerState::IDLE);
		return;
	}

	if (false == CrouchMaintain)
	{
		if (true == GameEngineInput::IsPress("DownMove") && true == GameEngineInput::IsDown("Attack"))
		{
			ChangeState(PlayerState::CROUCHATT);
			return;
		}
	}

	if (true == CrouchMaintain)
	{
		if (true == GameEngineInput::IsDown("Attack"))
		{
			ChangeState(PlayerState::CROUCHATT);
			return;
		}
	}

	// Crawling 이동 계산
	if (false == CrouchMaintain)
	{
		if (true == GameEngineInput::IsPress("DownMove") && true == GameEngineInput::IsPress("LeftMove"))
		{
			CrouchMoveSoundTime += _Time;

			if (0.35f <= CrouchMoveSoundTime)
			{
				if (1 == CrouchMoveSoundCount)
				{
					CrouchMovePlayer = GameEngineResources::GetInst().SoundPlayToControl("Player_crouchmove.wav");
					CrouchMovePlayer.Volume(0.3f);
					CrouchMovePlayer.LoopCount(1);

					CrouchMoveSoundTime = 0.0f;
					CrouchMoveSoundCount = 0;
				}
				else if (0 == CrouchMoveSoundCount)
				{
					CrouchMoveSoundCount = 1;
				}
			}

			if (true == ShantaeMove)
			{
				SetMove(float4::Left * CrouchSpeed * _Time);
			}
			if (true == CameraMove)
			{
				GetLevel()->SetCameraMove(float4::Left * CrouchSpeed * _Time);
			}
		}
		else if (true == GameEngineInput::IsPress("DownMove") && true == GameEngineInput::IsPress("RightMove"))
		{
			CrouchMoveSoundTime += _Time;

			if (0.35f <= CrouchMoveSoundTime)
			{
				if (1 == CrouchMoveSoundCount)
				{
					CrouchMovePlayer = GameEngineResources::GetInst().SoundPlayToControl("Player_crouchmove.wav");
					CrouchMovePlayer.Volume(0.3f);
					CrouchMovePlayer.LoopCount(1);

					CrouchMoveSoundTime = 0.0f;
					CrouchMoveSoundCount = 0;
				}
				else if (0 == CrouchMoveSoundCount)
				{
					CrouchMoveSoundCount = 1;
				}
			}

			if (true == ShantaeMove)
			{
				SetMove(float4::Right * CrouchSpeed * _Time);
			}
			if (true == CameraMove)
			{
				GetLevel()->SetCameraMove(float4::Right * CrouchSpeed * _Time);
			}
		}
	}

	if (true == CrouchMaintain)
	{
		if (true == GameEngineInput::IsPress("LeftMove"))
		{
			if (true == ShantaeMove)
			{
				SetMove(float4::Left * CrouchSpeed * _Time);
			}
			if (true == CameraMove)
			{
				GetLevel()->SetCameraMove(float4::Left * CrouchSpeed * _Time);
			}
		}
		else if (true == GameEngineInput::IsPress("RightMove"))
		{
			if (true == ShantaeMove)
			{
				SetMove(float4::Right * CrouchSpeed * _Time);
			}
			if (true == CameraMove)
			{
				GetLevel()->SetCameraMove(float4::Right * CrouchSpeed * _Time);
			}
		}
	}

	// Crawling 동작
	if (false == CrouchMaintain)
	{
		if (true == GameEngineInput::IsPress("DownMove") && true == GameEngineInput::IsPress("LeftMove"))
		{
			DirCheck("CrouchingMove");
		}
		else if (true == GameEngineInput::IsPress("DownMove") && true == GameEngineInput::IsPress("RightMove"))
		{
			DirCheck("CrouchingMove");
		}
		else
		{
			DirCheck("CrouchingMaintain");
		}
	}
	if (true == CrouchMaintain)
	{
		if (true == GameEngineInput::IsPress("LeftMove"))
		{
			DirCheck("CrouchingMove");
		}
		else if (true == GameEngineInput::IsPress("RightMove"))
		{
			DirCheck("CrouchingMove");
		}
		else
		{
			DirCheck("CrouchingMaintain");
		}
	}

	if (true == Fall && 0.1f <= FallTime)
	{
		ChangeState(PlayerState::FALL);
		return;
	}
	else if (GameEngineInput::IsDown("Jump") && false == IsJump && false == Fall && false == CrouchMaintain)
	{
		ChangeState(PlayerState::JUMP);
		return;
	}
}
void Player::CrouchingEnd()
{
	IsCrouch = false;
}

///////////////////////////////////////////////////////  Landing  ///////////////////////////////////////////////////////

void Player::LandingStart()
{
	int RandC = GameEngineRandom::MainRandom.RandomInt(1, 5);

	if (1 == RandC)
	{
		BGMPlayer = GameEngineResources::GetInst().SoundPlayToControl("Player_land.wav");
		BGMPlayer.Volume(0.1f);
		BGMPlayer.LoopCount(1);
	}

	Fall = false;
    IsJump = false;
	// Animation Start
	DirCheck("Landing");
}
void Player::LandingUpdate(float _Time)
{
	if (true == HitAction)
	{
		// Highest = false;
		// Fall = true;
		ChangeState(PlayerState::HIT);
		return;
	}

	float LandTime = 0.0f;
	LandTime += _Time;

	if (0.1f >= LandTime)
	{
		IsGravityPlus = false;
	}
	else
	{
		LandTime = 0.0f;
		IsGravityPlus = true;
	}

	if (GameEngineInput::IsPress("LeftMove") || GameEngineInput::IsPress("RightMove"))
	{
		ChangeState(PlayerState::MOVE);
		return;
	}

	if (GameEngineInput::IsDown("Jump") && false == IsJump)
	{
		ChangeState(PlayerState::JUMP);
		return;
	}
	else if (GameEngineInput::IsDown("Attack"))
	{
		ChangeState(PlayerState::ATT);
		return;
	}
	else if (GameEngineInput::IsPress("DownMove"))
	{
		ChangeState(PlayerState::CROUCH);
		return;
	}

	if (true == Fall && 0.1f <= FallTime)
	{
		ChangeState(PlayerState::FALL);
		return;
	}
	else if (GameEngineInput::IsDown("Jump") && false == IsJump && false == Fall)
	{
		ChangeState(PlayerState::JUMP);
		return;
	}

	if (true == AnimationRender->IsAnimationEnd())
	{
		ChangeState(PlayerState::IDLE);
		return;
	}
}
void Player::LandingEnd()
{
}

///////////////////////////////////////////////////////  MoveStop  ///////////////////////////////////////////////////////

void Player::MoveStopStart()
{
	// Animation Start
	DirCheck("RunStop");
}
void Player::MoveStopUpdate(float _Time)
{
	if (true == HitAction)
	{
		// Highest = false;
		// Fall = true;
		ChangeState(PlayerState::HIT);
		return;
	}

	if (GameEngineInput::IsPress("LeftMove") || GameEngineInput::IsPress("RightMove"))
	{
		ChangeState(PlayerState::MOVE);
		return;
	}

	if (GameEngineInput::IsDown("Jump") && false == IsJump)
	{
		ChangeState(PlayerState::JUMP);
		return;
	}
	else if (GameEngineInput::IsDown("Attack"))
	{
		ChangeState(PlayerState::ATT);
		return;
	}
	else if (GameEngineInput::IsPress("DownMove"))
	{
		ChangeState(PlayerState::CROUCH);
		return;
	}

	if (true == Fall && 0.1f <= FallTime)
	{
		ChangeState(PlayerState::FALL);
		return;
	}
	else if (GameEngineInput::IsDown("Jump") && false == IsJump && false == Fall)
	{
		ChangeState(PlayerState::JUMP);
		return;
	}

	if (true == AnimationRender->IsAnimationEnd())
	{
		ChangeState(PlayerState::IDLE);
		return;
	}
}
void Player::MoveStopEnd()
{
}

///////////////////////////////////////////////////////  Hit  ///////////////////////////////////////////////////////

void Player::HitStart()
{
	int RandC = GameEngineRandom::MainRandom.RandomInt(1, 5);

	if (1 == RandC)
	{
		BGMPlayer = GameEngineResources::GetInst().SoundPlayToControl("Player_hit1.wav");
		BGMPlayer.Volume(0.1f);
		BGMPlayer.LoopCount(1);
	}
	else if (2 == RandC)
	{
		BGMPlayer = GameEngineResources::GetInst().SoundPlayToControl("Player_hit2.wav");
		BGMPlayer.Volume(0.1f);
		BGMPlayer.LoopCount(1);
	}
	else if (3 == RandC)
	{
		BGMPlayer = GameEngineResources::GetInst().SoundPlayToControl("Player_hit3.wav");
		BGMPlayer.Volume(0.1f);
		BGMPlayer.LoopCount(1);
	}
	else if (4 == RandC)
	{
		BGMPlayer = GameEngineResources::GetInst().SoundPlayToControl("Player_hit4.wav");
		BGMPlayer.Volume(0.1f);
		BGMPlayer.LoopCount(1);
	}
	else if (5 == RandC)
	{
		BGMPlayer = GameEngineResources::GetInst().SoundPlayToControl("Player_hit5.wav");
		BGMPlayer.Volume(0.1f);
		BGMPlayer.LoopCount(1);
	}

	MoveDir.y = 0.0f;

	IsGravity = false;

	MoveDir.y -= 500.0f;

	DirCheck("Hit");
}
void Player::HitUpdate(float _Time)
{
	IsGravity = true;

	if (0.4f <= HitTime)
	{
		HitAction = false;
	}

	if (true == AnimationRender->IsAnimationEnd())
	{
		ChangeState(PlayerState::IDLE);
		return;
	}
}
void Player::HitEnd()
{
}

void Player::CrouchHitStart()
{
	int RandC = GameEngineRandom::MainRandom.RandomInt(1, 5);

	if (1 == RandC)
	{
		BGMPlayer = GameEngineResources::GetInst().SoundPlayToControl("Player_hit1.wav");
		BGMPlayer.Volume(0.1f);
		BGMPlayer.LoopCount(1);
	}
	else if (2 == RandC)
	{
		BGMPlayer = GameEngineResources::GetInst().SoundPlayToControl("Player_hit2.wav");
		BGMPlayer.Volume(0.1f);
		BGMPlayer.LoopCount(1);
	}
	else if (3 == RandC)
	{
		BGMPlayer = GameEngineResources::GetInst().SoundPlayToControl("Player_hit3.wav");
		BGMPlayer.Volume(0.1f);
		BGMPlayer.LoopCount(1);
	}
	else if (4 == RandC)
	{
		BGMPlayer = GameEngineResources::GetInst().SoundPlayToControl("Player_hit4.wav");
		BGMPlayer.Volume(0.1f);
		BGMPlayer.LoopCount(1);
	}
	else if (5 == RandC)
	{
		BGMPlayer = GameEngineResources::GetInst().SoundPlayToControl("Player_hit5.wav");
		BGMPlayer.Volume(0.1f);
		BGMPlayer.LoopCount(1);
	}

	DirCheck("CrouchingHit");
}
void Player::CrouchHitUpdate(float _Time)
{
	if (0.4f <= HitTime)
	{
		HitAction = false;
	}

	if (true == AnimationRender->IsAnimationEnd())
	{
		ChangeState(PlayerState::CROUCH);
		return;
	}
}
void Player::CrouchHitEnd()
{
}

void Player::JumpHitStart()
{
	int RandC = GameEngineRandom::MainRandom.RandomInt(1, 5);

	if (1 == RandC)
	{
		BGMPlayer = GameEngineResources::GetInst().SoundPlayToControl("Player_hit1.wav");
		BGMPlayer.Volume(0.1f);
		BGMPlayer.LoopCount(1);
	}
	else if (2 == RandC)
	{
		BGMPlayer = GameEngineResources::GetInst().SoundPlayToControl("Player_hit2.wav");
		BGMPlayer.Volume(0.1f);
		BGMPlayer.LoopCount(1);
	}
	else if (3 == RandC)
	{
		BGMPlayer = GameEngineResources::GetInst().SoundPlayToControl("Player_hit3.wav");
		BGMPlayer.Volume(0.1f);
		BGMPlayer.LoopCount(1);
	}
	else if (4 == RandC)
	{
		BGMPlayer = GameEngineResources::GetInst().SoundPlayToControl("Player_hit4.wav");
		BGMPlayer.Volume(0.1f);
		BGMPlayer.LoopCount(1);
	}
	else if (5 == RandC)
	{
		BGMPlayer = GameEngineResources::GetInst().SoundPlayToControl("Player_hit5.wav");
		BGMPlayer.Volume(0.1f);
		BGMPlayer.LoopCount(1);
	}

	IsJumpHit = true;
	MoveDir.y = 0.0f;
	IsGravity = false;
	MoveDir.y -= 400.0f;

	std::string HitDir = DirString;

	DirCheck("JumpHit1");
}
void Player::JumpHitUpdate(float _Time)
{
	IsGravity = true;

	if ("_L" == DirString)
	{
		MoveSpeed = 400.0f;
		WallCheck(400.0f);
		SetMove(float4::Right * MoveSpeed * _Time);
		if (true == CameraMove)
		{
			GetLevel()->SetCameraMove(float4::Right * MoveSpeed * _Time);
		}
	}
	else if ("_R" == DirString)
	{
		MoveSpeed = 400.0f;
		WallCheck(400.0f);
		SetMove(float4::Left * MoveSpeed * _Time);
		if (true == CameraMove)
		{
			GetLevel()->SetCameraMove(float4::Left * MoveSpeed * _Time);
		}
	}

	if (RGB(74, 65, 42) == ColMap->GetPixelColor(NextPos, RGB(0, 0, 0))
		|| RGB(0, 248, 0) == ColMap->GetPixelColor(NextPos, RGB(0, 0, 0)))
	{
		IsJumpHit = false;
		ChangeState(PlayerState::JUMPHIT2);
		return;
	}

	if (true == CollisionGround)
	{
		IsJumpHit = false;
		ChangeState(PlayerState::JUMPHIT2);
		return;
	}

	DirCheck("JumpHit2");
}
void Player::JumpHitEnd()
{
}

void Player::JumpHitStart2()
{
	DirCheck("JumpHit3");
}
void Player::JumpHitUpdate2(float _Time)
{
	if (0.4f <= HitTime)
	{
		HitAction = false;
	}

	if (true == AnimationRender->IsAnimationEnd())
	{
		ChangeState(PlayerState::IDLE);
		return;
	}
}
void Player::JumpHitEnd2()
{
}