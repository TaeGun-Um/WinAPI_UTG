#include "Desert_Man.h"

void Desert_Man::ChangeState(Desert_ManState _State)
{
	Desert_ManState NextState = _State;
	Desert_ManState PrevState = StateValue;

	StateValue = NextState;

	switch (NextState)
	{
	case Desert_ManState::IDLE:
		IdleStart();
		break;
	default:
		break;
	}

	switch (PrevState)
	{
	case Desert_ManState::IDLE:
		IdleEnd();
		break;
	default:
		break;
	}
}

void Desert_Man::UpdateState(float _Time)
{
	switch (StateValue)
	{
	case Desert_ManState::IDLE:
		IdleUpdate(_Time);
		break;
	default:
		break;
	}
}

void Desert_Man::IdleStart()
{

}
void Desert_Man::IdleUpdate(float _Time)
{

}
void Desert_Man::IdleEnd()
{

}