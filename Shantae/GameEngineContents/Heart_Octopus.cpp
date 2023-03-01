#include "Heart_Octopus.h"

#include <GameEngineCore/GameEngineRender.h>
#include <GameEngineCore/GameEngineCollision.h>

#include "ContentsEnum.h"
#include "Player.h"

Heart_Octopus::Heart_Octopus() 
{
}

Heart_Octopus::~Heart_Octopus() 
{
}

void Heart_Octopus::Start()
{
	AnimationRender = CreateRender(RenderOrder::Object);
	AnimationRender->SetScale({ 400, 400 });

	AnimationRender->CreateAnimation({ .AnimationName = "Octopus",  .ImageName = "Heart_Octopus.bmp", .Start = 0, .End = 4, .InterTime = 0.1f });


	BodyCollision = CreateCollision(CollisionOrder::Equip);
	BodyCollision->SetDebugRenderType(CT_Rect);
	BodyCollision->SetScale({ 60, 60 });
	BodyCollision->SetPosition({ 0, -30 });
	BodyCollision->Off();

	AnimationRender->ChangeAnimation("Octopus");
}

void Heart_Octopus::Update(float _DeltaTime)
{
	MoveCalculation(_DeltaTime);
	CollisionCheck(_DeltaTime);
}

void Heart_Octopus::Render(float _DeltaTime)
{

}

void Heart_Octopus::MoveCalculation(float _DeltaTime)
{
	if (true == IsStart)
	{
		IsStart = false;
		MoveDir.y -= Jump;
	}

	MoveDir += float4::Down * 2000.0f * _DeltaTime;

	NextPos = GetPos() + MoveDir * _DeltaTime;

	if (nullptr == ColMap)
	{
		MsgAssert("충돌용 맵 이미지가 없습니다.");
	}

	if (RGB(0, 248, 0) == ColMap->GetPixelColor(NextPos, RGB(0, 0, 0)))
	{
		MoveDir.y = 0.0f;
		IsStart = true;
		Jump /= 2;
		if (250.0f <= Jump)
		{
			Jump = 250.0f;
		}
	}

	if (RGB(74, 65, 42) == ColMap->GetPixelColor(NextPos, RGB(0, 0, 0)))
	{
		MoveDir.y = 0.0f;
		IsStart = true;
		Jump /= 2;
		if (250.0f <= Jump)
		{
			Jump = 250.0f;
		}
	}

	SetMove(MoveDir * _DeltaTime);
}

void Heart_Octopus::CollisionCheck(float _DeltaTime)
{
	if (10 >= Jump)
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
				BGMPlayer = GameEngineResources::GetInst().SoundPlayToControl("Player_hp_large.wav");
				BGMPlayer.Volume(0.1f);
				BGMPlayer.LoopCount(1);
			}

			ApplyScore();
		}
	}
}

void Heart_Octopus::ApplyScore()
{
	//Player::MainPlayer->SetPlayerGem(Score);
	Kill();
}

void Heart_Octopus::Kill()
{
	GameEngineActor* ColActor = AnimationRender->GetActor();
	ColActor->Off();
	ColActor->Death();
}