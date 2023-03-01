#include "Gem.h"

#include <GameEngineCore/GameEngineRender.h>
#include <GameEngineCore/GameEngineCollision.h>

#include "ContentsEnum.h"

Gem::Gem() 
{
}

Gem::~Gem() 
{
}

void Gem::Start()
{
	AnimationRender = CreateRender(RenderOrder::Object);
	AnimationRender->SetScale({ 400, 400 });

	AnimationRender->CreateAnimation({ .AnimationName = "Blue",  .ImageName = "Gem.bmp", .Start = 0, .End = 4, .InterTime = 0.1f });
	AnimationRender->CreateAnimation({ .AnimationName = "Blue_Big",  .ImageName = "Gem.bmp", .Start = 5, .End = 9, .InterTime = 0.1f });
	AnimationRender->CreateAnimation({ .AnimationName = "Green",  .ImageName = "Gem.bmp", .Start = 10, .End = 14, .InterTime = 0.1f });
	AnimationRender->CreateAnimation({ .AnimationName = "Green_Big",  .ImageName = "Gem.bmp", .Start = 15, .End = 19, .InterTime = 0.1f });
	AnimationRender->CreateAnimation({ .AnimationName = "Pupple",  .ImageName = "Gem.bmp", .Start = 20, .End = 24, .InterTime = 0.1f });
	AnimationRender->CreateAnimation({ .AnimationName = "Pupple_Big",  .ImageName = "Gem.bmp", .Start = 25, .End = 29, .InterTime = 0.1f });
	AnimationRender->CreateAnimation({ .AnimationName = "Red",  .ImageName = "Gem.bmp", .Start = 30, .End = 34, .InterTime = 0.1f });
	AnimationRender->CreateAnimation({ .AnimationName = "Red_Big",  .ImageName = "Gem.bmp", .Start = 35, .End = 39, .InterTime = 0.1f });
	AnimationRender->CreateAnimation({ .AnimationName = "Yellow",  .ImageName = "Gem.bmp", .Start = 40, .End = 44, .InterTime = 0.1f });
	AnimationRender->CreateAnimation({ .AnimationName = "Yellow_Big",  .ImageName = "Gem.bmp", .Start = 45, .End = 49, .InterTime = 0.1f });

	BodyCollision = CreateCollision(CollisionOrder::Item);
	BodyCollision->SetDebugRenderType(CT_Rect);
	BodyCollision->SetScale({ 25, 50 });
	BodyCollision->SetPosition({ 0, -25 });

	AnimationRender->ChangeAnimation("Blue");
}

void Gem::Update(float _DeltaTime)
{
	MoveCalculation(_DeltaTime);
	CollisionCheck(_DeltaTime);
}

void Gem::Render(float _DeltaTime)
{

}

// 중력, 점프, 맵타일
void Gem::MoveCalculation(float _DeltaTime)
{
	if (true == IsStart)
	{
		IsStart = false;
		MoveDir.y -= 800.0f;
	}

	MoveDir += float4::Down * 1500.0f * _DeltaTime;

	NextPos = GetPos() + MoveDir * _DeltaTime;

	if (nullptr == ColMap)
	{
		MsgAssert("충돌용 맵 이미지가 없습니다.");
	}

	if (RGB(0, 248, 0) == ColMap->GetPixelColor(NextPos, RGB(0, 0, 0)))
	{
		MoveDir = float4::Zero;
	}

	if (RGB(74, 65, 42) == ColMap->GetPixelColor(NextPos, RGB(0, 0, 0)))
	{
		MoveDir = float4::Zero;
	}

	SetMove(MoveDir * _DeltaTime);
}

void Gem::CollisionCheck(float _DeltaTime)
{
	if (nullptr != BodyCollision)
	{
		if (true == BodyCollision->Collision({ .TargetGroup = static_cast<int>(CollisionOrder::PlayerEffect), .TargetColType = CT_Rect, .ThisColType = CT_Rect }))
		{
			BodyCollision->Off();

			if (1 == SoundCount)
			{
				SoundCount = 0;
				BGMPlayer = GameEngineResources::GetInst().SoundPlayToControl("Player_gem.wav");
				BGMPlayer.Volume(0.2f);
				BGMPlayer.LoopCount(1);
			}

			Kill();
		}
	}
}

void Gem::Kill()
{
	GameEngineActor* ColActor = AnimationRender->GetActor();
	ColActor->Off();
	ColActor->Death();
}