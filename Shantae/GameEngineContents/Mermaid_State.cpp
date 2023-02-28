#include "Mermaid.h"

#include <GameEngineBase/GameEngineRandom.h>
#include <GameEngineCore/GameEngineCollision.h>

#include "ContentsEnum.h"
#include "Player.h"

// Player State º¯°æ
void Mermaid::ChangeState(MermaidState _State)
{
	MermaidState NextState = _State;
	MermaidState PrevState = StateValue;

	StateValue = NextState;

	switch (NextState)
	{
	case MermaidState::IDLE:
		IdleStart();
		break;
	case MermaidState::LURE:
		LureStart();
		break;
	case MermaidState::READY:
		ReadyStart();
		break;
	case MermaidState::HOLD:
		HoldStart();
		break;
	case MermaidState::DIVE:
		DiveStart();
		break;
	case MermaidState::EMERGE:
		EmergeStart();
		break;
	case MermaidState::SHOOT:
		ShootStart();
		break;
	case MermaidState::HIT:
		HitStart();
		break;
	case MermaidState::DIE:
		DieStart();
		break;
	default:
		break;
	}

	switch (PrevState)
	{
	case MermaidState::IDLE:
		IdleEnd();
		break;
	case MermaidState::LURE:
		LureEnd();
		break;
	case MermaidState::READY:
		ReadyEnd();
		break;
	case MermaidState::HOLD:
		HoldEnd();
		break;
	case MermaidState::DIVE:
		DiveEnd();
		break;
	case MermaidState::EMERGE:
		EmergeEnd();
		break;
	case MermaidState::SHOOT:
		ShootEnd();
		break;
	case MermaidState::HIT:
		HitEnd();
		break;
	case MermaidState::DIE:
		DieEnd();
		break;
	default:
		break;
	}
}

void Mermaid::UpdateState(float _Time)
{
	switch (StateValue)
	{
	case MermaidState::IDLE:
		IdleUpdate(_Time);
		break;
	case MermaidState::LURE:
		LureUpdate(_Time);
		break;
	case MermaidState::READY:
		ReadyUpdate(_Time);
		break;
	case MermaidState::HOLD:
		HoldUpdate(_Time);
		break;
	case MermaidState::DIVE:
		DiveUpdate(_Time);
		break;
	case MermaidState::EMERGE:
		EmergeUpdate(_Time);
		break;
	case MermaidState::SHOOT:
		ShootUpdate(_Time);
		break;
	case MermaidState::HIT:
		HitUpdate(_Time);
		break;
	case MermaidState::DIE:
		DieUpdate(_Time);
		break;
	default:
		break;
	}
}

void Mermaid::IdleStart()
{
	// Animation Start
	DirCheck("Idle");
}
void Mermaid::IdleUpdate(float _Time)
{
	if (true == IsDeath)
	{
		ChangeState(MermaidState::DIE);
		return;
	}

	if (true == HitAction)
	{
		ChangeState(MermaidState::HIT);
		return;
	}

	ShootStartTime += _Time;
	LureTime += _Time;

	if (3.0f <= ShootStartTime && true == IsAttack)
	{
		ShootCount = 1;
		ShootStartTime = 0.0f;
		LureTime = 0.0f;
		ChangeState(MermaidState::READY);
		return;
	}

	if (5.0f <= LureTime && false == IsAttack)
	{
		int RandC = GameEngineRandom::MainRandom.RandomInt(1, 2);

		if (1 == RandC)
		{
			LureTime = 0.0f;
			ChangeState(MermaidState::LURE);
			return;
		}
		else if (2 == RandC)
		{
			LureTime = 0.0f;
			ChangeState(MermaidState::DIVE);
			return;
		}
	}

	DirCheck("Idle");
}
void Mermaid::IdleEnd()
{
}

void Mermaid::LureStart()
{
	DirCheck("Lure");
}
void Mermaid::LureUpdate(float _Time)
{
	if (true == IsDeath)
	{
		ChangeState(MermaidState::DIE);
		return;
	}

	if (true == HitAction)
	{
		ChangeState(MermaidState::HIT);
		return;
	}

	ShootStartTime += _Time;

	if (3.0f <= ShootStartTime && true == IsAttack)
	{
		ShootCount = 1;
		ShootStartTime = 0.0f;
		ChangeState(MermaidState::READY);
		return;
	}

	if (true == AnimationRender->IsAnimationEnd())
	{
		ChangeState(MermaidState::IDLE);
		return;
	}
}
void Mermaid::LureEnd()
{

}

void Mermaid::ReadyStart()
{
	DirCheck("Ready");
}
void Mermaid::ReadyUpdate(float _Time)
{
	if (true == IsDeath)
	{
		ChangeState(MermaidState::DIE);
		return;
	}

	if (true == HitAction)
	{
		ChangeState(MermaidState::HIT);
		return;
	}

	if (true == AnimationRender->IsAnimationEnd())
	{
		ChangeState(MermaidState::HOLD);
		return;
	}
}
void Mermaid::ReadyEnd()
{

}

void Mermaid::HoldStart()
{
	DirCheck("Hold");
}
void Mermaid::HoldUpdate(float _Time)
{
	if (true == IsDeath)
	{
		ChangeState(MermaidState::DIE);
		return;
	}

	if (true == HitAction)
	{
		ChangeState(MermaidState::HIT);
		return;
	}

	HoldTime += _Time;

	if (0.5f <= HoldTime)
	{
		HoldTime = 0.0f;
		ChangeState(MermaidState::SHOOT);
		return;
	}
}
void Mermaid::HoldEnd()
{

}

void Mermaid::ShootStart()
{
	// Animation Start
	DirCheck("Attack");
}
void Mermaid::ShootUpdate(float _Time)
{
	if (true == IsDeath)
	{
		ChangeState(MermaidState::DIE);
		return;
	}

	if (true == HitAction)
	{
		ChangeState(MermaidState::HIT);
		return;
	}

	if (1 == ShootCount)
	{
		ShootCount = 0;
		Shoot();
		//BGMPlayer = GameEngineResources::GetInst().SoundPlayToControl("Soldier_gun_fire.mp3");
		//BGMPlayer.Volume(0.15f);
		//BGMPlayer.LoopCount(1);
	}

	if (true == AnimationRender->IsAnimationEnd())
	{
		ChangeState(MermaidState::IDLE);
		return;
	}
	
}
void Mermaid::ShootEnd()
{
}

void Mermaid::HitStart()
{
	DirCheck("Hurt");
}
void Mermaid::HitUpdate(float _Time)
{
	if (true == AnimationRender->IsAnimationEnd())
	{
		HitAction = false;
		ChangeState(MermaidState::DIVE);
		return;
	}
}
void Mermaid::HitEnd()
{
}

void Mermaid::DiveStart()
{
	BodyCollision->Off();

	DirCheck("Dive");
}
void Mermaid::DiveUpdate(float _Time)
{
	if (true == AnimationRender->IsAnimationEnd())
	{
		DiveTime += _Time;

		if (1.0f <= DiveTime)
		{
			DiveTime = 0.0f;
			ChangeState(MermaidState::EMERGE);
			return;
		}

	}
}
void Mermaid::DiveEnd()
{

}

void Mermaid::EmergeStart()
{
	DirCheck("Emerge");
}
void Mermaid::EmergeUpdate(float _Time)
{
	if (true == AnimationRender->IsAnimationEnd())
	{
		BodyCollision->On();
		ChangeState(MermaidState::IDLE);
		return;
	}
}
void Mermaid::EmergeEnd()
{

}

void Mermaid::DieStart()
{
	DirCheck("Die");
}
void Mermaid::DieUpdate(float _Time)
{
	if (true == AnimationRender->IsAnimationEnd())
	{
		Kill();
	}
}
void Mermaid::DieEnd()
{

}