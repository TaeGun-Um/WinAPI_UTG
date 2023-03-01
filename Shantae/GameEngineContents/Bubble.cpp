#include "Bubble.h"

#include <GameEngineCore/GameEngineCollision.h>
#include <GameEngineCore/GameEngineRender.h>

#include "ContentsEnum.h"
#include "Player.h"

Bubble::Bubble() 
{
}

Bubble::~Bubble() 
{
}

void Bubble::Start()
{
	AnimationRender = CreateRender(RenderOrder::Object);
	AnimationRender->SetScale({ 200, 200 });

	AnimationRender->CreateAnimation({ .AnimationName = "Bubble",  .ImageName = "Items.bmp", .Start = 5, .End = 5, .InterTime = 10.0f, .Loop = false });

	BodyCollision = CreateCollision(CollisionOrder::Equip);
	BodyCollision->SetDebugRenderType(CT_Rect);
	BodyCollision->SetScale({ 40, 40 });
	BodyCollision->SetPosition({ 0, -20 });
	BodyCollision->Off();

	AnimationRender->ChangeAnimation("Bubble");
}

void Bubble::Update(float _DeltaTime)
{
	MoveCalculation(_DeltaTime);
	CollisionCheck(_DeltaTime);
}

void Bubble::Render(float _DeltaTime)
{

}

void Bubble::MoveCalculation(float _DeltaTime)
{

}

void Bubble::CollisionCheck(float _DeltaTime)
{
	//if (//)
	//{
	//	BodyCollision->On();
	//}

	if (nullptr != BodyCollision)
	{
		if (true == BodyCollision->Collision({ .TargetGroup = static_cast<int>(CollisionOrder::PlayerEffect), .TargetColType = CT_Rect, .ThisColType = CT_Rect }))
		{
			BodyCollision->Off();

			if (1 == SoundCount)
			{
				SoundCount = 0;
				BGMPlayer = GameEngineResources::GetInst().SoundPlayToControl("Player_gem.wav");
				BGMPlayer.Volume(0.1f);
				BGMPlayer.LoopCount(1);
			}

			ApplyScore();
		}
	}
}

void Bubble::ApplyScore()
{
	// Player::MainPlayer->SetPlayerGem(Score); 획득시 플레이어 인벤토리의 옥토퍼스 카운트를 하나 증가시킨다.
	Kill();
}

void Bubble::Kill()
{
	GameEngineActor* ColActor = AnimationRender->GetActor();
	ColActor->Off();
	ColActor->Death();
}