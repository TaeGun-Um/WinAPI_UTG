#include "Town_Guard.h"

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
	default:
		break;
	}

	switch (PrevState)
	{
	case Town_GuardState::IDLE:
		IdleEnd();
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
	default:
		break;
	}
}

void Town_Guard::IdleStart()
{

}
void Town_Guard::IdleUpdate(float _Time)
{

}
void Town_Guard::IdleEnd()
{

}