#include "Stylist.h"

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
	default:
		break;
	}

	switch (PrevState)
	{
	case StylistState::IDLE:
		IdleEnd();
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
	default:
		break;
	}
}

void Stylist::IdleStart()
{

}
void Stylist::IdleUpdate(float _Time)
{

}
void Stylist::IdleEnd()
{

}