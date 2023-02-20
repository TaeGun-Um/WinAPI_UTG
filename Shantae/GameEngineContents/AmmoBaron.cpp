#include "AmmoBaron.h"

#include <GameEngineCore/GameEngineResources.h>
#include <GameEngineCore/GameEngineCollision.h>
#include <GameEngineCore/GameEngineRender.h>

#include "ContentsEnum.h"

AmmoBaron::AmmoBaron() 
{
}

AmmoBaron::~AmmoBaron() 
{
}

void AmmoBaron::Start()
{
	RenderSet();
	CollisionSet();

	AnimationRender->ChangeAnimation("Struggle");
}

void AmmoBaron::Update(float _DeltaTime)
{
	CollisionCheck();
}
void AmmoBaron::Render(float _DeltaTime)
{

}

void AmmoBaron::MoveCalculation(float _DeltaTime)
{

}

void AmmoBaron::CollisionCheck()
{

}

void AmmoBaron::RenderSet()
{
	AnimationRender = CreateRender(RenderOrder::Monster);
	AnimationRender->SetScale({ 400, 400 });

	AnimationRender->CreateAnimation({ .AnimationName = "Idle",  .ImageName = "AmmoBaron_R.bmp", .Start = 0, .End = 9, .InterTime = 0.1f });
	AnimationRender->CreateAnimation({ .AnimationName = "Run",  .ImageName = "AmmoBaron_R.bmp", .Start = 10, .End = 13, .InterTime = 0.1f });
	AnimationRender->CreateAnimation({ .AnimationName = "Move",  .ImageName = "AmmoBaron_R.bmp", .Start = 14, .End = 21, .InterTime = 0.1f });
	AnimationRender->CreateAnimation({ .AnimationName = "Jump",  .ImageName = "AmmoBaron_R.bmp", .Start = 22, .End = 23, .InterTime = 0.1f });
	AnimationRender->CreateAnimation({ .AnimationName = "Fly",  .ImageName = "AmmoBaron_R.bmp", .Start = 24, .End = 29, .InterTime = 0.1f });
	AnimationRender->CreateAnimation({ .AnimationName = "Down",  .ImageName = "AmmoBaron_R.bmp", .Start = 30, .End = 36, .InterTime = 0.1f });
	AnimationRender->CreateAnimation({ .AnimationName = "Standup",  .ImageName = "AmmoBaron_R.bmp", .Start = 37, .End = 43, .InterTime = 0.1f });
	AnimationRender->CreateAnimation({ .AnimationName = "Struggle",  .ImageName = "AmmoBaron_R.bmp", .Start = 44, .End = 51, .InterTime = 0.1f });
	AnimationRender->CreateAnimation({ .AnimationName = "Dustoff",  .ImageName = "AmmoBaron_R.bmp", .Start = 59, .End = 71, .InterTime = 0.1f });
}

void AmmoBaron::CollisionSet()
{
	BodyCollision = CreateCollision(CollisionOrder::Monster);
	BodyCollision->SetDebugRenderType(CT_Rect);
	BodyCollision->SetScale({ 50, 55 });
	BodyCollision->SetPosition({ 0, -27.5f });
}
