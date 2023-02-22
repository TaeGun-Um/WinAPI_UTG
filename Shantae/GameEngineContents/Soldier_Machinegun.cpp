#include "Soldier_Machinegun.h"

#include <GameEngineBase/GameEngineDebug.h>
#include <GameEngineCore/GameEngineResources.h>
#include <GameEngineCore/GameEngineCollision.h>
#include <GameEngineCore/GameEngineRender.h>
#include <GameEngineCore/GameEngineLevel.h>

#include "ContentsEnum.h"

#include "Soldier_Aim.h"
#include "Machinegun_Bulletmarks.h"

Soldier_Machinegun::Soldier_Machinegun() 
{
}

Soldier_Machinegun::~Soldier_Machinegun() 
{
}

void Soldier_Machinegun::Start()
{
	// Animation
	RenderSet();

	CollisionSet();

	// state
	ChangeState(Soldier_MachinegunState::IDLE);
}

void Soldier_Machinegun::Update(float _DeltaTime)
{
	CollisionCheck(_DeltaTime);
	UpdateState(_DeltaTime);
}
void Soldier_Machinegun::Render(float _DeltaTime)
{

}

void Soldier_Machinegun::CollisionCheck(float _DeltaTime)
{
	if (nullptr != SensorCollision)
	{
		if (true == SensorCollision->Collision({ .TargetGroup = static_cast<int>(CollisionOrder::Player), .TargetColType = CT_Rect, .ThisColType = CT_Rect }))
		{
			IsAttack = true;
		}
	}
	if (nullptr != SensorCollision2)
	{
		if (true == SensorCollision2->Collision({ .TargetGroup = static_cast<int>(CollisionOrder::Player), .TargetColType = CT_Rect, .ThisColType = CT_Rect }))
		{
			IsAttack = false;
		}
	}
}

void Soldier_Machinegun::CreateAim(const int _Value)
{
	if (0 == _Value)
	{
		float4 AimPos = float4::Zero;
		AimPos = GetPos() + (float4::Left * 350) + (float4::Down * 120);
		Aim_L = GetLevel()->CreateActor<Soldier_Aim>();
		Aim_L->SetPos(AimPos);
	}
	else if (1 == _Value)
	{
		float4 AimPos = float4::Zero;
		AimPos = GetPos() + (float4::Down * 120);
		Aim_M = GetLevel()->CreateActor<Soldier_Aim>();
		Aim_M->SetPos(AimPos);
	}
	else if (2 == _Value)
	{
		float4 AimPos = float4::Zero;
		AimPos = GetPos() + (float4::Right * 350) + (float4::Down * 120);
		Aim_R = GetLevel()->CreateActor<Soldier_Aim>();
		Aim_R->SetPos(AimPos);
	}
	else
	{
		MsgAssert("올바른 에임방향을 입력해주세요.");
		return;
	}
}

void Soldier_Machinegun::AimKill(const int _Value)
{
	if (0 == _Value)
	{
		Aim_L->Off();
		Aim_L->Death();
		Aim_L = nullptr;
	}
	else if (1 == _Value)
	{
		Aim_M->Off();
		Aim_M->Death();
		Aim_M = nullptr;
	}
	else if (2 == _Value)
	{
		Aim_R->Off();
		Aim_R->Death();
		Aim_R = nullptr;
	}
	else
	{
		MsgAssert("삭제할 에임방향을 올바르게 입력해주세요.");
		return;
	}
}

void Soldier_Machinegun::Fire(const int _Value)
{
	Machinegun_Bulletmarks* NewBulletmarks = nullptr;
	float4 BulletmarksPos = float4::Zero;

	if (0 == _Value)
	{
		BulletmarksPos = GetPos() + (float4::Left * 350) + (float4::Down * 200);
	}
	else if (1 == _Value)
	{
		BulletmarksPos = GetPos() + (float4::Down * 200);
	}
	else if (2 == _Value)
	{
		BulletmarksPos = GetPos() + (float4::Right * 350) + (float4::Down * 200);
	}
	else
	{
		MsgAssert("올바른 발사방향을 입력해주세요.");
		return;
	}
	
	NewBulletmarks = GetLevel()->CreateActor<Machinegun_Bulletmarks>();
	NewBulletmarks->SetPos(BulletmarksPos);
}

void Soldier_Machinegun::RenderSet()
{
	AnimationRender = CreateRender(RenderOrder::Monster);
	AnimationRender->SetScale({ 400, 400 });

	// Right
	AnimationRender->CreateAnimation({ .AnimationName = "Idle",  .ImageName = "Soldier_Machinegun_L.bmp", .Start = 0, .End = 3, .InterTime = 0.08f });
	// End 1씩 추가함
	AnimationRender->CreateAnimation({ .AnimationName = "Turn_L",  .ImageName = "Soldier_Machinegun_L.bmp", .Start = 8, .End = 11, .InterTime = 0.08f });
	AnimationRender->CreateAnimation({ .AnimationName = "Fire_L",  .ImageName = "Soldier_Machinegun_L.bmp", .Start = 6, .End = 7, .InterTime = 0.05f });
	AnimationRender->CreateAnimation({ .AnimationName = "Turn_LB",  .ImageName = "Soldier_Machinegun_L.bmp", .Start = 12, .End = 15, .InterTime = 0.08f });
	AnimationRender->CreateAnimation({ .AnimationName = "Fire_M",  .ImageName = "Soldier_Machinegun_L.bmp", .Start = 4, .End = 5, .InterTime = 0.05f });
	AnimationRender->CreateAnimation({ .AnimationName = "Turn_R",  .ImageName = "Soldier_Machinegun_R.bmp", .Start = 8, .End = 11, .InterTime = 0.08f });
	AnimationRender->CreateAnimation({ .AnimationName = "Fire_R",  .ImageName = "Soldier_Machinegun_R.bmp", .Start = 6, .End = 7, .InterTime = 0.05f });
	AnimationRender->CreateAnimation({ .AnimationName = "Turn_RB",  .ImageName = "Soldier_Machinegun_R.bmp", .Start = 12, .End = 15, .InterTime = 0.08f });

}
void Soldier_Machinegun::CollisionSet()
{
	SensorCollision = CreateCollision(CollisionOrder::Trigger);
	SensorCollision->SetDebugRenderType(CT_Rect);
	SensorCollision->SetScale({ 10, 500 });
	SensorCollision->SetPosition({ -650, 0 });

	SensorCollision2 = CreateCollision(CollisionOrder::Trigger);
	SensorCollision2->SetDebugRenderType(CT_Rect);
	SensorCollision2->SetScale({ 10, 500 });
	SensorCollision2->SetPosition({ 650, 0 });
}