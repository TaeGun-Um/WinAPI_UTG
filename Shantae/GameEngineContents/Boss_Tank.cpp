#include "Boss_Tank.h"

#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineResources.h>
#include <GameEngineCore/GameEngineCollision.h>
#include <GameEngineCore/GameEngineRender.h>

#include "ContentsEnum.h"

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
}

void Boss_Tank::Update(float _DeltaTime)
{
	if (GameEngineInput::IsDown("MonsterTest"))
	{
		if (0 == Test)
		{
			Test = 1;
			Fire(_DeltaTime);
		}
		else if (1 == Test)
		{
			Test = 0;
			Charge(_DeltaTime);
		}
	}
}
void Boss_Tank::Render(float _DeltaTime)
{

}

// Animation
void Boss_Tank::RenderSet()
{
	// Animation
	AnimationRender = CreateRender(RenderOrder::Monster);
	AnimationRender->SetScale({ 1500, 1500 });
	AnimationRender->SetPosition({ 1200, 750 });
	
	BossPos = { 1200, 750 };

	// ÁÂ¿ì ±¸ºÐ x
	AnimationRender->CreateAnimation({ .AnimationName = "Idle",  .ImageName = "Boss_Tank.bmp", .Start = 0, .End = 3, .InterTime = 0.08f });
	AnimationRender->CreateAnimation({ .AnimationName = "Move",  .ImageName = "Boss_Tank.bmp", .Start = 8, .End = 11, .InterTime = 0.08f });
	AnimationRender->CreateAnimation({ .AnimationName = "BackUp",  .ImageName = "Boss_Tank.bmp", .Start = 12, .End = 15, .InterTime = 0.08f });
	AnimationRender->CreateAnimation({ .AnimationName = "Fire",  .ImageName = "Boss_Tank.bmp", .Start = 16, .End = 22, .InterTime = 0.08f });
	AnimationRender->CreateAnimation({ .AnimationName = "Dead_Idle",  .ImageName = "Boss_Tank.bmp", .Start = 31, .End = 31, .InterTime = 0.1f, .Loop = false });
	AnimationRender->CreateAnimation({ .AnimationName = "Empty",  .ImageName = "Boss_Tank.bmp", .Start = 32, .End = 32, .InterTime = 0.1f, .Loop = false });
}

// Collision
void Boss_Tank::CollisionSet()
{
	// Collision
	BodyCollision = CreateCollision(CollisionOrder::Monster);
	BodyCollision->SetDebugRenderType(CT_Rect);
	BodyCollision->SetScale({ 750, 750 });
	BodyCollision->SetPosition({ 0, 0 });
}

void Boss_Tank::Fire(float _DeltaTime)
{
	//
}

void Boss_Tank::Charge(float _DeltaTime)
{
	//
}
