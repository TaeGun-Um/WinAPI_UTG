#include "AmmoBaron.h"

#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineCollision.h>
#include <GameEngineCore/GameEngineRender.h>

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
	case AmmoBaronState::STRUGGLE:
		StruggleStart();
		break;
	case AmmoBaronState::STANDUP:
		StandupStart();
		break;
	case AmmoBaronState::DUSTOFF:
		DustoffStart();
		break;
	case AmmoBaronState::RUN:
		RunStart();
		break;
	case AmmoBaronState::JUMP:
		JumpStart();
		break;
	case AmmoBaronState::IDLE:
		IdleStart();
		break;
	case AmmoBaronState::MOVE:
		MoveStart();
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
	case AmmoBaronState::STRUGGLE:
		StruggleEnd();
		break;
	case AmmoBaronState::STANDUP:
		StandupEnd();
		break;
	case AmmoBaronState::DUSTOFF:
		DustoffEnd();
		break;
	case AmmoBaronState::RUN:
		RunEnd();
		break;
	case AmmoBaronState::JUMP:
		JumpEnd();
		break;
	case AmmoBaronState::IDLE:
		IdleEnd();
		break;
	case AmmoBaronState::MOVE:
		MoveEnd();
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
	case AmmoBaronState::STRUGGLE:
		StruggleUpdate(_Time);
		break;
	case AmmoBaronState::STANDUP:
		StandupUpdate(_Time);
		break;
	case AmmoBaronState::DUSTOFF:
		DustoffUpdate(_Time);
		break;
	case AmmoBaronState::RUN:
		RunUpdate(_Time);
		break;
	case AmmoBaronState::JUMP:
		JumpUpdate(_Time);
		break;
	case AmmoBaronState::IDLE:
		IdleUpdate(_Time);
		break;
	case AmmoBaronState::MOVE:
		MoveUpdate(_Time);
		break;
	default:
		break;
	}
}

/////////////////////////////////////////////////////// States ///////////////////////////////////////////////////////

void AmmoBaron::IdleStart()
{
	AnimationRender->ChangeAnimation("Idle");

	if (false == IsEnd)
	{
		AnimationRender->Off();
	}
}
void AmmoBaron::IdleUpdate(float _DeltaTime)
{
	if (true == IsAction)
	{
		IsStart = true;
		ChangeState(AmmoBaronState::FLY);
		return;
	}
}
void AmmoBaron::IdleEnd()
{

}

void AmmoBaron::MoveStart()
{
	AnimationRender->ChangeAnimation("Move");
}
void AmmoBaron::MoveUpdate(float _DeltaTime)
{

}
void AmmoBaron::MoveEnd()
{

}

void AmmoBaron::FlyStart()
{
	BGMPlayer = GameEngineResources::GetInst().SoundPlayToControl("Boss_fly.mp3");
	BGMPlayer.Volume(0.1f);
	BGMPlayer.LoopCount(1);

	AnimationRender->ChangeAnimation("Fly");
	AnimationRender->On();
	MoveDir.y -= 600.0f;
	MoveSpeed = 200.0f;
}
void AmmoBaron::FlyUpdate(float _DeltaTime)
{
	SetMove(float4::Left * MoveSpeed * _DeltaTime);

	if (RGB(0, 248, 0) == ColMap->GetPixelColor(NextPos, RGB(0, 0, 0)))
	{
		ChangeState(AmmoBaronState::DOWN);
		return;
	}
}
void AmmoBaron::FlyEnd()
{

}

void AmmoBaron::DownStart()
{
	AnimationRender->ChangeAnimation("Down");
}
void AmmoBaron::DownUpdate(float _DeltaTime)
{
	if (true == AnimationRender->IsAnimationEnd())
	{
		AnimationRender->ChangeAnimation("Downing");
		DowningTime += _DeltaTime;
	}

	if (0.1f <= DowningTime)
	{
		ChangeState(AmmoBaronState::STRUGGLE);
		return;
	}
}
void AmmoBaron::DownEnd()
{
	DowningTime = 0.0f;
}

void AmmoBaron::StruggleStart()
{
	AnimationRender->ChangeAnimation("Struggle");

	if (false == IsEnd)
	{
		IsStruggle = true;
	}
}
void AmmoBaron::StruggleUpdate(float _DeltaTime)
{
	if (false == IsEnd)
	{
		StruggleTime += _DeltaTime;

		if (3.0f <= StruggleTime)
		{
			IsStruggle = false;
			BodyCollision->Off();
			ChangeState(AmmoBaronState::STANDUP);
			return;
		}
	}
	else if (IsEnd == true)
	{
		StruggleTime += _DeltaTime;

		if (3.0f <= StruggleTime)
		{
			IsTurn = false;
			IsStart = false;
			IsAction = false;
			ChangeState(AmmoBaronState::STANDUP);
			return;
		}
	}
}
void AmmoBaron::StruggleEnd()
{
	StruggleTime = 0.0f;
}

void AmmoBaron::StandupStart()
{
	AnimationRender->ChangeAnimation("Standup");
}
void AmmoBaron::StandupUpdate(float _DeltaTime)
{
	if (true == AnimationRender->IsAnimationEnd()
		&& true == IsEnd)
	{
		ChangeState(AmmoBaronState::IDLE);
		return;
	}

	if (true == AnimationRender->IsAnimationEnd())
	{
		ChangeState(AmmoBaronState::DUSTOFF);
		return;
	}
}
void AmmoBaron::StandupEnd()
{

}

void AmmoBaron::DustoffStart()
{
	AnimationRender->ChangeAnimation("Dustoff");
}
void AmmoBaron::DustoffUpdate(float _DeltaTime)
{
	if (true == AnimationRender->IsAnimationEnd())
	{
		ChangeState(AmmoBaronState::RUN);
		return;
	}
}
void AmmoBaron::DustoffEnd()
{

}

void AmmoBaron::RunStart()
{
	RunPlayer = GameEngineResources::GetInst().SoundPlayToControl("Boss_Run.mp3");
	RunPlayer.Volume(0.1f);
	RunPlayer.LoopCount(1);

	AnimationRender->ChangeAnimation("Run");
	MoveSpeed = 500.0f;
}
void AmmoBaron::RunUpdate(float _DeltaTime)
{
	SetMove(float4::Right * MoveSpeed * _DeltaTime);

	if (1250.0f <= GetPos().x)
	{
		ChangeState(AmmoBaronState::JUMP);
		return;
	}
}
void AmmoBaron::RunEnd()
{
	RunPlayer.Stop();
}

void AmmoBaron::JumpStart()
{
	AnimationRender->ChangeAnimation("Jump_R");
	MoveDir.y -= 1050.0f;
}
void AmmoBaron::JumpUpdate(float _DeltaTime)
{
	if (1405.0f <= GetPos().x)
	{
		IsTurn = true;
	}

	if (false == IsTurn)
	{
		SetMove(float4::Right * MoveSpeed * _DeltaTime);
	}
	else if (true == IsTurn)
	{
		AnimationRender->ChangeAnimation("Jump_L");
		SetMove(float4::Left * MoveSpeed * _DeltaTime);
	}

	if (1200.0f >= GetPos().x && true == IsTurn)
	{
		MoveSpeed = 0.0f;
		MoveDir = float4::Zero;
		SetPos({ 1200, 400 });
		ChangeState(AmmoBaronState::IDLE);
		return;
	}
	
}
void AmmoBaron::JumpEnd()
{
	IsTurn = false;
	IsStart = false;
	IsAction = false;
}
