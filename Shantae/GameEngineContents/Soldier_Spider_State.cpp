#include "Soldier_Spider.h"

#include <GameEngineCore/GameEngineCollision.h>

#include "ContentsEnum.h"
#include "Player.h"

// Player State º¯°æ
void Soldier_Spider::ChangeState(Soldier_SpiderState _State)
{
	Soldier_SpiderState NextState = _State;
	Soldier_SpiderState PrevState = StateValue;

	StateValue = NextState;

	switch (NextState)
	{
	case Soldier_SpiderState::IDLE:
		IdleStart();
		break;
	case Soldier_SpiderState::MOVE:
		MoveStart();
		break;
	case Soldier_SpiderState::ATTACK:
		AttackStart();
		break;
	case Soldier_SpiderState::HIT:
		HitStart();
		break;
	default:
		break;
	}

	switch (PrevState)
	{
	case Soldier_SpiderState::IDLE:
		IdleEnd();
		break;
	case Soldier_SpiderState::MOVE:
		MoveEnd();
		break;
	case Soldier_SpiderState::ATTACK:
		AttackEnd();
		break;
	case Soldier_SpiderState::HIT:
		HitEnd();
		break;
	default:
		break;
	}
}

void Soldier_Spider::UpdateState(float _Time)
{
	switch (StateValue)
	{
	case Soldier_SpiderState::IDLE:
		IdleUpdate(_Time);
		break;
	case Soldier_SpiderState::MOVE:
		MoveUpdate(_Time);
		break;
	case Soldier_SpiderState::ATTACK:
		AttackUpdate(_Time);
		break;
	case Soldier_SpiderState::HIT:
		HitUpdate(_Time);
		break;
	default:
		break;
	}
}

/////////////////////////////////////////////////////// States ///////////////////////////////////////////////////////

///////////////////////////////////////////////////////  Idle  ///////////////////////////////////////////////////////

void Soldier_Spider::IdleStart()
{
	// Animation Start
	DirCheck("Idle");
}
void Soldier_Spider::IdleUpdate(float _Time)
{
	MoveSpeed = 0.0f;
	DirCheck("Idle");
}
void Soldier_Spider::IdleEnd()
{
}

///////////////////////////////////////////////////////  Shoot  ///////////////////////////////////////////////////////

void Soldier_Spider::MoveStart()
{
	// Animation Start
	MoveSpeed = 300.0f;
}
void Soldier_Spider::MoveUpdate(float _Time)
{
	AttackDelay += _Time;

	if (true == HitAction)
	{
		ChangeState(Soldier_SpiderState::HIT);
		return;
	}

	if (true == IsAttack && 0.5f < AttackDelay)
	{
		ChangeState(Soldier_SpiderState::ATTACK);
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

	DirCheck("Move");
}
void Soldier_Spider::MoveEnd()
{
	AttackDelay = 0.0f;
}

///////////////////////////////////////////////////////  ReLoad  ///////////////////////////////////////////////////////

void Soldier_Spider::AttackStart()
{
	// Animation Start
	DirCheck("Attack");
}
void Soldier_Spider::AttackUpdate(float _Time)
{
	if (true == AnimationRender->IsAnimationEnd())
	{
		IsAttack = false;
		AttackCollision->Off();
		ChangeState(Soldier_SpiderState::MOVE);
		return;
	}

	if (15 == AnimationRender->GetFrame())
	{
		AttackCollision->On();
	}

}
void Soldier_Spider::AttackEnd()
{
}

///////////////////////////////////////////////////////  Hit  ///////////////////////////////////////////////////////

void Soldier_Spider::HitStart()
{
	CollisionGround = false;
	IsGravity = false;

	MoveDir.y += 10.0f;

	BodyCollision->Off();

	DirCheck("Hit");
}

void Soldier_Spider::HitUpdate(float _Time)
{
	if ("_L" == DirString)
	{
		SetMove(float4::Left * 250.0f * _Time);
	}
	else if ("_R" == DirString)
	{
		SetMove(float4::Right * 250.0f * _Time);
	}

	HitTime += _Time;

	if (0.5f <= HitTime)
	{
		Kill();
		return;
	}
}
void Soldier_Spider::HitEnd()
{
}