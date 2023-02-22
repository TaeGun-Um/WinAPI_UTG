#include "Soldier_Bomberman.h"

#include <GameEngineCore/GameEngineCollision.h>

#include "ContentsEnum.h"
#include "Player.h"

// Player State º¯°æ
void Soldier_Bomberman::ChangeState(Soldier_BombermanState _State)
{
	Soldier_BombermanState NextState = _State;
	Soldier_BombermanState PrevState = StateValue;

	StateValue = NextState;

	switch (NextState)
	{
	case Soldier_BombermanState::CROUCH:
		CrouchStart();
		break;
	case Soldier_BombermanState::LOB:
		LobStart();
		break;
	case Soldier_BombermanState::HIT:
		HitStart();
		break;
	default:
		break;
	}

	switch (PrevState)
	{
	case Soldier_BombermanState::CROUCH:
		CrouchEnd();
		break;
	case Soldier_BombermanState::LOB:
		LobEnd();
		break;
	case Soldier_BombermanState::HIT:
		HitEnd();
		break;
	default:
		break;
	}
}

void Soldier_Bomberman::UpdateState(float _Time)
{
	switch (StateValue)
	{
	case Soldier_BombermanState::CROUCH:
		CrouchUpdate(_Time);
		break;
	case Soldier_BombermanState::LOB:
		LobUpdate(_Time);
		break;
	case Soldier_BombermanState::HIT:
		HitUpdate(_Time);
		break;
	default:
		break;
	}
}

/////////////////////////////////////////////////////// States ///////////////////////////////////////////////////////

///////////////////////////////////////////////////////  Crouch  ///////////////////////////////////////////////////////

void Soldier_Bomberman::CrouchStart()
{
	// Animation Start
	DirCheck("Crouch");
}
void Soldier_Bomberman::CrouchUpdate(float _Time)
{
	if (true == HitAction)
	{
		ChangeState(Soldier_BombermanState::HIT);
		return;
	}

	LobStatTime += _Time;

	if (2.0f <= LobStatTime)
	{
		BoomCount = 1;
		LobStatTime = 0.0f;
		ChangeState(Soldier_BombermanState::LOB);
		return;
	}

	DirCheck("Crouch");
}
void Soldier_Bomberman::CrouchEnd()
{
}

///////////////////////////////////////////////////////  Lob  ///////////////////////////////////////////////////////

void Soldier_Bomberman::LobStart()
{
	// Animation Start
	trace = false;
	DirCheck("Lob");
}
void Soldier_Bomberman::LobUpdate(float _Time)
{
	if (true == HitAction)
	{
		trace = true;
		ChangeState(Soldier_BombermanState::HIT);
		return;
	}

	if (32 == AnimationRender->GetFrame())
	{	
		if (1 == BoomCount)
		{
			BoomCount = 0;
			Throw();
		}
	}

	if (AnimationRender->IsAnimationEnd())
	{
		trace = true;
		ChangeState(Soldier_BombermanState::CROUCH);
		return;
	}
}
void Soldier_Bomberman::LobEnd()
{
	trace = true;
}

///////////////////////////////////////////////////////  Hit  ///////////////////////////////////////////////////////

void Soldier_Bomberman::HitStart()
{
	HitDir = Player::MainPlayer->GetDir().data();

	MoveDir.y += -900.0f;

	BodyCollision->Off();

	BGMPlayer = GameEngineResources::GetInst().SoundPlayToControl("Soldier_die.wav");
	BGMPlayer.Volume(0.05f);
	BGMPlayer.LoopCount(1);
}
void Soldier_Bomberman::HitUpdate(float _Time)
{
	IsTurn = false;

	if ("_L" == HitDir)
	{
		AnimationRender->ChangeAnimation("Hit_R");
		SetMove(float4::Left * 250.0f * _Time);
	}
	else if ("_R" == HitDir)
	{
		AnimationRender->ChangeAnimation("Hit_L");
		SetMove(float4::Right * 250.0f * _Time);
	}

	HitTime += _Time;

	if (0.5f <= HitTime)
	{
		IsDeath = true;
		return;
	}
}
void Soldier_Bomberman::HitEnd()
{
}