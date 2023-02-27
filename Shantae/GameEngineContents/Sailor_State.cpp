#include "Sailor.h"

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
	default:
		break;
	}

	switch (PrevState)
	{
	case SailorState::IDLE:
		IdleEnd();
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
	default:
		break;
	}
}

void Sailor::IdleStart()
{

}
void Sailor::IdleUpdate(float _Time)
{

}
void Sailor::IdleEnd()
{

}