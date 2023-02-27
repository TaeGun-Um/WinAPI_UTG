#include "Mayor_Scuttlebutt.h"

#include <GameEngineCore/GameEngineRender.h>

void Mayor_Scuttlebutt::ChangeState(Mayor_ScuttlebuttState _State)
{
	Mayor_ScuttlebuttState NextState = _State;
	Mayor_ScuttlebuttState PrevState = StateValue;

	StateValue = NextState;

	switch (NextState)
	{
	case Mayor_ScuttlebuttState::IDLE:
		IdleStart();
		break;
	case Mayor_ScuttlebuttState::TURN:
		TurnStart();
		break;
	default:
		break;
	}

	switch (PrevState)
	{
	case Mayor_ScuttlebuttState::IDLE:
		IdleEnd();
		break;
	case Mayor_ScuttlebuttState::TURN:
		TurnEnd();
		break;
	default:
		break;
	}
}

void Mayor_Scuttlebutt::UpdateState(float _Time)
{
	switch (StateValue)
	{
	case Mayor_ScuttlebuttState::IDLE:
		IdleUpdate(_Time);
		break;
	case Mayor_ScuttlebuttState::TURN:
		TurnUpdate(_Time);
		break;
	default:
		break;
	}
}

void Mayor_Scuttlebutt::IdleStart()
{
	DirCheck("Idle");
}
void Mayor_Scuttlebutt::IdleUpdate(float _Time)
{
	if (true == Isturn)
	{
		ChangeState(Mayor_ScuttlebuttState::TURN);
		return;
	}

	DirCheck("Idle");
}
void Mayor_Scuttlebutt::IdleEnd()
{

}

void Mayor_Scuttlebutt::TurnStart()
{
	Isturn = false;
	DirCheck("Turn");
}
void Mayor_Scuttlebutt::TurnUpdate(float _Time)
{
	if (true == AnimationRender->IsAnimationEnd())
	{
		ChangeState(Mayor_ScuttlebuttState::IDLE);
		return;
	}
}
void Mayor_Scuttlebutt::TurnEnd()
{

}