#include "Gem.h"

#include <GameEngineBase/GameEngineRandom.h>
#include <GameEngineCore/GameEngineRender.h>
#include <GameEngineCore/GameEngineCollision.h>

#include "ContentsEnum.h"
#include "Player.h"

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
	AnimationRender->CreateAnimation({ .AnimationName = "Green",  .ImageName = "Gem.bmp", .Start = 10, .End = 14, .InterTime = 0.1f });
	AnimationRender->CreateAnimation({ .AnimationName = "Pupple",  .ImageName = "Gem.bmp", .Start = 20, .End = 24, .InterTime = 0.1f });
	AnimationRender->CreateAnimation({ .AnimationName = "Red",  .ImageName = "Gem.bmp", .Start = 30, .End = 34, .InterTime = 0.1f });
	AnimationRender->CreateAnimation({ .AnimationName = "Yellow",  .ImageName = "Gem.bmp", .Start = 40, .End = 44, .InterTime = 0.1f });
	AnimationRender->CreateAnimation({ .AnimationName = "Blue_Big",  .ImageName = "Gem.bmp", .Start = 5, .End = 9, .InterTime = 0.1f });
	AnimationRender->CreateAnimation({ .AnimationName = "Green_Big",  .ImageName = "Gem.bmp", .Start = 15, .End = 19, .InterTime = 0.1f });
	AnimationRender->CreateAnimation({ .AnimationName = "Pupple_Big",  .ImageName = "Gem.bmp", .Start = 25, .End = 29, .InterTime = 0.1f });
	AnimationRender->CreateAnimation({ .AnimationName = "Red_Big",  .ImageName = "Gem.bmp", .Start = 35, .End = 39, .InterTime = 0.1f });
	AnimationRender->CreateAnimation({ .AnimationName = "Yellow_Big",  .ImageName = "Gem.bmp", .Start = 45, .End = 49, .InterTime = 0.1f });

	BodyCollision = CreateCollision(CollisionOrder::Item);
	BodyCollision->SetDebugRenderType(CT_Rect);
	BodyCollision->SetScale({ 25, 45 });
	BodyCollision->SetPosition({ 0, -22.5f });

	AnimationRender->ChangeAnimation("Blue");
}

void Gem::Update(float _DeltaTime)
{
	if (1 == CreateSet)
	{
		CreateSet = 0;
		GemSetting();
	}
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
		if (400.0f <= Jump)
		{
			Jump = 400.0f;
		}
	}

	if (RGB(74, 65, 42) == ColMap->GetPixelColor(NextPos, RGB(0, 0, 0)))
	{
		MoveDir.y = 0.0f;
		IsStart = true;
		Jump /= 2;
		if (400.0f <= Jump)
		{
			Jump = 400.0f;
		}
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

			ApplyScore();
		}
	}
}

void Gem::GemSetting()
{
	int RandC = GameEngineRandom::MainRandom.RandomInt(1, 100);

	if (1 <= RandC && RandC <= 15)
	{
		CreateGem = GemState::Blue;
	}
	else if (16 <= RandC && RandC <= 30)
	{
		CreateGem = GemState::Green;
	}
	else if (31 <= RandC && RandC <= 45)
	{
		CreateGem = GemState::Pupple;
	}
	else if (46 <= RandC && RandC <= 60)
	{
		CreateGem = GemState::Red;
	}
	else if (61 <= RandC && RandC <= 75)
	{
		CreateGem = GemState::Yellow;
	}
	else if (76 <= RandC && RandC <= 80)
	{
		CreateGem = GemState::Blue_Big;
	}
	else if (81 <= RandC && RandC <= 85)
	{
		CreateGem = GemState::Green_Big;
	}
	else if (86 <= RandC && RandC <= 90)
	{
		CreateGem = GemState::Pupple_Big;
	}
	else if (91 <= RandC && RandC <= 95)
	{
		CreateGem = GemState::Red_Big;
	}
	else
	{
		CreateGem = GemState::Yellow_Big;
	}
	
	switch (CreateGem)
	{
	case GemState::Blue:
		AnimationRender->ChangeAnimation("Blue");
		Score = 1;
		break;
	case GemState::Green:
		AnimationRender->ChangeAnimation("Green");
		Score = 2;
		break;
	case GemState::Pupple:
		AnimationRender->ChangeAnimation("Pupple");
		Score = 3;
		break;
	case GemState::Red:
		AnimationRender->ChangeAnimation("Red");
		Score = 4;
		break;
	case GemState::Yellow:
		AnimationRender->ChangeAnimation("Yellow");
		Score = 5;
		break;
	case GemState::Blue_Big:
		AnimationRender->ChangeAnimation("Blue_Big");
		Score = 10;
		BodyCollision->SetScale({ 30, 45 });
		BodyCollision->SetPosition({ 0, -22.5f });
		break;
	case GemState::Green_Big:
		AnimationRender->ChangeAnimation("Green_Big");
		Score = 15;
		BodyCollision->SetScale({ 30, 45 });
		BodyCollision->SetPosition({ 0, -22.5f });
		break;
	case GemState::Pupple_Big:
		AnimationRender->ChangeAnimation("Pupple_Big");
		Score = 20;
		BodyCollision->SetScale({ 30, 45 });
		BodyCollision->SetPosition({ 0, -22.5f });
		break;
	case GemState::Red_Big:
		AnimationRender->ChangeAnimation("Red_Big");
		Score = 25;
		BodyCollision->SetScale({ 30, 45 });
		BodyCollision->SetPosition({ 0, -22.5f });
		break;
	case GemState::Yellow_Big:
		AnimationRender->ChangeAnimation("Yellow_Big");
		Score = 30;
		BodyCollision->SetScale({ 30, 45 });
		BodyCollision->SetPosition({ 0, -22.5f });
		break;
	default:
		break;
	}
}

void Gem::ApplyScore()
{
	Player::MainPlayer->SetPlayerGem(Score);
	Kill();
}

void Gem::Kill()
{
	GameEngineActor* ColActor = AnimationRender->GetActor();
	ColActor->Off();
	ColActor->Death();
}