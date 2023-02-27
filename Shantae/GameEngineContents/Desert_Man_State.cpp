#include "Desert_Man.h"

#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineRender.h>

void Desert_Man::ChangeState(Desert_ManState _State)
{
	Desert_ManState NextState = _State;
	Desert_ManState PrevState = StateValue;

	StateValue = NextState;

	switch (NextState)
	{
	case Desert_ManState::IDLE:
		IdleStart();
		break;
	case Desert_ManState::MOVE:
		MoveStart();
		break;
	case Desert_ManState::TURN:
		TurnStart();
		break;
	case Desert_ManState::RUN:
		RunStart();
		break;
	default:
		break;
	}

	switch (PrevState)
	{
	case Desert_ManState::IDLE:
		IdleEnd();
		break;
	case Desert_ManState::MOVE:
		MoveEnd();
		break;
	case Desert_ManState::TURN:
		TurnEnd();
		break;
	case Desert_ManState::RUN:
		RunEnd();
		break;
	default:
		break;
	}
}

void Desert_Man::UpdateState(float _Time)
{
	switch (StateValue)
	{
	case Desert_ManState::IDLE:
		IdleUpdate(_Time);
		break;
	case Desert_ManState::MOVE:
		MoveUpdate(_Time);
		break;
	case Desert_ManState::TURN:
		TurnUpdate(_Time);
		break;
	case Desert_ManState::RUN:
		RunUpdate(_Time);
		break;
	default:
		break;
	}
}

void Desert_Man::IdleStart()
{
	DirCheck("Idle");
}
void Desert_Man::IdleUpdate(float _Time)
{
	MoveTime += _Time;

	if (true == IsTurn && 2.0f <= MoveTime)
	{
		MoveDirect = false;
		MoveTime = 0.0f;
		ChangeState(Desert_ManState::TURN);
		return;
	}

	if (2.0f <= MoveTime)
	{
		MoveDirect = true;
		MoveTime = 0.0f;
		ChangeState(Desert_ManState::TURN);
		return;
	}

	if (true == IsRun)
	{
		ChangeState(Desert_ManState::RUN);
		return;
	}
	if (GameEngineInput::IsDown("MonsterTest"))
	{
		ChangeState(Desert_ManState::RUN);
		return;
	}
}
void Desert_Man::IdleEnd()
{

}

void Desert_Man::MoveStart()
{
	DirCheck("Move");
}
void Desert_Man::MoveUpdate(float _Time)
{
	if (true == MoveDirect)
	{
		if (GetPos().x >= LeftMovePos.x)
		{
			SetMove(float4::Left * 70 * _Time);
		}
		else
		{
			IsTurn = true;
			ChangeState(Desert_ManState::IDLE);
			return;
		}
	}
	else if (false == MoveDirect)
	{
		if (GetPos().x <= CurrentPos.x)
		{
			SetMove(float4::Right * 70 * _Time);
		}
		else
		{
			IsTurn = false;
			ChangeState(Desert_ManState::IDLE);
			return;
		}
	}

}
void Desert_Man::MoveEnd()
{
}

void Desert_Man::TurnStart()
{
	if (1 == Pass)
	{
		Pass = 0;
		DirCheck("Idle");
	}
	else if (0 == Pass)
	{
		DirCheck("Turn");
	}
}
void Desert_Man::TurnUpdate(float _Time)
{
	if (true == AnimationRender->IsAnimationEnd())
	{
		ChangeState(Desert_ManState::MOVE);
		return;
	}
}
void Desert_Man::TurnEnd()
{

}

void Desert_Man::RunStart()
{
	AnimationRender->ChangeAnimation("Run");
}
void Desert_Man::RunUpdate(float _Time)
{
	SetMove(float4::Left * RunSpeed * _Time);
}
void Desert_Man::RunEnd()
{}