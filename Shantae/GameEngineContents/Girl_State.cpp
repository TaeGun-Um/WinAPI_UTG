#include "Girl.h"

#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineRender.h>

void Girl::ChangeState(GirlState _State)
{
	GirlState NextState = _State;
	GirlState PrevState = StateValue;

	StateValue = NextState;

	switch (NextState)
	{
	case GirlState::IDLE:
		IdleStart();
		break;
	case GirlState::MOVE:
		MoveStart();
		break;
	case GirlState::RUN:
		RunStart();
		break;
	default:
		break;
	}

	switch (PrevState)
	{
	case GirlState::IDLE:
		IdleEnd();
		break;
	case GirlState::MOVE:
		MoveEnd();
		break;
	case GirlState::RUN:
		RunEnd();
		break;
	default:
		break;
	}
}

void Girl::UpdateState(float _Time)
{
	switch (StateValue)
	{
	case GirlState::IDLE:
		IdleUpdate(_Time);
		break;
	case GirlState::MOVE:
		MoveUpdate(_Time);
		break;
	case GirlState::RUN:
		RunUpdate(_Time);
		break;
	default:
		break;
	}
}

void Girl::IdleStart()
{
	DirCheck("Idle");
}
void Girl::IdleUpdate(float _Time)
{
	MoveTime += _Time;

	if (true == IsTurn && 2.0f <= MoveTime)
	{
		MoveDirect = false;
		MoveTime = 0.0f;
		ChangeState(GirlState::MOVE);
		return;
	}

	if (2.0f <= MoveTime)
	{
		MoveDirect = true;
		MoveTime = 0.0f;
		ChangeState(GirlState::MOVE);
		return;
	}

	if (true == IsRun)
	{
		ChangeState(GirlState::RUN);
		return;
	}
	if (GameEngineInput::IsDown("MonsterTest"))
	{
		ChangeState(GirlState::RUN);
		return;
	}
}
void Girl::IdleEnd()
{

}

void Girl::MoveStart()
{
	DirCheck("Move");
}
void Girl::MoveUpdate(float _Time)
{
	if (true == MoveDirect)
	{
		if (GetPos().x >= LeftMovePos.x)
		{
			SetMove(float4::Left * 90.0f * _Time);
		}
		else
		{
			IsTurn = true;
			ChangeState(GirlState::IDLE);
			return;
		}
	}
	else if (false == MoveDirect)
	{
		if (GetPos().x <= CurrentPos.x)
		{
			SetMove(float4::Right * 90.0f * _Time);
		}
		else
		{
			IsTurn = false;
			ChangeState(GirlState::IDLE);
			return;
		}
	}

}
void Girl::MoveEnd()
{
}

void Girl::RunStart()
{
	AnimationRender->ChangeAnimation("Run");
}
void Girl::RunUpdate(float _Time)
{
	SetMove(float4::Left * 400.0f * _Time);
}
void Girl::RunEnd()
{
}