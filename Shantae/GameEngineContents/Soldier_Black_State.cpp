#include "Soldier_Black.h"

#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineCollision.h>

#include "ContentsEnum.h"
#include "Player.h"

// Player State º¯°æ
void Soldier_Black::ChangeState(Soldier_BlackState _State)
{
	Soldier_BlackState NextState = _State;
	Soldier_BlackState PrevState = StateValue;

	StateValue = NextState;

	switch (NextState)
	{
	case Soldier_BlackState::IDLE:
		IdleStart();
		break;
	case Soldier_BlackState::SHOOT:
		ShootStart();
		break;
	case Soldier_BlackState::RELOAD:
		ReloadStart();
		break;
	case Soldier_BlackState::HIT:
		HitStart();
		break;
	default:
		break;
	}

	switch (PrevState)
	{
	case Soldier_BlackState::IDLE:
		IdleEnd();
		break;
	case Soldier_BlackState::SHOOT:
		ShootEnd();
		break;
	case Soldier_BlackState::RELOAD:
		ReloadEnd();
		break;
	case Soldier_BlackState::HIT:
		HitEnd();
		break;
	default:
		break;
	}
}

void Soldier_Black::UpdateState(float _Time)
{
	switch (StateValue)
	{
	case Soldier_BlackState::IDLE:
		IdleUpdate(_Time);
		break;
	case Soldier_BlackState::SHOOT:
		ShootUpdate(_Time);
		break;
	case Soldier_BlackState::RELOAD:
		ReloadUpdate(_Time);
		break;
	case Soldier_BlackState::HIT:
		HitUpdate(_Time);
		break;
	default:
		break;
	}
}

/////////////////////////////////////////////////////// States ///////////////////////////////////////////////////////

///////////////////////////////////////////////////////  Idle  ///////////////////////////////////////////////////////

void Soldier_Black::IdleStart()
{
	// Animation Start
	DirCheck("Idle");
}
void Soldier_Black::IdleUpdate(float _Time)
{
	if (true == HitAction)
	{
		ChangeState(Soldier_BlackState::HIT);
		return;
	}

	ShootStartTime += _Time;

	if (2.0f <= ShootStartTime)
	{
		ShootCount = 3;
		ShootStartTime = 0.0f;
		ChangeState(Soldier_BlackState::SHOOT);
		return;
	}

	DirCheck("Idle");
}
void Soldier_Black::IdleEnd()
{
}

///////////////////////////////////////////////////////  Shoot  ///////////////////////////////////////////////////////

void Soldier_Black::ShootStart()
{
	// Animation Start
	DirCheck("Shoot");
	trace = false;
}
void Soldier_Black::ShootUpdate(float _Time)
{
	if (true == HitAction)
	{
		trace = true;
		ChangeState(Soldier_BlackState::HIT);
		return;
	}

	if (0 == ShootCount)
	{
		ChangeState(Soldier_BlackState::RELOAD);
		return;
	}

	ShootTime += _Time;

	if (0 < ShootCount && 0.2f <= ShootTime)
	{
		ShootTime = 0.0f;
		Shoot();
		--ShootCount;
		DirCheck("Shoot");
	}
}
void Soldier_Black::ShootEnd()
{
}

///////////////////////////////////////////////////////  ReLoad  ///////////////////////////////////////////////////////

void Soldier_Black::ReloadStart()
{
	// Animation Start
	DirCheck("ReLoad");
}
void Soldier_Black::ReloadUpdate(float _Time)
{
	if (true == HitAction)
	{
		trace = true;
		ChangeState(Soldier_BlackState::HIT);
		return;
	}

	if (true == AnimationRender->IsAnimationEnd())
	{
		trace = true;
		ChangeState(Soldier_BlackState::IDLE);
		return;
	}

	DirCheck("ReLoad");
}
void Soldier_Black::ReloadEnd()
{
}

///////////////////////////////////////////////////////  Hit  ///////////////////////////////////////////////////////

void Soldier_Black::HitStart()
{
	HitDir = Player::MainPlayer->GetDir().data();

	MoveDir.y += -900.0f;

	BodyCollision->Off();
}
void Soldier_Black::HitUpdate(float _Time)
{
	IsTurn = false;

	if ("_L" == HitDir)
	{
		AnimationRender->ChangeAnimation("Hit_R");
		SetMove(float4::Left * 250.0f * _Time);
	}
	else if ("_R" == HitDir)
	{
		AnimationRender->ChangeAnimation("Hit_L");
		SetMove(float4::Right * 250.0f * _Time);
	}

	HitTime += _Time;

	if (0.5f <= HitTime)
	{
		IsDeath = true;
		return;
	}
}
void Soldier_Black::HitEnd()
{
}