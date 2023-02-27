#include "Squidsmith.h"

void Squidsmith::ChangeState(SquidsmithState _State)
{
	SquidsmithState NextState = _State;
	SquidsmithState PrevState = StateValue;

	StateValue = NextState;

	switch (NextState)
	{
	case SquidsmithState::IDLE:
		IdleStart();
		break;
	default:
		break;
	}

	switch (PrevState)
	{
	case SquidsmithState::IDLE:
		IdleEnd();
		break;
	default:
		break;
	}
}

void Squidsmith::UpdateState(float _Time)
{
	switch (StateValue)
	{
	case SquidsmithState::IDLE:
		IdleUpdate(_Time);
		break;
	default:
		break;
	}
}

void Squidsmith::IdleStart()
{

}
void Squidsmith::IdleUpdate(float _Time)
{

}
void Squidsmith::IdleEnd()
{

}