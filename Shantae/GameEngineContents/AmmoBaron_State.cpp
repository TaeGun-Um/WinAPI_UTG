#include "AmmoBaron.h"

#include <GameEngineCore/GameEngineCollision.h>

#include "ContentsEnum.h"

// Player State º¯°æ
void AmmoBaron::ChangeState(AmmoBaronState _State)
{
	AmmoBaronState NextState = _State;
	AmmoBaronState PrevState = StateValue;

	StateValue = NextState;

	switch (NextState)
	{
	case AmmoBaronState::FLY:
		FlyStart();
		break;
	case AmmoBaronState::DOWN:
		DownStart();
		break;
	case AmmoBaronState::UP:
		UpStart();
		break;
	case AmmoBaronState::RUN:
		RunStart();
		break;
	case AmmoBaronState::JUMP:
		JumpStart();
		break;
	default:
		break;
	}

	switch (PrevState)
	{
	case AmmoBaronState::FLY:
		FlyEnd();
		break;
	case AmmoBaronState::DOWN:
		DownEnd();
		break;
	case AmmoBaronState::UP:
		UpEnd();
		break;
	case AmmoBaronState::RUN:
		RunEnd();
		break;
	case AmmoBaronState::JUMP:
		JumpEnd();
		break;
	default:
		break;
	}
}

void AmmoBaron::UpdateState(float _Time)
{
	switch (StateValue)
	{
	case AmmoBaronState::FLY:
		FlyUpdate(_Time);
		break;
	case AmmoBaronState::DOWN:
		DownUpdate(_Time);
		break;
	case AmmoBaronState::UP:
		UpUpdate(_Time);
		break;
	case AmmoBaronState::RUN:
		RunUpdate(_Time);
		break;
	case AmmoBaronState::JUMP:
		JumpUpdate(_Time);
		break;
	default:
		break;
	}
}

/////////////////////////////////////////////////////// States ///////////////////////////////////////////////////////

void AmmoBaron::FlyStart()
{

}
void AmmoBaron::FlyUpdate(float _DeltaTime)
{

}
void AmmoBaron::FlyEnd()
{

}

void AmmoBaron::DownStart()
{

}
void AmmoBaron::DownUpdate(float _DeltaTime)
{

}
void AmmoBaron::DownEnd()
{

}

void AmmoBaron::UpStart()
{

}
void AmmoBaron::UpUpdate(float _DeltaTime)
{

}
void AmmoBaron::UpEnd()
{

}

void AmmoBaron::RunStart()
{

}
void AmmoBaron::RunUpdate(float _DeltaTime)
{

}
void AmmoBaron::RunEnd()
{

}

void AmmoBaron::JumpStart()
{

}
void AmmoBaron::JumpUpdate(float _DeltaTime)
{

}
void AmmoBaron::JumpEnd()
{

}