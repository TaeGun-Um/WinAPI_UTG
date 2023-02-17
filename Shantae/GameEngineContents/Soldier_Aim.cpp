#include "Soldier_Aim.h"

#include <GameEngineCore/GameEngineResources.h>
#include <GameEngineCore/GameEngineCollision.h>
#include <GameEngineCore/GameEngineRender.h>

#include "ContentsEnum.h"

#include "Machinegun_Plat.h"

Soldier_Aim::Soldier_Aim() 
{
}

Soldier_Aim::~Soldier_Aim() 
{
}

void Soldier_Aim::Start()
{
	// Animation
	AnimationRender = CreateRender(RenderOrder::Effect);
	AnimationRender->SetScale({ 400, 400 });
	AnimationRender->CreateAnimation({ .AnimationName = "On",  .ImageName = "Soldier_Aim.bmp", .Start = 0, .End = 1, .InterTime = 0.1f });

	AnimationRender->ChangeAnimation("On");
}
void Soldier_Aim::Update(float _DeltaTime)
{
	if (true == IsDeath)
	{
		GameEngineActor* ColActor = AnimationRender->GetActor();
		ColActor->Death();
	}
}

void Soldier_Aim::Render(float _DeltaTime)
{
}