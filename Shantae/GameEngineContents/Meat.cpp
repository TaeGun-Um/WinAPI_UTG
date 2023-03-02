#include "Meat.h"

#include <GameEngineCore/GameEngineCollision.h>
#include <GameEngineCore/GameEngineRender.h>

#include "ContentsEnum.h"
#include "Inventory.h"
#include "Player.h"

Meat::Meat() 
{
}

Meat::~Meat() 
{
}

void Meat::Start()
{
	AnimationRender = CreateRender(RenderOrder::Object);
	AnimationRender->SetScale({ 200, 200 });

	AnimationRender->CreateAnimation({ .AnimationName = "Meat",  .ImageName = "Items.bmp", .Start = 2, .End = 2, .InterTime = 10.0f, .Loop = false });

	BodyCollision = CreateCollision(CollisionOrder::Equip);
	BodyCollision->SetDebugRenderType(CT_Rect);
	BodyCollision->SetScale({ 50, 50 });
	BodyCollision->SetPosition({ -2.5f, 5 });
	BodyCollision->Off();

	AnimationRender->ChangeAnimation("Meat");
}

void Meat::Update(float _DeltaTime)
{
	if (1 == UpCount)
	{
		UpCount = 0;
		UpPos = GetPos() + float4::Up * 30.0f;;
	}

	MoveCalculation(_DeltaTime);
	CollisionCheck(_DeltaTime);
}

void Meat::Render(float _DeltaTime)
{

}

void Meat::MoveCalculation(float _DeltaTime)
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

void Meat::CollisionCheck(float _DeltaTime)
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

void Meat::ApplyScore()
{
	Player::MainPlayer->PlusPlayerMeat(1);
	Player::MainPlayer->SetItemEquip(true);
	Inventory::PlayerInven->SetEquipItem("Meat");
	Kill();
}

void Meat::Kill()
{
	GameEngineActor* ColActor = AnimationRender->GetActor();
	ColActor->Off();
	ColActor->Death();
}