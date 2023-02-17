#include "Soldier_Machinegun.h"

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

	// state
	ChangeState(Soldier_MachinegunState::IDLE);
}

void Soldier_Machinegun::Update(float _DeltaTime)
{
	UpdateState(_DeltaTime);
}
void Soldier_Machinegun::Render(float _DeltaTime)
{

}

void Soldier_Machinegun::Fire()
{
	Soldier_Aim* NewAim = nullptr;
	float4 BoomPos = float4::Zero;
	BoomPos = GetPos() + (float4::Up * 90);

	NewAim = GetLevel()->CreateActor<Soldier_Aim>();
	NewAim->SetPos(BoomPos);
}

void Soldier_Machinegun::RenderSet()
{
	AnimationRender = CreateRender(RenderOrder::Monster);
	AnimationRender->SetScale({ 400, 400 });

	// Right
	AnimationRender->CreateAnimation({ .AnimationName = "Idle",  .ImageName = "Soldier_Machinegun_L.bmp", .Start = 0, .End = 3, .InterTime = 0.2f });
	// End 1씩 추가함
	AnimationRender->CreateAnimation({ .AnimationName = "Turn_L",  .ImageName = "Soldier_Machinegun_L.bmp", .Start = 8, .End = 11, .InterTime = 0.2f });
	AnimationRender->CreateAnimation({ .AnimationName = "Fire_L",  .ImageName = "Soldier_Machinegun_L.bmp", .Start = 6, .End = 7, .InterTime = 0.2f });
	AnimationRender->CreateAnimation({ .AnimationName = "Turn_LB",  .ImageName = "Soldier_Machinegun_L.bmp", .Start = 12, .End = 15, .InterTime = 0.2f });
	AnimationRender->CreateAnimation({ .AnimationName = "Fire_M",  .ImageName = "Soldier_Machinegun_L.bmp", .Start = 5, .End = 6, .InterTime = 0.2f });
	AnimationRender->CreateAnimation({ .AnimationName = "Turn_R",  .ImageName = "Soldier_Machinegun_R.bmp", .Start = 8, .End = 11, .InterTime = 0.2f });
	AnimationRender->CreateAnimation({ .AnimationName = "Fire_R",  .ImageName = "Soldier_Machinegun_R.bmp", .Start = 6, .End = 7, .InterTime = 0.2f });
	AnimationRender->CreateAnimation({ .AnimationName = "Turn_RB",  .ImageName = "Soldier_Machinegun_R.bmp", .Start = 12, .End = 15, .InterTime = 0.2f });

}