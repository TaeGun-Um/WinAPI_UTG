#include "Mermaid.h"

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
	case MermaidState::SHOOT:
		ShootStart();
		break;
	case MermaidState::RELOAD:
		ReloadStart();
		break;
	case MermaidState::HIT:
		HitStart();
		break;
	default:
		break;
	}

	switch (PrevState)
	{
	case MermaidState::IDLE:
		IdleEnd();
		break;
	case MermaidState::SHOOT:
		ShootEnd();
		break;
	case MermaidState::RELOAD:
		ReloadEnd();
		break;
	case MermaidState::HIT:
		HitEnd();
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
	case MermaidState::SHOOT:
		ShootUpdate(_Time);
		break;
	case MermaidState::RELOAD:
		ReloadUpdate(_Time);
		break;
	case MermaidState::HIT:
		HitUpdate(_Time);
		break;
	default:
		break;
	}
}

/////////////////////////////////////////////////////// States ///////////////////////////////////////////////////////

///////////////////////////////////////////////////////  Idle  ///////////////////////////////////////////////////////

void Mermaid::IdleStart()
{
	// Animation Start
	DirCheck("Idle");
}
void Mermaid::IdleUpdate(float _Time)
{
	if (true == HitAction)
	{
		ChangeState(MermaidState::HIT);
		return;
	}

	ShootStartTime += _Time;

	if (2.0f <= ShootStartTime && true == IsAttack)
	{
		ShootCount = 3;
		ShootStartTime = 0.0f;
		ChangeState(MermaidState::SHOOT);
		return;
	}

	DirCheck("Idle");
}
void Mermaid::IdleEnd()
{
}

///////////////////////////////////////////////////////  Shoot  ///////////////////////////////////////////////////////

void Mermaid::ShootStart()
{
	// Animation Start
	DirCheck("Shoot");
	trace = false;
}
void Mermaid::ShootUpdate(float _Time)
{
	if (true == HitAction)
	{
		trace = true;
		ChangeState(MermaidState::HIT);
		return;
	}

	if (0 == ShootCount)
	{
		ChangeState(MermaidState::RELOAD);
		return;
	}

	ShootTime += _Time;

	if (0 < ShootCount && 0.2f <= ShootTime)
	{
		ShootTime = 0.0f;
		Shoot();
		--ShootCount;

		BGMPlayer = GameEngineResources::GetInst().SoundPlayToControl("Soldier_gun_fire.mp3");
		BGMPlayer.Volume(0.15f);
		BGMPlayer.LoopCount(1);

		DirCheck("Shoot");
	}

}
void Mermaid::ShootEnd()
{
}

///////////////////////////////////////////////////////  ReLoad  ///////////////////////////////////////////////////////

void Mermaid::ReloadStart()
{
	// Animation Start
	DirCheck("ReLoad");
}
void Mermaid::ReloadUpdate(float _Time)
{
	if (true == HitAction)
	{
		trace = true;
		ChangeState(MermaidState::HIT);
		return;
	}

	if (true == AnimationRender->IsAnimationEnd())
	{
		trace = true;
		ChangeState(MermaidState::IDLE);
		return;
	}

	DirCheck("ReLoad");
}
void Mermaid::ReloadEnd()
{
}

///////////////////////////////////////////////////////  Hit  ///////////////////////////////////////////////////////

void Mermaid::HitStart()
{
	HitDir = Player::MainPlayer->GetDir().data();

	MoveDir.y += -900.0f;

	BodyCollision->Off();

	BGMPlayer = GameEngineResources::GetInst().SoundPlayToControl("Soldier_die.wav");
	BGMPlayer.Volume(0.05f);
	BGMPlayer.LoopCount(1);
}
void Mermaid::HitUpdate(float _Time)
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
void Mermaid::HitEnd()
{
}