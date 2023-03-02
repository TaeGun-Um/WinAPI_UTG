#include "IDCard.h"

#include <GameEngineCore/GameEngineCollision.h>
#include <GameEngineCore/GameEngineRender.h>

#include "ContentsEnum.h"
#include "Inventory.h"
#include "Player.h"

IDCard::IDCard() 
{
}

IDCard::~IDCard() 
{
}

void IDCard::Start()
{
	AnimationRender = CreateRender(RenderOrder::Object);
	AnimationRender->SetScale({ 200, 200 });

	AnimationRender->CreateAnimation({ .AnimationName = "Pass",  .ImageName = "Items.bmp", .Start = 10, .End = 10, .InterTime = 10.0f, .Loop = false });

	BodyCollision = CreateCollision(CollisionOrder::Equip);
	BodyCollision->SetDebugRenderType(CT_Rect);
	BodyCollision->SetScale({ 50, 50 });
	BodyCollision->SetPosition({ -2.5f, 5 });
	BodyCollision->Off();

	AnimationRender->ChangeAnimation("Pass");
}

void IDCard::Update(float _DeltaTime)
{
	if (1 == UpCount)
	{
		UpCount = 0;
		UpPos = GetPos() + float4::Up * 30.0f;;
	}

	MoveCalculation(_DeltaTime);
	CollisionCheck(_DeltaTime);
}

void IDCard::Render(float _DeltaTime)
{

}

void IDCard::MoveCalculation(float _DeltaTime)
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

void IDCard::CollisionCheck(float _DeltaTime)
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

void IDCard::ApplyScore()
{
	Player::MainPlayer->SetPlayerIDCard(1);
	Player::MainPlayer->SetItemEquip(true);
	Inventory::PlayerInven->SetEquipItem("IDCard");
	Kill();
}

void IDCard::Kill()
{
	GameEngineActor* ColActor = AnimationRender->GetActor();
	ColActor->Off();
	ColActor->Death();
}