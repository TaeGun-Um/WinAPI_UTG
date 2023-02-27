#include "SkyNPC.h"

void SkyNPC::ChangeState(SkyNPCState _State)
{
	SkyNPCState NextState = _State;
	SkyNPCState PrevState = StateValue;

	StateValue = NextState;

	switch (NextState)
	{
	case SkyNPCState::IDLE:
		IdleStart();
		break;
	default:
		break;
	}

	switch (PrevState)
	{
	case SkyNPCState::IDLE:
		IdleEnd();
		break;
	default:
		break;
	}
}

void SkyNPC::UpdateState(float _Time)
{
	switch (StateValue)
	{
	case SkyNPCState::IDLE:
		IdleUpdate(_Time);
		break;
	default:
		break;
	}
}

void SkyNPC::IdleStart()
{

}
void SkyNPC::IdleUpdate(float _Time)
{

}
void SkyNPC::IdleEnd()
{

}