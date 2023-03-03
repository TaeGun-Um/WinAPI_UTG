#include "PikeBallEffect.h"

#include <GameEngineCore/GameEngineResources.h>
#include <GameEngineCore/GameEngineCollision.h>
#include <GameEngineCore/GameEngineRender.h>

#include "ContentsEnum.h"
#include "Player.h"

PikeBallEffect::PikeBallEffect() 
{
}

PikeBallEffect::~PikeBallEffect() 
{
}

void PikeBallEffect::Start()
{
	// Animation
	AnimationRender = CreateRender("PikeBall.Bmp", RenderOrder::Effect);
	AnimationRender->SetScale({ 400, 400 });

	// Collision
	BodyCollision = CreateCollision(CollisionOrder::PlayerAttack);
	BodyCollision->SetDebugRenderType(CT_Rect);
	BodyCollision->SetScale({ 50, 50 });
	BodyCollision->SetPosition({ 0, 0 });
}

void PikeBallEffect::Update(float _DeltaTime)
{
	if (1 == PivotSet)
	{
		PivotSet = 0;
		PivotPoint = Player::MainPlayer->GetPos() + float4::Up * 60;
		SetPos(Player::MainPlayer->GetPos() + float4::Up * 120);
	}

	MoveCalculation(_DeltaTime);
}
void PikeBallEffect::Render(float _DeltaTime)
{

}

void PikeBallEffect::MoveCalculation(float _DeltaTime)
{
	NewPos = Player::MainPlayer->GetPos() - PivotPoint;
	BodyCollision->SetPosition({ 0, 0 });

	RotationTime += _DeltaTime;
	if (0.1f <= RotationTime)
	{
		Angle += 1.0f;
	}
	
	float4 Dir = float4::AngleToDirection2DToDeg(Angle);
	AnimationRender->SetPosition(NewPos + Dir * 120.0f);
	BodyCollision->SetPosition(NewPos + Dir * 120.0f);
}

void PikeBallEffect::Kill()
{
	GameEngineActor* ColActor = BodyCollision->GetActor();
	ColActor->Off();
	ColActor->Death();
}