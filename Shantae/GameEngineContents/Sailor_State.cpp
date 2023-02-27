#include "Sailor.h"

#include <GameEngineCore/GameEngineRender.h>

void Sailor::ChangeState(SailorState _State)
{
	SailorState NextState = _State;
	SailorState PrevState = StateValue;

	StateValue = NextState;

	switch (NextState)
	{
	case SailorState::IDLE:
		IdleStart();
		break;
	case SailorState::TURN:
		TurnStart();
		break;
	default:
		break;
	}

	switch (PrevState)
	{
	case SailorState::IDLE:
		IdleEnd();
		break;
	case SailorState::TURN:
		TurnEnd();
		break;
	default:
		break;
	}
}

void Sailor::UpdateState(float _Time)
{
	switch (StateValue)
	{
	case SailorState::IDLE:
		IdleUpdate(_Time);
		break;
	case SailorState::TURN:
		TurnUpdate(_Time);
		break;
	default:
		break;
	}
}

void Sailor::IdleStart()
{
	DirCheck("Idle");
}
void Sailor::IdleUpdate(float _Time)
{
	if (true == Isturn)
	{
		ChangeState(SailorState::TURN);
		return;
	}

	DirCheck("Idle");
}
void Sailor::IdleEnd()
{

}

void Sailor::TurnStart()
{
	Isturn = false;
	DirCheck("Turn");
}
void Sailor::TurnUpdate(float _Time)
{
	if (true == AnimationRender->IsAnimationEnd())
	{
		ChangeState(SailorState::IDLE);
		return;
	}
}
void Sailor::TurnEnd()
{

}