#include "Town_Guard.h"

#include <GameEngineCore/GameEngineRender.h>

void Town_Guard::ChangeState(Town_GuardState _State)
{
	Town_GuardState NextState = _State;
	Town_GuardState PrevState = StateValue;

	StateValue = NextState;

	switch (NextState)
	{
	case Town_GuardState::IDLE:
		IdleStart();
		break;
	case Town_GuardState::TURN:
		TurnStart();
		break;
	default:
		break;
	}

	switch (PrevState)
	{
	case Town_GuardState::IDLE:
		IdleEnd();
		break;
	case Town_GuardState::TURN:
		TurnEnd();
		break;
	default:
		break;
	}
}

void Town_Guard::UpdateState(float _Time)
{
	switch (StateValue)
	{
	case Town_GuardState::IDLE:
		IdleUpdate(_Time);
		break;
	case Town_GuardState::TURN:
		TurnUpdate(_Time);
		break;
	default:
		break;
	}
}

void Town_Guard::IdleStart()
{
	DirCheck("Idle");
}
void Town_Guard::IdleUpdate(float _Time)
{
	if (true == Isturn)
	{
		ChangeState(Town_GuardState::TURN);
		return;
	}

	DirCheck("Idle");
}
void Town_Guard::IdleEnd()
{

}

void Town_Guard::TurnStart()
{
	Isturn = false;
	DirCheck("Turn");
}
void Town_Guard::TurnUpdate(float _Time)
{
	if (true == AnimationRender->IsAnimationEnd())
	{
		ChangeState(Town_GuardState::IDLE);
		return;
	}
}
void Town_Guard::TurnEnd()
{

}