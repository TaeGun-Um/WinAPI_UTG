#include "Boss_Tank.h"

#include <GameEngineCore/GameEngineCollision.h>
#include <GameEngineCore/GameEngineRender.h>

#include "ContentsEnum.h"
#include "AmmoBaron.h"
#include "Player.h"

// Player State º¯°æ
void Boss_Tank::ChangeState(Boss_TankState _State)
{
	Boss_TankState NextState = _State;
	Boss_TankState PrevState = StateValue;

	StateValue = NextState;

	switch (NextState)
	{
	case Boss_TankState::IDLE:
		IdleStart();
		break;
	case Boss_TankState::IDLEREV:
		IdleRevStart();
		break;
	case Boss_TankState::PUSHOUT:
		PushoutStart();
		break;
	case Boss_TankState::CHARGE:
		ChargeStart();
		break;
	case Boss_TankState::BACKUP:
		BackUpStart();
		break;
	case Boss_TankState::FIRE:
		FireStart();
		break;
	case Boss_TankState::HIT:
		HitStart();
		break;
	case Boss_TankState::EMPTY:
		EmptyStart();
		break;
	default:
		break;
	}

	switch (PrevState)
	{
	case Boss_TankState::IDLE:
		IdleEnd();
		break;
	case Boss_TankState::IDLEREV:
		IdleRevEnd();
		break;
	case Boss_TankState::PUSHOUT:
		PushoutEnd();
		break;
	case Boss_TankState::CHARGE:
		ChargeEnd();
		break;
	case Boss_TankState::BACKUP:
		BackUpEnd();
		break;
	case Boss_TankState::FIRE:
		FireEnd();
		break;
	case Boss_TankState::HIT:
		HitEnd();
		break;
	case Boss_TankState::EMPTY:
		EmptyEnd();
		break;
	default:
		break;
	}
}

void Boss_Tank::UpdateState(float _Time)
{
	switch (StateValue)
	{
	case Boss_TankState::IDLE:
		IdleUpdate(_Time);
		break;
	case Boss_TankState::IDLEREV:
		IdleRevUpdate(_Time);
		break;
	case Boss_TankState::PUSHOUT:
		PushoutUpdate(_Time);
		break;
	case Boss_TankState::CHARGE:
		ChargeUpdate(_Time);
		break;
	case Boss_TankState::BACKUP:
		BackUpUpdate(_Time);
		break;
	case Boss_TankState::FIRE:
		FireUpdate(_Time);
		break;
	case Boss_TankState::HIT:
		HitUpdate(_Time);
		break;
	case Boss_TankState::EMPTY:
		EmptyUpdate(_Time);
		break;
	default:
		break;
	}
}

/////////////////////////////////////////////////////// States ///////////////////////////////////////////////////////

///////////////////////////////////////////////////////  Crouch  ///////////////////////////////////////////////////////

void Boss_Tank::IdleStart()
{
	AnimationRender->ChangeAnimation("Idle");
}
void Boss_Tank::IdleUpdate(float _DeltaTime)
{
	AccTime += _DeltaTime;

	if (0 >= Baron->GetBaronHP())
	{
		if (2.0f <= AccTime && 3 == FireCount)
		{
			FireCount = 2;
			ChangeState(Boss_TankState::FIRE);
			return;
		}
		else if (2.0f <= AccTime && 2 == FireCount)
		{
			FireCount = 1;
			ChangeState(Boss_TankState::FIRE);
			return;
		}
		else if (2.0f <= AccTime && 1 == FireCount)
		{
			FireCount = 0;
			ChangeState(Boss_TankState::FIRE);
			return;
		}
	}

	if (true == HitAction && 0 >= Baron->GetBaronHP())
	{
		ChangeState(Boss_TankState::EMPTY);
		return;
	}

	if (0 <= Baron->GetBaronHP())
	{
		if (true == HitAction)
		{
			FireCount = 3;
			ChangeState(Boss_TankState::HIT);
			return;
		}

		if (1 == RandCreate)
		{
			RandCreate = 0;
			Rand = RandomNumberGeneration();
		}

		/*if (0 <= Rand && Rand <= 4)*/
		if (0 == Rand % 2)
		{
			if (2.0f <= AccTime && 3 == FireCount)
			{
				FireCount = 2;
				ChangeState(Boss_TankState::FIRE);
				return;
			}
			else if (2.0f <= AccTime && 2 == FireCount)
			{
				FireCount = 1;
				ChangeState(Boss_TankState::FIRE);
				return;
			}
			else if (2.0f <= AccTime && 1 == FireCount)
			{
				FireCount = 0;
				ChangeState(Boss_TankState::FIRE);
				return;
			}
		}

		/*if (5 <= Rand && Rand <= 9)*/
		if (0 != Rand % 2)
		{
			if (2.0f <= AccTime)
			{
				ChangeState(Boss_TankState::CHARGE);
				return;
			}
		}
	}
}
void Boss_Tank::IdleEnd()
{
	AccTime = 0.0f;
}

void Boss_Tank::ChargeStart()
{
	AnimationRender->ChangeAnimation("Charge");
}
void Boss_Tank::ChargeUpdate(float _DeltaTime)
{
	ChargeTime += _DeltaTime;

	if (2.0f < ChargeTime && false == IsCharge)
	{
		if (ChargePos.x <= GetPos().x)
		{
			SetMove(float4::Left * 1200.0f * _DeltaTime);
		}
		else if ((ChargePos.x + 5.0f) >= GetPos().x)
		{
			IsCharge = true;
			SetPos(ChargePos);
			Player::MainPlayer->SetCameraShaking(0.5f, 5);
		}
	}

	if (true == IsCharge)
	{
		IsCharge = false;
		ChangeState(Boss_TankState::IDLEREV);
		return;
	}
}
void Boss_Tank::ChargeEnd()
{
	ChargeTime = 0.0f;
}

void Boss_Tank::IdleRevStart()
{
	AnimationRender->ChangeAnimation("IdleRev");
}
void Boss_Tank::IdleRevUpdate(float _DeltaTime)
{
	RevTime += _DeltaTime;

	if (1.0f < RevTime)
	{
		ChangeState(Boss_TankState::BACKUP);
		return;
	}
}
void Boss_Tank::IdleRevEnd()
{
	RevTime = 0.0f;
}

void Boss_Tank::BackUpStart()
{
	AnimationRender->ChangeAnimation("BackUp");
}
void Boss_Tank::BackUpUpdate(float _DeltaTime)
{
	if (GetPos().x <= BossPos.x)
	{
		SetMove(float4::Right * 1500.0f * _DeltaTime);
	}
	else if (GetPos().x >= BossPos.x)
	{
		SetPos(BossPos);
		RandCreate = 1;
		AccTime += 1.0f;
		ChangeState(Boss_TankState::IDLE);
		return;
	}
}
void Boss_Tank::BackUpEnd()
{
}

void Boss_Tank::FireStart()
{
	AnimationRender->ChangeAnimation("Fire");
}
void Boss_Tank::FireUpdate(float _DeltaTime)
{
	if (21 == AnimationRender->GetFrame())
	{
		if (1 == CreateCount && 2 == FireCount)
		{
			CreateCount = 0;
			CreateExplosion();
			Fire();
			ChangeState(Boss_TankState::PUSHOUT);
			return;
		}
		else if (1 == CreateCount && 1 == FireCount)
		{
			CreateCount = 0;
			CreateExplosion();
			Fire();
			ChangeState(Boss_TankState::PUSHOUT);
			return;
		}
		else if (1 == CreateCount && 0 == FireCount)
		{
			CreateCount = 0;
			FireCount = 3;
			RandCreate = 1;
			AccTime -= 1.5f;
			CreatePoof();
			Fire_Red();
		}
	}

	if (true == AnimationRender->IsAnimationEnd())
	{
		ChangeState(Boss_TankState::IDLE);
		return;
	}
}
void Boss_Tank::FireEnd()
{
	CreateCount = 1;
}

void Boss_Tank::PushoutStart()
{
	AnimationRender->ChangeAnimation("Pushout");
	SetPos(PushoutPos);
}
void Boss_Tank::PushoutUpdate(float _DeltaTime)
{
	PushoutTime += _DeltaTime;

	if (0.1f <= PushoutTime)
	{
		AnimationRender->ChangeAnimation("IdleRev");
	}

	if (0.3f <= PushoutTime && GetPos().x >= BossPos.x)
	{
		AnimationRender->ChangeAnimation("Move");
		SetMove(float4::Left * 500.0f * _DeltaTime);
	}
	else if (GetPos().x <= BossPos.x)
	{
		SetPos(BossPos);
		ChangeState(Boss_TankState::IDLE);
		return;
	}
}
void Boss_Tank::PushoutEnd()
{
	PushoutTime = 0.0f;
}

void Boss_Tank::HitStart()
{
	AnimationRender->ChangeAnimation("Empty");
	BodyCollision->Off();
	
	if (1 == BaronStart)
	{
		BaronStart = 0;
		Baron->SetBaronAction(true);
	}
}
void Boss_Tank::HitUpdate(float _DeltaTime)
{
	if (false == Baron->GetBaronAction())
	{
		ChangeState(Boss_TankState::IDLE);
		return;
	}

}
void Boss_Tank::HitEnd()
{
	BodyCollision->On();
	HitAction = false;
	BaronStart = 1;
}

void Boss_Tank::EmptyStart()
{
	AnimationRender->ChangeAnimation("IdleRev");
	BodyCollision->Off();
}
void Boss_Tank::EmptyUpdate(float _DeltaTime)
{
	ExplosionTime += _DeltaTime;
	RandomExplosionTime += _DeltaTime;

	if (0.1f <= RandomExplosionTime 
		&& 4.0f >= ExplosionTime)
	{
		RandomCreateExplosion(_DeltaTime);
		RandomExplosionTime = 0.0f;
	}

	if (4.0f <= ExplosionTime)
	{
		if (1 == BaronStart)
		{
			BaronStart = 0;
			Baron->SetBaronAction(true);
			Baron->SetEnd();
		}
		AnimationRender->ChangeAnimation("Dead_Idle");
	}
}
void Boss_Tank::EmptyEnd()
{
	ExplosionTime = 0.0f;
}