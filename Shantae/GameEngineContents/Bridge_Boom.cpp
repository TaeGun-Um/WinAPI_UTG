#include "Bridge_Boom.h"

#include <GameEngineCore/GameEngineResources.h>
#include <GameEngineCore/GameEngineCollision.h>
#include <GameEngineCore/GameEngineRender.h>
#include <GameEngineCore/GameEngineLevel.h>

#include "ContentsEnum.h"
#include "Public_Boom.h"

Bridge_Boom::Bridge_Boom() 
{
}

Bridge_Boom::~Bridge_Boom() 
{
}

void Bridge_Boom::Start()
{
	// Animation
	AnimationRender = CreateRender(RenderOrder::Effect);
	AnimationRender->SetScale({ 400, 400 });
	AnimationRender->CreateAnimation({ .AnimationName = "Basic",  .ImageName = "Bridge_Boom.bmp", .Start = 0, .End = 2, .InterTime = 0.1f });
	AnimationRender->CreateAnimation({ .AnimationName = "On",  .ImageName = "Bridge_Boom.bmp", .Start = 0, .End = 2, .InterTime = 0.035f });

	AnimationRender->ChangeAnimation("Basic");
}
void Bridge_Boom::Update(float _DeltaTime)
{
	if (5.0f <= AccTime)
	{
		AnimationRender->ChangeAnimation("On");
	}
	
	if (7.0f <= AccTime)
	{
		Kill();
	}
}

void Bridge_Boom::Kill()
{
	GameEngineActor* ColActor = AnimationRender->GetActor();
	ColActor->Off();

	Explosion();

	ColActor->Death();
}

void Bridge_Boom::Explosion()
{
	Public_Boom* Ex = nullptr;
	float4 ExPos = float4::Zero;
	ExPos = GetPos() + (float4::Down * 20);

	Ex = GetLevel()->CreateActor<Public_Boom>();
	Ex->SetPos(ExPos);
}

void Bridge_Boom::Render(float _DeltaTime)
{
}