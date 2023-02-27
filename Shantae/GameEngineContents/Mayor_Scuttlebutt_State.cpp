#include "Mayor_Scuttlebutt.h"

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
	default:
		break;
	}

	switch (PrevState)
	{
	case Mayor_ScuttlebuttState::IDLE:
		IdleEnd();
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
	default:
		break;
	}
}

void Mayor_Scuttlebutt::IdleStart()
{

}
void Mayor_Scuttlebutt::IdleUpdate(float _Time)
{

}
void Mayor_Scuttlebutt::IdleEnd()
{

}