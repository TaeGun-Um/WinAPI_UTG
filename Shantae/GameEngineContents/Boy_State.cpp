#include "Boy.h"

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
	default:
		break;
	}

	switch (PrevState)
	{
	case BoyState::IDLE:
		IdleEnd();
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
	default:
		break;
	}
}

void Boy::IdleStart()
{

}
void Boy::IdleUpdate(float _Time)
{

}
void Boy::IdleEnd()
{

}