#include "PikeBall.h"

#include <GameEngineCore/GameEngineCollision.h>
#include <GameEngineCore/GameEngineRender.h>

#include "ContentsEnum.h"
#include "Inventory.h"
#include "Player.h"

PikeBall::PikeBall() 
{
}

PikeBall::~PikeBall() 
{
}

void PikeBall::Start()
{
	AnimationRender = CreateRender(RenderOrder::Object);
	AnimationRender->SetScale({ 200, 200 });

	AnimationRender->CreateAnimation({ .AnimationName = "PikeBall",  .ImageName = "Items.bmp", .Start = 6, .End = 6, .InterTime = 10.0f, .Loop = false });

	BodyCollision = CreateCollision(CollisionOrder::Equip);
	BodyCollision->SetDebugRenderType(CT_Rect);
	BodyCollision->SetScale({ 50, 50 });
	BodyCollision->SetPosition({ -2.5f, 5 });
	BodyCollision->Off();

	AnimationRender->ChangeAnimation("PikeBall");
}

void PikeBall::Update(float _DeltaTime)
{
	if (1 == UpCount)
	{
		UpCount = 0;
		UpPos = GetPos() + float4::Up * 30.0f;;
	}

	MoveCalculation(_DeltaTime);
	CollisionCheck(_DeltaTime);
}

void PikeBall::Render(float _DeltaTime)
{

}

void PikeBall::MoveCalculation(float _DeltaTime)
{
	if (GetPos().y >= UpPos.y)
	{
		SetMove(float4::Up * 50 * _DeltaTime);
	}
	else
	{
		IsUp = true;
	}
}

void PikeBall::CollisionCheck(float _DeltaTime)
{
	if (true == IsUp)
	{
		BodyCollision->On();
	}

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

void PikeBall::ApplyScore()
{
	Player::MainPlayer->PlusPlayerPikeBall(1);
	Player::MainPlayer->SetItemEquip(true);
	Inventory::PlayerInven->SetEquipItem("PikeBall");
	Kill();
}

void PikeBall::Kill()
{
	GameEngineActor* ColActor = AnimationRender->GetActor();
	ColActor->Off();
	ColActor->Death();
}
