#include "Girl.h"

void Girl::ChangeState(GirlState _State)
{
	GirlState NextState = _State;
	GirlState PrevState = StateValue;

	StateValue = NextState;

	switch (NextState)
	{
	case GirlState::IDLE:
		IdleStart();
		break;
	default:
		break;
	}

	switch (PrevState)
	{
	case GirlState::IDLE:
		IdleEnd();
		break;
	default:
		break;
	}
}

void Girl::UpdateState(float _Time)
{
	switch (StateValue)
	{
	case GirlState::IDLE:
		IdleUpdate(_Time);
		break;
	default:
		break;
	}
}

void Girl::IdleStart()
{

}
void Girl::IdleUpdate(float _Time)
{

}
void Girl::IdleEnd()
{

}