#include "Boss_Mob.h"

#include <GameEngineCore/GameEngineResources.h>
#include <GameEngineCore/GameEngineCollision.h>
#include <GameEngineCore/GameEngineRender.h>

#include "ContentsEnum.h"

Boss_Mob::Boss_Mob() 
{
}

Boss_Mob::~Boss_Mob() 
{
}

void Boss_Mob::Start()
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

	// 좌우 구분 x
	AnimationRender->CreateAnimation({ .AnimationName = "ALL",  .ImageName = "Boos.bmp", .Start = 0, .End = 36, .InterTime = 0.1f });
	AnimationRender->CreateAnimation({ .AnimationName = "Idle",  .ImageName = "Boos.bmp", .Start = 0, .End = 6, .InterTime = 0.1f });

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

void Boss_Mob::Update(float _DeltaTime)
{

}
void Boss_Mob::Render(float _DeltaTime)
{

}