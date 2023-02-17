#include "Soldier_Red.h"

#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineCollision.h>

#include "Player.h"
#include "ContentsEnum.h"

// Player State º¯°æ
void Soldier_Red::ChangeState(Soldier_RedState _State)
{
	Soldier_RedState NextState = _State;
	Soldier_RedState PrevState = StateValue;

	StateValue = NextState;

	switch (NextState)
	{
	case Soldier_RedState::MOVE:
		MoveStart();
		break;
	case Soldier_RedState::MOVESTOP:
		MoveStopStart();
		break;
	case Soldier_RedState::JUMP:
		IsGravityPlus = false;
		JumpStart();
		break;
	case Soldier_RedState::JUMPWALL:
		IsGravityPlus = false;
		JumpWallStart();
		break;
	case Soldier_RedState::AMBUSH:
		AmbushStart();
		break;
	case Soldier_RedState::HIT:
		if (0 == HP)
		{
			IsGravityPlus = false;
		}
		HitStart();
		break;
	default:
		break;
	}

	switch (PrevState)
	{
	case Soldier_RedState::MOVE:
		MoveEnd();
		break;
	case Soldier_RedState::MOVESTOP:
		MoveStopEnd();
		break;
	case Soldier_RedState::JUMP:
		IsGravityPlus = false;
		JumpEnd();
		break;
	case Soldier_RedState::JUMPWALL:
		IsGravityPlus = false;
		JumpWallEnd();
		break;
	case Soldier_RedState::AMBUSH:
		AmbushEnd();
		break;
	case Soldier_RedState::HIT:
		if (0 == HP)
		{
			IsGravityPlus = false;
		}
		HitEnd();
		break;
	default:
		break;
	}
}

void Soldier_Red::UpdateState(float _Time)
{
	switch (StateValue)
	{
	case Soldier_RedState::MOVE:
		MoveUpdate(_Time);
		break;
	case Soldier_RedState::MOVESTOP:
		MoveStopUpdate(_Time);
		break;
	case Soldier_RedState::JUMP:
		IsGravityPlus = false;
		JumpUpdate(_Time);
		break;
	case Soldier_RedState::JUMPWALL:
		IsGravityPlus = false;
		JumpWallUpdate(_Time);
		break;
	case Soldier_RedState::AMBUSH:
		AmbushUpdate(_Time);
		break;
	case Soldier_RedState::HIT:
		if (0 == HP)
		{
			IsGravityPlus = false;
		}
		HitUpdate(_Time);
		break;
	default:
		break;
	}
}

/////////////////////////////////////////////////////// States ///////////////////////////////////////////////////////

///////////////////////////////////////////////////////  Move  ///////////////////////////////////////////////////////

void Soldier_Red::MoveStart()
{
	// Animation Start
	DirCheck("Move");
}
void Soldier_Red::MoveUpdate(float _Time)
{
	if (true == HitAction)
	{
		ChangeState(Soldier_RedState::HIT);
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
		ChangeState(Soldier_RedState::MOVESTOP);
		return;
	}

	if (true == IsJump)
	{
		ChangeState(Soldier_RedState::JUMP);
		return;
	}

	DirCheck("Move");
}
void Soldier_Red::MoveEnd()
{
}

///////////////////////////////////////////////////////  MoveStop  ///////////////////////////////////////////////////////

void Soldier_Red::MoveStopStart()
{
	// Animation Start
	DirCheck("Turn");
}
void Soldier_Red::MoveStopUpdate(float _Time)
{
	if (true == HitAction)
	{
		ChangeState(Soldier_RedState::HIT);
		return;
	}

	if (AnimationRender->IsAnimationEnd())
	{
		ChangeState(Soldier_RedState::MOVE);
		return;
	}
}
void Soldier_Red::MoveStopEnd()
{
	IsTurn = false;
}

///////////////////////////////////////////////////////  Jump  ///////////////////////////////////////////////////////

void Soldier_Red::JumpStart()
{
	MoveDir.y += -650.0f;

	DirCheck("Jump");
}
void Soldier_Red::JumpUpdate(float _Time)
{
	if (true == HitAction)
	{
		ChangeState(Soldier_RedState::HIT);
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
		ChangeState(Soldier_RedState::MOVE);
		return;
	}

	DirCheck("Jump");
}
void Soldier_Red::JumpEnd()
{
	IsGravityPlus = true;
	IsJump = false;
}

void Soldier_Red::JumpWallStart()
{
	MoveDir.y += -650.0f;

	DirCheck("Jump");
}
void Soldier_Red::JumpWallUpdate(float _Time)
{
	if (true == HitAction)
	{
		ChangeState(Soldier_RedState::HIT);
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
		ChangeState(Soldier_RedState::MOVE);
		return;
	}

	DirCheck("Jump");
}
void Soldier_Red::JumpWallEnd()
{
	IsGravityPlus = true;
	IsJump = false;
}

///////////////////////////////////////////////////////  Ambush  ///////////////////////////////////////////////////////

void Soldier_Red::AmbushStart()
{
	if (1 == AmbushJump)
	{
		MoveDir.y += -1350.0f;
		AmbushJump = 0;
	}

	AnimationRender->ChangeAnimation("Ambush");
}
void Soldier_Red::AmbushUpdate(float _Time)
{
	if (true == AnimationRender->IsAnimationEnd())
	{
		BodyCollision->On();
	}

	if (true == HitAction)
	{
		IsAmbush = false;
		IsGravityPlus = false;
		ChangeState(Soldier_RedState::HIT);
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
			ChangeState(Soldier_RedState::MOVE);
			return;
		}
	}
}
void Soldier_Red::AmbushEnd()
{
}

///////////////////////////////////////////////////////  Hit  ///////////////////////////////////////////////////////

void Soldier_Red::HitStart()
{
	HitDir = Player::MainPlayer->GetDir().data();

	IsGravityPlus = false;

	MoveDir.y = 0.0f;

	if (5 == HP)
	{
		MoveDir.y -= 300.0f;
	}
	else if (0 == HP)
	{
		MoveDir.y -= 900.0f;
	}

	BodyCollision->Off();

	MoveSpeed = 250.0f;

	IsJump = true;
}
void Soldier_Red::HitUpdate(float _Time)
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

	if (RGB(0, 248, 0) == ColMap->GetPixelColor(NextPos, RGB(0, 0, 0))
		|| RGB(74, 65, 42) == ColMap->GetPixelColor(NextPos, RGB(0, 0, 0)))
	{
		MoveSpeed = 0.0f;
	}

	HitTime += _Time;

	if (5 == HP && 0.4f <= HitTime && RGB(0, 248, 0) == ColMap->GetPixelColor(NextPos, RGB(0, 0, 0))
		|| 5 == HP && 0.4f <= HitTime && RGB(74, 65, 42) == ColMap->GetPixelColor(NextPos, RGB(0, 0, 0)))
	{
		HitTime = 0.0f;
		BodyCollision->On();
		IsJump = false;
		HitAction = false;
		ChangeState(Soldier_RedState::MOVE);
		return;
	}
	else if (0 == HP && 0.5f <= HitTime)		 
	{
		Kill();
	}
}
void Soldier_Red::HitEnd()
{
}