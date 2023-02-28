#include "Cacklebat.h"

#include <GameEngineCore/GameEngineCollision.h>

#include "ContentsEnum.h"
#include "Player.h"

// Player State º¯°æ
void Cacklebat::ChangeState(CacklebatState _State)
{
	CacklebatState NextState = _State;
	CacklebatState PrevState = StateValue;

	StateValue = NextState;

	switch (NextState)
	{
	case CacklebatState::IDLE:
		IdleStart();
		break;
	default:
		break;
	}

	switch (PrevState)
	{
	case CacklebatState::IDLE:
		IdleEnd();
		break;
	default:
		break;
	}
}

void Cacklebat::UpdateState(float _Time)
{
	switch (StateValue)
	{
	case CacklebatState::IDLE:
		IdleUpdate(_Time);
		break;
	default:
		break;
	}
}

/////////////////////////////////////////////////////// States ///////////////////////////////////////////////////////

///////////////////////////////////////////////////////  Idle  ///////////////////////////////////////////////////////

void Cacklebat::IdleStart()
{
	// Animation Start
	DirCheck("Idle");
}
void Cacklebat::IdleUpdate(float _Time)
{
	DirCheck("Idle");
}
void Cacklebat::IdleEnd()
{
}