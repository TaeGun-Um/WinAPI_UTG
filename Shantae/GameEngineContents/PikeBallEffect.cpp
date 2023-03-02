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
	BodyCollision = CreateCollision(CollisionOrder::PikeBall);
	BodyCollision->SetDebugRenderType(CT_Rect);
	BodyCollision->SetScale({ 50, 50 });
	BodyCollision->SetPosition({ 0, 0 });
}

void PikeBallEffect::Update(float _DeltaTime)
{
	MoveCalculation(_DeltaTime);
}
void PikeBallEffect::Render(float _DeltaTime)
{

}

void PikeBallEffect::MoveCalculation(float _DeltaTime)
{
	SetPos(Player::MainPlayer->GetPos() + float4::Up * 180);
}

void PikeBallEffect::Kill()
{
	GameEngineActor* ColActor = BodyCollision->GetActor();
	ColActor->Off();
	ColActor->Death();
}