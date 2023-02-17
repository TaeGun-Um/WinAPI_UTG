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
	SetPos({ 477, 615 });

	// 숫자
	// TestNumber.SetOwner(this);
	// TestNumber.SetImage("Numbers.Bmp", { 26, 35 }, 10, RGB(255, 0, 255), "GemWindow.bmp");
	// TestNumber.SetValue(Value);
	// TestNumber.SetAlign(Align::Right);
	// TestNumber.SetRenderPos({300, -600});
	// TestNumber.SetCameraEffect(true);

	// Animation
	AnimationRender = CreateRender(RenderOrder::Monster);
	AnimationRender->SetScale({ 400, 400 });

	// Right
	AnimationRender->CreateAnimation({ .AnimationName = "ALL",  .ImageName = "AmmoBaron_R.bmp", .Start = 0, .End = 71, .InterTime = 0.1f });
	AnimationRender->CreateAnimation({ .AnimationName = "Idle_R",  .ImageName = "AmmoBaron_R.bmp", .Start = 0, .End = 6, .InterTime = 0.1f });

	// Left
	AnimationRender->CreateAnimation({ .AnimationName = "Idle_L",  .ImageName = "AmmoBaron_L.bmp", .Start = 0, .End = 6, .InterTime = 0.1f });

	// Collision
	BodyCollision = CreateCollision(CollisionOrder::Monster);
	BodyCollision->SetScale({ 50, 50 });

	// Text(예시; 0206 추가)
	//GameEngineRender* Render = CreateRender(RenderOrder::Monster);
	//Render->SetText("1234");

	// state
	// ChangeState(MonsterState::IDLE);
	AnimationRender->ChangeAnimation("ALL");
}

void AmmoBaron::Update(float _DeltaTime)
{

}
void AmmoBaron::Render(float _DeltaTime)
{

}