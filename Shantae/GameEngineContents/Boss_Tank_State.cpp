#include "Boss_Tank.h"

#include <GameEngineCore/GameEngineCollision.h>

#include "ContentsEnum.h"
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
	case Boss_TankState::MOVE:
		MoveStart();
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
	default:
		break;
	}

	switch (PrevState)
	{
	case Boss_TankState::IDLE:
		IdleEnd();
		break;
	case Boss_TankState::MOVE:
		MoveEnd();
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
	case Boss_TankState::MOVE:
		MoveUpdate(_Time);
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
	if (true == HitAction)
	{
		ChangeState(Boss_TankState::HIT);
		return;
	}

	AccTime += _DeltaTime;

	if (2.0f <= AccTime && 3 == FireCount)
	{
		// FireCount = 2;
		// 
		ChangeState(Boss_TankState::FIRE);
		return;
	}
	//if (2.0f <= AccTime && 2 == FireCount)
	//{
	//	FireCount = 1;
	//	//
	//	ChangeState(Boss_TankState::FIRE);
	//	return;
	//}
	//if (2.0f <= AccTime && 1 == FireCount)
	//{
	//	FireCount = 0;
	//	//
	//	ChangeState(Boss_TankState::FIRE);
	//	return;
	//}

}
void Boss_Tank::IdleEnd()
{
	AccTime = 0.0f;
}

void Boss_Tank::MoveStart()
{
	AnimationRender->ChangeAnimation("Move");
}
void Boss_Tank::MoveUpdate(float _DeltaTime)
{

}
void Boss_Tank::MoveEnd()
{

}

void Boss_Tank::ChargeStart()
{
	AnimationRender->ChangeAnimation("Move");
}
void Boss_Tank::ChargeUpdate(float _DeltaTime)
{

}
void Boss_Tank::ChargeEnd()
{

}

void Boss_Tank::BackUpStart()
{
	AnimationRender->ChangeAnimation("BackUp");
}
void Boss_Tank::BackUpUpdate(float _DeltaTime)
{

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
	if (true == AnimationRender->IsAnimationEnd())
	{
		Fire();
		CreatePoof();
		ChangeState(Boss_TankState::IDLE);
		return;
	}
}
void Boss_Tank::FireEnd()
{

}

void Boss_Tank::HitStart()
{
	AnimationRender->ChangeAnimation("Empty");
	BodyCollision->Off();
}
void Boss_Tank::HitUpdate(float _DeltaTime)
{
	HitActionTime += _DeltaTime;

	if (5.0f <= HitActionTime)
	{
		HitAction = false;
		BodyCollision->On();
		ChangeState(Boss_TankState::IDLE);
		return;
	}

}
void Boss_Tank::HitEnd()
{
	HitActionTime = 0.0f;
}