#include "SkyNPC.h"

#include <GameEngineCore/GameEngineRender.h>

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
	case SkyNPCState::TURN:
		TurnStart();
		break;
	default:
		break;
	}

	switch (PrevState)
	{
	case SkyNPCState::IDLE:
		IdleEnd();
		break;
	case SkyNPCState::TURN:
		TurnEnd();
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
	case SkyNPCState::TURN:
		TurnUpdate(_Time);
		break;
	default:
		break;
	}
}

void SkyNPC::IdleStart()
{
	DirCheck("Idle");
}
void SkyNPC::IdleUpdate(float _Time)
{
	if (true == Isturn)
	{
		ChangeState(SkyNPCState::TURN);
		return;
	}

	DirCheck("Idle");
}
void SkyNPC::IdleEnd()
{

}

void SkyNPC::TurnStart()
{
	Isturn = false;
	DirCheck("Turn");
}
void SkyNPC::TurnUpdate(float _Time)
{
	if (true == AnimationRender->IsAnimationEnd())
	{
		ChangeState(SkyNPCState::IDLE);
		return;
	}
}
void SkyNPC::TurnEnd()
{

}