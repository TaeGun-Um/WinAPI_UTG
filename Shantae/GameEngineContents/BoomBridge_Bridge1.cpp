#include "BoomBridge_Bridge1.h"

#include <GameEngineCore/GameEngineResources.h>
#include <GameEngineCore/GameEngineCollision.h>
#include <GameEngineCore/GameEngineRender.h>
#include <GameEngineCore/GameEngineLevel.h>

#include "Public_Boom.h"
#include "ContentsEnum.h"

BoomBridge_Bridge1::BoomBridge_Bridge1() 
{
}

BoomBridge_Bridge1::~BoomBridge_Bridge1() 
{
}

void BoomBridge_Bridge1::Start()
{
	// Animation
	RenderSet();

	// Collision
	CollisionSet();
}

void BoomBridge_Bridge1::Update(float _DeltaTime)
{
	if (7.0f <= AccTime)
	{
		Kill();
	}
}
void BoomBridge_Bridge1::Render(float _DeltaTime)
{
}

void BoomBridge_Bridge1::Kill()
{
	GameEngineActor* ColActor = BodyCollision->GetActor();
	ColActor->Off();

	// BreakGround();

	ColActor->Death();
}

void BoomBridge_Bridge1::RenderSet()
{
	AnimationRender = CreateRender("BoomBridge_Bridge1.Bmp", RenderOrder::Map);
	AnimationRender->SetScale({ 350, 50 });
}

void BoomBridge_Bridge1::CollisionSet()
{
	BodyCollision = CreateCollision(CollisionOrder::Ground);
	BodyCollision->SetDebugRenderType(CT_Rect);
	BodyCollision->SetScale({ 350, 20 });
	BodyCollision->SetPosition({ 0, -15 });
}