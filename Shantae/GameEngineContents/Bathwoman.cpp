#include "Bathwoman.h"

#include <GameEngineCore/GameEngineRender.h>
#include <GameEngineCore/GameEngineCollision.h>
#include <GameEngineCore/GameEngineLevel.h>

#include "ContentsEnum.h"
#include "A_Button.h"

Bathwoman::Bathwoman() 
{
}

Bathwoman::~Bathwoman() 
{
}

void Bathwoman::Start()
{
	AnimationRender = CreateRender(RenderOrder::Monster);
	AnimationRender->SetScale({ 400, 400 });

	// Right
	AnimationRender->CreateAnimation({ .AnimationName = "Idle",  .ImageName = "Bathwoman.bmp", .Start = 0, .End = 10, .InterTime = 0.1f });

	BodyCollision = CreateCollision(CollisionOrder::Trigger);
	BodyCollision->SetDebugRenderType(CT_Rect);
	BodyCollision->SetScale({ 100, 100 });
	BodyCollision->SetPosition({ 50, -50 });

	AnimationRender->ChangeAnimation("Idle");
}

void Bathwoman::Update(float _DeltaTime)
{
	if (1 == CreateAButtion)
	{
		CreateAButtion = 0;
		AButton = nullptr;
		float4 AButtonPos = float4::Zero;
		AButtonPos = GetPos() + (float4::Up * 180);

		AButton = GetLevel()->CreateActor<A_Button>();
		AButton->SetPos(AButtonPos);
		AButton->Off();
	}

	CollisionCheck();
}

void Bathwoman::Render(float _DeltaTime)
{

}

void Bathwoman::CollisionCheck()
{
	if (nullptr != BodyCollision)
	{
		if (true == BodyCollision->Collision({ .TargetGroup = static_cast<int>(CollisionOrder::Player), .TargetColType = CT_Rect, .ThisColType = CT_Rect }))
		{
			AButton->On();
		}
		else
		{
			AButton->Off();
		}
	}
}