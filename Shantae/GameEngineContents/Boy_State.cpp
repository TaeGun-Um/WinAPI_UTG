#include "Boy.h"

#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineRender.h>

void Boy::ChangeState(BoyState _State)
{
	BoyState NextState = _State;
	BoyState PrevState = StateValue;

	StateValue = NextState;

	switch (NextState)
	{
	case BoyState::IDLE:
		IdleStart();
		break;
	case BoyState::MOVE:
		MoveStart();
		break;
	case BoyState::RUN:
		RunStart();
		break;
	default:
		break;
	}

	switch (PrevState)
	{
	case BoyState::IDLE:
		IdleEnd();
		break;
	case BoyState::MOVE:
		MoveEnd();
		break;
	case BoyState::RUN:
		RunEnd();
		break;
	default:
		break;
	}
}

void Boy::UpdateState(float _Time)
{
	switch (StateValue)
	{
	case BoyState::IDLE:
		IdleUpdate(_Time);
		break;
	case BoyState::MOVE:
		MoveUpdate(_Time);
		break;
	case BoyState::RUN:
		RunUpdate(_Time);
		break;
	default:
		break;
	}
}

void Boy::IdleStart()
{
	DirCheck("Idle");
}
void Boy::IdleUpdate(float _Time)
{
	MoveTime += _Time;

	if (true == IsTurn && 1.5f <= MoveTime)
	{
		MoveDirect = false;
		MoveTime = 0.0f;
		ChangeState(BoyState::MOVE);
		return;
	}

	if (1.5f <= MoveTime)
	{
		MoveDirect = true;
		MoveTime = 0.0f;
		ChangeState(BoyState::MOVE);
		return;
	}

	if (true == IsRun)
	{
		ChangeState(BoyState::RUN);
		return;
	}
	if (GameEngineInput::IsDown("MonsterTest"))
	{
		ChangeState(BoyState::RUN);
		return;
	}
}
void Boy::IdleEnd()
{

}

void Boy::MoveStart()
{
	DirCheck("Move");
}
void Boy::MoveUpdate(float _Time)
{
	if (true == MoveDirect)
	{
		if (GetPos().x >= LeftMovePos.x)
		{
			SetMove(float4::Left * 100.0f * _Time);
		}
		else
		{
			IsTurn = true;
			ChangeState(BoyState::IDLE);
			return;
		}
	}
	else if (false == MoveDirect)
	{
		if (GetPos().x <= CurrentPos.x)
		{
			SetMove(float4::Right * 100.0f * _Time);
		}
		else
		{
			IsTurn = false;
			ChangeState(BoyState::IDLE);
			return;
		}
	}
	
}
void Boy::MoveEnd()
{
}

void Boy::RunStart()
{
	AnimationRender->ChangeAnimation("Run");
}
void Boy::RunUpdate(float _Time)
{
	SetMove(float4::Left * RunSpeed * _Time);
}
void Boy::RunEnd()
{}