#include "Squidsmith.h"

#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineRender.h>

#include "Player.h"

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
	case SquidsmithState::TURN:
		TurnStart();
		break;
	case SquidsmithState::ACTION:
		ActionStart();
		break;
	default:
		break;
	}

	switch (PrevState)
	{
	case SquidsmithState::IDLE:
		IdleEnd();
		break;
	case SquidsmithState::TURN:
		TurnEnd();
		break;
	case SquidsmithState::ACTION:
		ActionEnd();
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
	case SquidsmithState::TURN:
		TurnUpdate(_Time);
		break;
	case SquidsmithState::ACTION:
		ActionUpdate(_Time);
		break;
	default:
		break;
	}
}

void Squidsmith::IdleStart()
{
	DirCheck("Idle");
}
void Squidsmith::IdleUpdate(float _Time)
{
	if (GameEngineInput::IsDown("MonsterTest"))
	{
		ChangeState(SquidsmithState::ACTION);
		return;
	}

	if (true == Isturn)
	{
		ChangeState(SquidsmithState::TURN);
		return;
	}
	
	DirCheck("Idle");
}
void Squidsmith::IdleEnd()
{
	
}

void Squidsmith::TurnStart()
{
	Isturn = false;
	DirCheck("Turn");
}
void Squidsmith::TurnUpdate(float _Time)
{
	if (true == AnimationRender->IsAnimationEnd())
	{
		ChangeState(SquidsmithState::IDLE);
		return;
	}
}
void Squidsmith::TurnEnd()
{

}

void Squidsmith::ActionStart()
{
	AnimationRender->ChangeAnimation("Enchant");
}
void Squidsmith::ActionUpdate(float _Time)
{
	if (71 == AnimationRender->GetFrame())
	{
		Player::MainPlayer->SetCameraShaking(0.5f, 4.0f);
	}

	if (true == AnimationRender->IsAnimationEnd())
	{
		ChangeState(SquidsmithState::IDLE);
		return;
	}
}
void Squidsmith::ActionEnd()
{

}