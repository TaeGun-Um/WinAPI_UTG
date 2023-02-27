#include "Jug_Woman.h"

void Jug_Woman::ChangeState(Jug_WomanState _State)
{
	Jug_WomanState NextState = _State;
	Jug_WomanState PrevState = StateValue;

	StateValue = NextState;

	switch (NextState)
	{
	case Jug_WomanState::IDLE:
		IdleStart();
		break;
	default:
		break;
	}

	switch (PrevState)
	{
	case Jug_WomanState::IDLE:
		IdleEnd();
		break;
	default:
		break;
	}
}

void Jug_Woman::UpdateState(float _Time)
{
	switch (StateValue)
	{
	case Jug_WomanState::IDLE:
		IdleUpdate(_Time);
		break;
	default:
		break;
	}
}

void Jug_Woman::IdleStart()
{

}
void Jug_Woman::IdleUpdate(float _Time)
{

}
void Jug_Woman::IdleEnd()
{

}