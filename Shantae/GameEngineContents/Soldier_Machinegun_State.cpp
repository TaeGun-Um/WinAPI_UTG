#include "Soldier_Machinegun.h"

#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineCollision.h>
#include <GameEngineCore/GameEngineRender.h>

#include "ContentsEnum.h"

// Player State ����
void Soldier_Machinegun::ChangeState(Soldier_MachinegunState _State)
{
	Soldier_MachinegunState NextState = _State;
	Soldier_MachinegunState PrevState = StateValue;

	StateValue = NextState;

	switch (NextState)
	{
	case Soldier_MachinegunState::IDLE:
		IdleStart();
		break;
	case Soldier_MachinegunState::FIRE_L:
		FireLStart();
		break;
	case Soldier_MachinegunState::FIRE_M:
		FireMStart();
		break;
	case Soldier_MachinegunState::FIRE_R:
		FireRStart();
		break;
	case Soldier_MachinegunState::TURN_R:
		TurnRStart();
		break;
	case Soldier_MachinegunState::TURN_L:
		TurnLStart();
		break;
	case Soldier_MachinegunState::TURN_LB:
		TurnLBStart();
		break;
	case Soldier_MachinegunState::TURN_RB:
		TurnRBStart();
		break;
	default:
		break;
	}

	switch (PrevState)
	{
	case Soldier_MachinegunState::IDLE:
		IdleEnd();
		break;
	case Soldier_MachinegunState::FIRE_L:
		FireLEnd();
		break;
	case Soldier_MachinegunState::FIRE_M:
		FireMEnd();
		break;
	case Soldier_MachinegunState::FIRE_R:
		FireREnd();
		break;
	case Soldier_MachinegunState::TURN_R:
		TurnREnd();
		break;
	case Soldier_MachinegunState::TURN_L:
		TurnLEnd();
		break;
	case Soldier_MachinegunState::TURN_LB:
		TurnLBEnd();
		break;
	case Soldier_MachinegunState::TURN_RB:
		TurnRBEnd();
		break;
	default:
		break;
	}
}

void Soldier_Machinegun::UpdateState(float _Time)
{
	switch (StateValue)
	{
	case Soldier_MachinegunState::IDLE:
		IdleUpdate(_Time);
		break;
	case Soldier_MachinegunState::FIRE_L:
		FireLUpdate(_Time);
		break;
	case Soldier_MachinegunState::FIRE_M:
		FireMUpdate(_Time);
		break;
	case Soldier_MachinegunState::FIRE_R:
		FireRUpdate(_Time);
		break;
	case Soldier_MachinegunState::TURN_R:
		TurnRUpdate(_Time);
		break;
	case Soldier_MachinegunState::TURN_L:
		TurnLUpdate(_Time);
		break;
	case Soldier_MachinegunState::TURN_LB:
		TurnLBUpdate(_Time);
		break;
	case Soldier_MachinegunState::TURN_RB:
		TurnRBUpdate(_Time);
		break;
	default:
		break;
	}
}

/////////////////////////////////////////////////////// States ///////////////////////////////////////////////////////

///////////////////////////////////////////////////////  Crouch  ///////////////////////////////////////////////////////

// ���
void Soldier_Machinegun::IdleStart()
{
	// Animation Start
	AnimationRender->ChangeAnimation("Idle");
}
void Soldier_Machinegun::IdleUpdate(float _Time)
{
	AccTime += _Time;

	if (2.0f <= AccTime)
	{
		AccTime = 0.0f;
		ChangeState(Soldier_MachinegunState::TURN_L);
		return;
	}
}
void Soldier_Machinegun::IdleEnd()
{
}

///////////////////////////////////////////////////////  Lob  ///////////////////////////////////////////////////////

// �������� ����
void Soldier_Machinegun::TurnLStart()
{
	AnimationRender->ChangeAnimation("Turn_L");
}
void Soldier_Machinegun::TurnLUpdate(float _Time)
{
	if (true == AnimationRender->IsAnimationEnd())
	{
		ChangeState(Soldier_MachinegunState::FIRE_L);
		return;
	}
}
void Soldier_Machinegun::TurnLEnd()
{

}

// ���� ���
void Soldier_Machinegun::FireLStart()
{
	AnimationRender->ChangeAnimation("Fire_L");
}
void Soldier_Machinegun::FireLUpdate(float _Time)
{
	if (true == AnimationRender->IsAnimationEnd())
	{
		ChangeState(Soldier_MachinegunState::TURN_LB);
		return;
	}
}
void Soldier_Machinegun::FireLEnd()
{

}

// ���ʿ��� ���ƿ´�
void Soldier_Machinegun::TurnLBStart()
{
	AnimationRender->ChangeAnimation("Turn_LB");
}
void Soldier_Machinegun::TurnLBUpdate(float _Time)
{
	if (true == AnimationRender->IsAnimationEnd())
	{
		ChangeState(Soldier_MachinegunState::FIRE_M);
		return;
	}
}
void Soldier_Machinegun::TurnLBEnd()
{

}

// ��� ���
void Soldier_Machinegun::FireMStart()
{
	AnimationRender->ChangeAnimation("Fire_M");
}
void Soldier_Machinegun::FireMUpdate(float _Time)
{
	if (true == AnimationRender->IsAnimationEnd())
	{
		ChangeState(Soldier_MachinegunState::TURN_R);
		return;
	}
}
void Soldier_Machinegun::FireMEnd()
{

}

// ���������� ����
void Soldier_Machinegun::TurnRStart()
{
	AnimationRender->ChangeAnimation("Turn_R");
}
void Soldier_Machinegun::TurnRUpdate(float _Time)
{
	if (true == AnimationRender->IsAnimationEnd())
	{
		ChangeState(Soldier_MachinegunState::FIRE_R);
		return;
	}
}
void Soldier_Machinegun::TurnREnd()
{

}

// ������ ���
void Soldier_Machinegun::FireRStart()
{
	AnimationRender->ChangeAnimation("Fire_R");
}
void Soldier_Machinegun::FireRUpdate(float _Time)
{
	if (true == AnimationRender->IsAnimationEnd())
	{
		ChangeState(Soldier_MachinegunState::TURN_RB);
		return;
	}
}
void Soldier_Machinegun::FireREnd()
{

}

// �����ʿ��� ���ƿ´�.
void Soldier_Machinegun::TurnRBStart()
{
	AnimationRender->ChangeAnimation("Turn_RB");
}
void Soldier_Machinegun::TurnRBUpdate(float _Time)
{
	if (true == AnimationRender->IsAnimationEnd())
	{
		ChangeState(Soldier_MachinegunState::IDLE);
		return;
	}
}
void Soldier_Machinegun::TurnRBEnd()
{

}