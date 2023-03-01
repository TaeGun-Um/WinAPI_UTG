#include "TimerCollision.h"

#include <GameEngineBase/GameEngineDebug.h>
#include <GameEngineCore/GameEngineResources.h>
#include <GameEngineCore/GameEngineCollision.h>
#include <GameEngineCore/GameEngineRender.h>
#include <GameEngineCore/GameEngineLevel.h>

#include "ContentsEnum.h"

TimerCollision* TimerCollision::Timer = nullptr;

TimerCollision::TimerCollision() 
{
}

TimerCollision::~TimerCollision() 
{
}

void TimerCollision::Start()
{
	Timer = this;

	// Collision
	TimerSpot = CreateCollision(CollisionOrder::Spawner);
	TimerSpot->SetDebugRenderType(CT_Rect);
	TimerSpot->SetScale({ 1200, 100 });
	TimerSpot->SetPosition({ 0, 0 });

}

void TimerCollision::Update(float _DeltaTime)
{
	if (0 == TimerSet)
	{
		AccTime += _DeltaTime;
	}

	CollisionCheck();
}

void TimerCollision::CollisionCheck()
{
	if (nullptr != TimerSpot)
	{
		if (true == TimerSpot->Collision({ .TargetGroup = static_cast<int>(CollisionOrder::PlayerEffect), .TargetColType = CT_Rect, .ThisColType = CT_Rect }))
		{
			TimerSet = 0;
		}
	}
}
