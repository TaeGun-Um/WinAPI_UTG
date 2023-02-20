#include "Boss_Tank.h"

#include <cstdlib>
#include <ctime>

#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineResources.h>
#include <GameEngineCore/GameEngineCollision.h>
#include <GameEngineCore/GameEngineRender.h>
#include <GameEngineCore/GameEngineLevel.h>

#include "ContentsEnum.h"

#include "Public_Boom.h"
#include "Boss_Boom.h"
#include "Boss_Boom_Red.h"
#include "SmallPoof.h"

Boss_Tank::Boss_Tank()
{
}

Boss_Tank::~Boss_Tank()
{
}

void Boss_Tank::Start()
{
	// Animation
	RenderSet();

	// Collision
	CollisionSet();

	//ChangeState(Boss_TankState::IDLE);
	ChangeState(Boss_TankState::HIT);
}

void Boss_Tank::Update(float _DeltaTime)
{
	UpdateState(_DeltaTime);
	CollisionCheck();
}
void Boss_Tank::Render(float _DeltaTime)
{

}

void Boss_Tank::CollisionCheck()
{
	if (nullptr != BodyCollision)
	{
		if (true == BodyCollision->Collision({ .TargetGroup = static_cast<int>(CollisionOrder::Trigger), .TargetColType = CT_Rect, .ThisColType = CT_Rect }))
		{
			HitAction = true;
		}
	}
}

// Animation
void Boss_Tank::RenderSet()
{
	// Animation
	AnimationRender = CreateRender(RenderOrder::Monster);
	AnimationRender->SetScale({ 1500, 1500 });
	
	BossPos = { 1200, 750 };
	ChargePos = { 550, 750 };
	PushoutPos = { 1300, 750 };

	// ÁÂ¿ì ±¸ºÐ x
	AnimationRender->CreateAnimation({ .AnimationName = "Idle",  .ImageName = "Boss_Tank.bmp", .Start = 0, .End = 3, .InterTime = 0.08f });
	AnimationRender->CreateAnimation({ .AnimationName = "IdleRev",  .ImageName = "Boss_Tank.bmp", .Start = 4, .End = 7, .InterTime = 0.08f });
	AnimationRender->CreateAnimation({ .AnimationName = "Move",  .ImageName = "Boss_Tank.bmp", .Start = 8, .End = 11, .InterTime = 0.08f });
	AnimationRender->CreateAnimation({ .AnimationName = "Charge",  .ImageName = "Boss_Tank.bmp", .Start = 8, .End = 11, .InterTime = 0.05f });
	AnimationRender->CreateAnimation({ .AnimationName = "BackUp",  .ImageName = "Boss_Tank.bmp", .Start = 12, .End = 15, .InterTime = 0.08f });
	AnimationRender->CreateAnimation({ .AnimationName = "Fire",  .ImageName = "Boss_Tank.bmp", .Start = 16, .End = 22, .InterTime = 0.08f });
	AnimationRender->CreateAnimation({ .AnimationName = "Pushout",  .ImageName = "Boss_Tank.bmp", .Start = 22, .End = 22, .InterTime = 0.08f, .Loop = false });
	AnimationRender->CreateAnimation({ .AnimationName = "Dead_Idle",  .ImageName = "Boss_Tank.bmp", .Start = 31, .End = 31, .InterTime = 0.1f, .Loop = false });
	AnimationRender->CreateAnimation({ .AnimationName = "Empty",  .ImageName = "Boss_Tank.bmp", .Start = 32, .End = 32, .InterTime = 0.1f, .Loop = false });
}

// Collision
void Boss_Tank::CollisionSet()
{
	// Collision
	BodyCollision = CreateCollision(CollisionOrder::Monster);
	BodyCollision->SetDebugRenderType(CT_Rect);
	BodyCollision->SetScale({ 300, 500 });
	BodyCollision->SetPosition({ 0, -200 });
}

void Boss_Tank::CreateExplosion()
{
	Public_Boom* Ex = nullptr;
	float4 ExPos = float4::Zero;
	ExPos = GetPos() + (float4::Left * 220) + (float4::Up * 330);

	Ex = GetLevel()->CreateActor<Public_Boom>();
	Ex->SetPos(ExPos);
	Ex->SetExPlus(0);
}

void Boss_Tank::CreatePoof()
{
	SmallPoof* Ex = nullptr;
	float4 ExPos = float4::Zero;
	ExPos = GetPos() + (float4::Left * 220) + (float4::Up * 330);

	Ex = GetLevel()->CreateActor<SmallPoof>();
	Ex->SetPos(ExPos);
}

void Boss_Tank::Fire()
{
	Boss_Boom* NewBoom = nullptr;
	float4 BoomPos = float4::Zero;
	BoomPos = GetPos() + (float4::Left * 220) + (float4::Up * 330);

	NewBoom = GetLevel()->CreateActor<Boss_Boom>();
	NewBoom->SetColMap(ColMap);
	NewBoom->SetPos(BoomPos);
	NewBoom->SetOwnerPos(GetPos());
}

void Boss_Tank::Fire_Red()
{
	Boss_Boom_Red* NewBoom = nullptr;
	float4 BoomPos = float4::Zero;
	BoomPos = GetPos() + (float4::Left * 220) + (float4::Up * 300);

	NewBoom = GetLevel()->CreateActor<Boss_Boom_Red>();
	NewBoom->SetColMap(ColMap);
	NewBoom->SetPos(BoomPos);
	NewBoom->SetOwnerPos(GetPos());
}

void Boss_Tank::Charge()
{
	//
}

int Boss_Tank::RandomNumberGeneration()
{
	srand((unsigned int)time(nullptr));

	int Return = 0;
	int RandomNumber = rand();

	return Return = RandomNumber % 10;
}