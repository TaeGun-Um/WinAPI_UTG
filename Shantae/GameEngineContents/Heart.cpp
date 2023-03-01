#include "Heart.h"

#include <GameEngineBase/GameEngineString.h>
#include <GameEngineBase/GameEngineRandom.h>
#include <GameEngineCore/GameEngineRender.h>
#include <GameEngineCore/GameEngineCollision.h>

#include "ContentsEnum.h"
#include "Player.h"

Heart::Heart() 
{
}

Heart::~Heart() 
{
}

void Heart::Start()
{
	AnimationRender = CreateRender(RenderOrder::Object);
	AnimationRender->SetScale({ 400, 400 });

	AnimationRender->CreateAnimation({ .AnimationName = "Heart",  .ImageName = "Heart1.bmp", .Start = 0, .End = 3, .InterTime = 0.1f });
	AnimationRender->CreateAnimation({ .AnimationName = "Heart_Large",  .ImageName = "Heart2.bmp", .Start = 0, .End = 7, .InterTime = 0.1f });

	BodyCollision = CreateCollision(CollisionOrder::Equip);
	BodyCollision->SetDebugRenderType(CT_Rect);
	BodyCollision->SetScale({ 25, 25 });
	BodyCollision->SetPosition({ 0, -12.5f });

	AnimationRender->ChangeAnimation("Heart");
}

void Heart::Update(float _DeltaTime)
{
	if (1 == CreateSet)
	{
		CreateSet = 0;
		GemSetting();
	}

	MoveCalculation(_DeltaTime);

	CollisionCheck(_DeltaTime);
}

void Heart::Render(float _DeltaTime)
{

}

void Heart::MoveCalculation(float _DeltaTime)
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

void Heart::CollisionCheck(float _DeltaTime)
{
	if (nullptr != BodyCollision)
	{
		if (true == BodyCollision->Collision({ .TargetGroup = static_cast<int>(CollisionOrder::PlayerEffect), .TargetColType = CT_Rect, .ThisColType = CT_Rect }))
		{
			BodyCollision->Off();

			if (1 == SoundCount && HeartState::Small == CreateHeart)
			{
				SoundCount = 0;
				BGMPlayer = GameEngineResources::GetInst().SoundPlayToControl("Player_hp_small.mp3");
				BGMPlayer.Volume(0.1f);
				BGMPlayer.LoopCount(1);
			}
			else if (1 == SoundCount && HeartState::Large == CreateHeart)
			{
				SoundCount = 0;
				BGMPlayer = GameEngineResources::GetInst().SoundPlayToControl("Player_hp_large.wav");
				BGMPlayer.Volume(0.15f);
				BGMPlayer.LoopCount(1);
			}

			ApplyScore();
		}
	}
}

void Heart::GemSetting()
{
	std::string UpperName = GameEngineString::ToUpper(JarSize);
	std::string UpperName_comparison1 = GameEngineString::ToUpper("Small");
	std::string UpperName_comparison2 = GameEngineString::ToUpper("Large");

	if (UpperName_comparison1 == UpperName)
	{
		CreateHeart = HeartState::Small;
	}
	else if (UpperName_comparison2 == UpperName)
	{
		CreateHeart = HeartState::Large;
	}

	switch (CreateHeart)
	{
	case HeartState::Small:
		AnimationRender->ChangeAnimation("Heart");
		Score = 1;
		break;
	case HeartState::Large:
		AnimationRender->ChangeAnimation("Heart_Large");
		Score = 4;
		BodyCollision->SetScale({ 40, 40 });
		BodyCollision->SetPosition({ 0, -20 });
		break;
	default:
		break;
	}
}

void Heart::ApplyScore()
{
	int CurrentHp = Player::MainPlayer->GetPlayerHP();
	int CurrentMaxHp = Player::MainPlayer->GetPlayerMaxHP();
	int EquipHp = CurrentHp + Score;

	if (EquipHp >= CurrentMaxHp)
	{
		Score = CurrentMaxHp;
		Player::MainPlayer->SetPlayerHP(Score);
	}
	else
	{
		Player::MainPlayer->PlusPlayerHP(Score);
	}

	Kill();
}

void Heart::Kill()
{
	GameEngineActor* ColActor = AnimationRender->GetActor();
	ColActor->Off();
	ColActor->Death();
}