#include "Boss_Tank.h"

#include <cstdlib>
#include <ctime>

#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineResources.h>
#include <GameEngineCore/GameEngineCollision.h>
#include <GameEngineCore/GameEngineRender.h>
#include <GameEngineCore/GameEngineLevel.h>

#include "ContentsEnum.h"

#include "Player.h"
#include "Public_Boom.h"
#include "Boss_Boom.h"
#include "Boss_Boom_Red.h"
#include "SmallPoof.h"
#include "AmmoBaron.h"

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

	ChangeState(Boss_TankState::IDLE);
	// ChangeState(Boss_TankState::HIT);
}

void Boss_Tank::Update(float _DeltaTime)
{
	if (1 == BaronCreate)
	{
		BaronCreate = 0;
		CreateAmmoBaron();
	}

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
			Player::MainPlayer->SetCameraShaking(1.0f, 5.0f);
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

	// ?¿? ???? x
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
	Ex->SetSoundOff();
}

void Boss_Tank::Explosions(float4 _Value)
{
	Public_Boom* Ex = nullptr;

	Ex = GetLevel()->CreateActor<Public_Boom>();
	Ex->SetPos(_Value);
	Ex->SetExPlus(0);
	Ex->SetSoundOff();
}

void Boss_Tank::RandomCreateExplosion(float _DeltaTime)
{
	int Return = 0;
	int RandomNumber = rand();

	Return = RandomNumber % 10;

	if (0 == Return)
	{
		Explosions({ 1050, 400 });
	}
	else if (1 == Return)
	{
		Explosions({ 1090, 700 });
	}
	else if (2 == Return)
	{
		Explosions({ 1130, 550 });
	}
	else if (3 == Return)
	{
		Explosions({ 1170, 600 });
	}
	else if (4 == Return)
	{
		Explosions({ 1210, 450 });
	}
	else if (5 == Return)
	{
		Explosions({ 1250, 700 });
	}
	else if (6 == Return)
	{
		Explosions({ 1290, 450 });
	}
	else if (7 == Return)
	{
		Explosions({ 1330, 600 });
	}
	else if (8 == Return)
	{
		Explosions({ 1200, 500 });
	}
	else if (9 == Return)
	{
		Explosions({ 1360, 730 });
	}
	else
	{
		Explosions({ 0, 0 });
	}
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

int Boss_Tank::RandomNumberGeneration()
{
	srand(static_cast<unsigned int>(time(nullptr)));

	int Return = 0;
	int RandomNumber = rand();

	return Return = RandomNumber % 10;
}

void Boss_Tank::CreateAmmoBaron()
{
	Ammo = GetLevel()->CreateActor<AmmoBaron>();
	Baron = dynamic_cast<AmmoBaron*>(Ammo);
	Baron->SetPos({ 1200, 400 });
	Baron->SetColMap(ColMap);
}