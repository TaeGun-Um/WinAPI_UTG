#include "Soldier_Blue.h"

#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineCollision.h>

#include "Player.h"
#include "ContentsEnum.h"

// Player State º¯°æ
void Soldier_Blue::ChangeState(Soldier_BlueState _State)
{
	Soldier_BlueState NextState = _State;
	Soldier_BlueState PrevState = StateValue;

	StateValue = NextState;

	switch (NextState)
	{
	case Soldier_BlueState::MOVE:
		MoveStart();
		break;
	case Soldier_BlueState::MOVESTOP:
		MoveStopStart();
		break;
	case Soldier_BlueState::JUMP:
		IsGravityPlus = false;
		JumpStart();
		break;
	case Soldier_BlueState::JUMPWALL:
		IsGravityPlus = false;
		JumpWallStart();
		break;
	case Soldier_BlueState::AMBUSH:
		AmbushStart();
		break;
	case Soldier_BlueState::HIT:
		IsGravityPlus = false;
		HitStart();
		break;
	default:
		break;
	}

	switch (PrevState)
	{
	case Soldier_BlueState::MOVE:
		MoveEnd();
		break;
	case Soldier_BlueState::MOVESTOP:
		MoveStopEnd();
		break;
	case Soldier_BlueState::JUMP:
		IsGravityPlus = false;
		JumpEnd();
		break;
	case Soldier_BlueState::JUMPWALL:
		IsGravityPlus = false;
		JumpWallEnd();
		break;
	case Soldier_BlueState::AMBUSH:
		AmbushEnd();
		break;
	case Soldier_BlueState::HIT:
		IsGravityPlus = false;
		HitEnd();
		break;
	default:
		break;
	}
}

void Soldier_Blue::UpdateState(float _Time)
{
	switch (StateValue)
	{
	case Soldier_BlueState::MOVE:
		MoveUpdate(_Time);
		break;
	case Soldier_BlueState::MOVESTOP:
		MoveStopUpdate(_Time);
		break;
	case Soldier_BlueState::JUMP:
		IsGravityPlus = false;
		JumpUpdate(_Time);
		break;
	case Soldier_BlueState::JUMPWALL:
		IsGravityPlus = false;
		JumpWallUpdate(_Time);
		break;
	case Soldier_BlueState::AMBUSH:
		AmbushUpdate(_Time);
		break;
	case Soldier_BlueState::HIT:
		IsGravityPlus = false;
		HitUpdate(_Time);
		break;
	default:
		break;
	}
}

/////////////////////////////////////////////////////// States ///////////////////////////////////////////////////////

///////////////////////////////////////////////////////  Move  ///////////////////////////////////////////////////////

void Soldier_Blue::MoveStart()
{
	// Animation Start
	DirCheck("Move");
}
void Soldier_Blue::MoveUpdate(float _Time)
{
	if (true == HitAction)
	{
		ChangeState(Soldier_BlueState::HIT);
		return;
	}

	if (true == MoveDirect)
	{
		SetMove(float4::Left * MoveSpeed * _Time);
	}
	else if (false == MoveDirect)
	{
		SetMove(float4::Right * MoveSpeed * _Time);
	}

	if (true == IsTurn)
	{
		ChangeState(Soldier_BlueState::MOVESTOP);
		return;
	}

	if (true == IsJump)
	{
		ChangeState(Soldier_BlueState::JUMP);
		return;
	}

	DirCheck("Move");
}
void Soldier_Blue::MoveEnd()
{
}

///////////////////////////////////////////////////////  MoveStop  ///////////////////////////////////////////////////////

void Soldier_Blue::MoveStopStart()
{
	// Animation Start
	DirCheck("Turn");
}
void Soldier_Blue::MoveStopUpdate(float _Time)
{
	if (true == HitAction)
	{
		ChangeState(Soldier_BlueState::HIT);
		return;
	}

	if (AnimationRender->IsAnimationEnd())
	{
		ChangeState(Soldier_BlueState::MOVE);
		return;
	}
}
void Soldier_Blue::MoveStopEnd()
{
	IsTurn = false;
}

///////////////////////////////////////////////////////  Jump  ///////////////////////////////////////////////////////

void Soldier_Blue::JumpStart()
{
	MoveDir.y += -650.0f;

	DirCheck("Jump");
}
void Soldier_Blue::JumpUpdate(float _Time)
{
	if (true == HitAction)
	{
		ChangeState(Soldier_BlueState::HIT);
		return;
	}

	if (true == MoveDirect)
	{
		SetMove(float4::Left * MoveSpeed * _Time);
	}
	else if (false == MoveDirect)
	{
		SetMove(float4::Right * MoveSpeed * _Time);
	}

	if (RGB(0, 248, 0) == ColMap->GetPixelColor(NextPos, RGB(0, 0, 0))
		|| RGB(74, 65, 42) == ColMap->GetPixelColor(NextPos, RGB(0, 0, 0)))
	{
		IsGravityPlus = false;
		ChangeState(Soldier_BlueState::MOVE);
		return;
	}

	DirCheck("Jump");
}
void Soldier_Blue::JumpEnd()
{
	IsGravityPlus = true;
	IsJump = false;
}

void Soldier_Blue::JumpWallStart()
{
	MoveDir.y += -650.0f;

	DirCheck("Jump");
}
void Soldier_Blue::JumpWallUpdate(float _Time)
{
	if (true == HitAction)
	{
		ChangeState(Soldier_BlueState::HIT);
		return;
	}

	if (true == MoveDirect)
	{
		SetMove(float4::Left * MoveSpeed * _Time);
	}
	else if (false == MoveDirect)
	{
		SetMove(float4::Right * MoveSpeed * _Time);
	}

	if (RGB(0, 248, 0) == ColMap->GetPixelColor(NextPos, RGB(0, 0, 0))
		|| RGB(74, 65, 42) == ColMap->GetPixelColor(NextPos, RGB(0, 0, 0)))
	{
		IsGravityPlus = false;
		ChangeState(Soldier_BlueState::MOVE);
		return;
	}

	DirCheck("Jump");
}
void Soldier_Blue::JumpWallEnd()
{
	IsGravityPlus = true;
	IsJump = false;
}

///////////////////////////////////////////////////////  Ambush  ///////////////////////////////////////////////////////

void Soldier_Blue::AmbushStart()
{
	if (1 == AmbushJump)
	{
		MoveDir.y += -1350.0f;
		AmbushJump = 0;
	}
	
	AnimationRender->ChangeAnimation("Ambush");
}
void Soldier_Blue::AmbushUpdate(float _Time)
{
	if (true == AnimationRender->IsAnimationEnd())
	{
		BodyCollision->On();
	}

	if (true == HitAction)
	{
		ChangeState(Soldier_BlueState::HIT);
		return;
	}

	if (1.0f <= AmbushTime)
	{
		float4 LandPos = GetPos() + (float4::Down * 5);

		if (AmbushTime && RGB(0, 248, 0) == ColMap->GetPixelColor(LandPos, RGB(0, 0, 0))
			|| AmbushTime && RGB(74, 65, 42) == ColMap->GetPixelColor(LandPos, RGB(0, 0, 0)))
		{
			IsAmbush = false;
			IsGravityPlus = false;
			ChangeState(Soldier_BlueState::MOVE);
			return;
		}
	}
}
void Soldier_Blue::AmbushEnd()
{
}

///////////////////////////////////////////////////////  Hit  ///////////////////////////////////////////////////////

void Soldier_Blue::HitStart()
{
	HitActionCount = 0;

	HitDir = Player::MainPlayer->GetDir().data();

	IsGravityPlus = false;

	MoveDir.y = 0.0f;
	MoveDir.y += -900.0f;

	BodyCollision->Off();

	MoveSpeed = 250.0f;

	IsJump = true;
}
void Soldier_Blue::HitUpdate(float _Time)
{
	IsTurn = false;

	if ("_L" == HitDir)
	{
		AnimationRender->ChangeAnimation("Hit_R");
		SetMove(float4::Left * MoveSpeed * _Time);
	}
	else if ("_R" == HitDir)
	{
		AnimationRender->ChangeAnimation("Hit_L");
		SetMove(float4::Right * MoveSpeed * _Time);
	}

	HitTime += _Time;

	if (0.5f <= HitTime)
	{
		Kill();
	}
}
void Soldier_Blue::HitEnd()
{
}