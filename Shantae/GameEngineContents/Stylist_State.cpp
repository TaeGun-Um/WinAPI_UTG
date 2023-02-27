#include "Stylist.h"

#include <GameEngineCore/GameEngineRender.h>

void Stylist::ChangeState(StylistState _State)
{
	StylistState NextState = _State;
	StylistState PrevState = StateValue;

	StateValue = NextState;

	switch (NextState)
	{
	case StylistState::IDLE:
		IdleStart();
		break;
	case StylistState::MOVE:
		MoveStart();
		break;
	case StylistState::TURN:
		TurnStart();
		break;
	case StylistState::RUN:
		RunStart();
		break;
	default:
		break;
	}

	switch (PrevState)
	{
	case StylistState::IDLE:
		IdleEnd();
		break;
	case StylistState::MOVE:
		MoveEnd();
		break;
	case StylistState::TURN:
		TurnEnd();
		break;
	case StylistState::RUN:
		RunEnd();
		break;
	default:
		break;
	}
}

void Stylist::UpdateState(float _Time)
{
	switch (StateValue)
	{
	case StylistState::IDLE:
		IdleUpdate(_Time);
		break;
	case StylistState::MOVE:
		MoveUpdate(_Time);
		break;
	case StylistState::TURN:
		TurnUpdate(_Time);
		break;
	case StylistState::RUN:
		RunUpdate(_Time);
		break;
	default:
		break;
	}
}

void Stylist::IdleStart()
{
	DirCheck("Idle");
}
void Stylist::IdleUpdate(float _Time)
{
	MoveTime += _Time;

	if (true == IsTurn && 1.0f <= MoveTime)
	{
		MoveDirect = false;
		MoveTime = 0.0f;
		ChangeState(StylistState::TURN);
		return;
	}

	if (1.0f <= MoveTime)
	{
		MoveDirect = true;
		MoveTime = 0.0f;
		ChangeState(StylistState::TURN);
		return;
	}

	if (true == IsRun)
	{
		ChangeState(StylistState::RUN);
		return;
	}
}
void Stylist::IdleEnd()
{

}

void Stylist::MoveStart()
{
	DirCheck("Move");
}
void Stylist::MoveUpdate(float _Time)
{
	if (true == MoveDirect)
	{
		if (GetPos().x >= LeftMovePos.x)
		{
			SetMove(float4::Left * 300.0f * _Time);
		}
		else
		{
			IsTurn = true;
			ChangeState(StylistState::IDLE);
			return;
		}
	}
	else if (false == MoveDirect)
	{
		if (GetPos().x <= CurrentPos.x)
		{
			SetMove(float4::Right * 300.0f * _Time);
		}
		else
		{
			IsTurn = false;
			ChangeState(StylistState::IDLE);
			return;
		}
	}

}
void Stylist::MoveEnd()
{
}

void Stylist::TurnStart()
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
void Stylist::TurnUpdate(float _Time)
{
	if (true == AnimationRender->IsAnimationEnd())
	{
		ChangeState(StylistState::MOVE);
		return;
	}
}
void Stylist::TurnEnd()
{

}

void Stylist::RunStart()
{
	AnimationRender->ChangeAnimation("Run");
}
void Stylist::RunUpdate(float _Time)
{
	SetMove(float4::Left * 400.0f * _Time);
}
void Stylist::RunEnd()
{}