#include "Scarecrow_Black.h"

#include <GameEngineCore/GameEngineResources.h>
#include <GameEngineCore/GameEngineCollision.h>
#include <GameEngineCore/GameEngineRender.h>

#include "ContentsEnum.h"

Scarecrow_Black::Scarecrow_Black() 
{
}

Scarecrow_Black::~Scarecrow_Black() 
{
}

void Scarecrow_Black::Start()
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
	AnimationRender->CreateAnimation({ .AnimationName = "ALL",  .ImageName = "Scarecrow_Black_R.bmp", .Start = 0, .End = 64, .InterTime = 0.1f });
	AnimationRender->CreateAnimation({ .AnimationName = "Idle_R",  .ImageName = "Scarecrow_Black_R.bmp", .Start = 0, .End = 6, .InterTime = 0.1f });

	// Left
	AnimationRender->CreateAnimation({ .AnimationName = "Idle_L",  .ImageName = "Scarecrow_Black_L.bmp", .Start = 0, .End = 6, .InterTime = 0.1f });

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

void Scarecrow_Black::Update(float _DeltaTime)
{

}
void Scarecrow_Black::Render(float _DeltaTime)
{

}