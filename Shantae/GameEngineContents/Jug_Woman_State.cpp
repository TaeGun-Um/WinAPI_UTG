#include "Jug_Woman.h"

#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineRender.h>

void Jug_Woman::ChangeState(Jug_WomanState _State)
{
	Jug_WomanState NextState = _State;
	Jug_WomanState PrevState = StateValue;

	StateValue = NextState;

	switch (NextState)
	{
	case Jug_WomanState::IDLE:
		IdleStart();
		break;
	case Jug_WomanState::MOVE:
		MoveStart();
		break;
	case Jug_WomanState::TURN:
		TurnStart();
		break;
	case Jug_WomanState::RUN:
		RunStart();
		break;
	default:
		break;
	}

	switch (PrevState)
	{
	case Jug_WomanState::IDLE:
		IdleEnd();
		break;
	case Jug_WomanState::MOVE:
		MoveEnd();
		break;
	case Jug_WomanState::TURN:
		TurnEnd();
		break;
	case Jug_WomanState::RUN:
		RunEnd();
		break;
	default:
		break;
	}
}

void Jug_Woman::UpdateState(float _Time)
{
	switch (StateValue)
	{
	case Jug_WomanState::IDLE:
		IdleUpdate(_Time);
		break;
	case Jug_WomanState::MOVE:
		MoveUpdate(_Time);
		break;
	case Jug_WomanState::TURN:
		TurnUpdate(_Time);
		break;
	case Jug_WomanState::RUN:
		RunUpdate(_Time);
		break;
	default:
		break;
	}
}

void Jug_Woman::IdleStart()
{
	DirCheck("Idle");
}
void Jug_Woman::IdleUpdate(float _Time)
{
	MoveTime += _Time;

	if (true == IsTurn && 1.7f <= MoveTime)
	{
		MoveDirect = false;
		MoveTime = 0.0f;
		ChangeState(Jug_WomanState::TURN);
		return;
	}

	if (1.7f <= MoveTime)
	{
		MoveDirect = true;
		MoveTime = 0.0f;
		ChangeState(Jug_WomanState::TURN);
		return;
	}

	if (true == IsRun)
	{
		ChangeState(Jug_WomanState::RUN);
		return;
	}
	if (GameEngineInput::IsDown("MonsterTest"))
	{
		ChangeState(Jug_WomanState::RUN);
		return;
	}
}
void Jug_Woman::IdleEnd()
{

}

void Jug_Woman::MoveStart()
{
	DirCheck("Move");
}
void Jug_Woman::MoveUpdate(float _Time)
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
			ChangeState(Jug_WomanState::IDLE);
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
			ChangeState(Jug_WomanState::IDLE);
			return;
		}
	}

}
void Jug_Woman::MoveEnd()
{
}

void Jug_Woman::TurnStart()
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
void Jug_Woman::TurnUpdate(float _Time)
{
	if (true == AnimationRender->IsAnimationEnd())
	{
		ChangeState(Jug_WomanState::MOVE);
		return;
	}
}
void Jug_Woman::TurnEnd()
{

}

void Jug_Woman::RunStart()
{
	AnimationRender->ChangeAnimation("Run");
}
void Jug_Woman::RunUpdate(float _Time)
{
	SetMove(float4::Left * 400.0f * _Time);
}
void Jug_Woman::RunEnd()
{}