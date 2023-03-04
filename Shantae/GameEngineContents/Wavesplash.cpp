#include "Wavesplash.h"

#include <GameEngineCore/GameEngineRender.h>
#include <GameEngineCore/GameEngineCollision.h>
#include <GameEngineCore/GameEngineLevel.h>

#include "ContentsEnum.h"
#include "Splash.h"
#include "Player.h"

Wavesplash::Wavesplash() 
{
}

Wavesplash::~Wavesplash() 
{
}

void Wavesplash::Start()
{
	BodyCollision = CreateCollision(CollisionOrder::Trigger);
	BodyCollision->SetDebugRenderType(CT_Rect);
	BodyCollision->SetScale({ 200, 10 });
	BodyCollision->SetPosition({ 75, 112.5f });
}

void Wavesplash::Update(float _DeltaTime)
{
	if (true == IsIn && 1 == CreateSpl)
	{
		CreateSpl = 0;
		CreateSplash();
	}

	CollisionCheck();

	if (true == IsHelthWater && true == IsIn)
	{
		HealthWater(_DeltaTime);
	}
}

void Wavesplash::CollisionCheck()
{
	if (nullptr != BodyCollision)
	{
		if (true == BodyCollision->Collision({ .TargetGroup = static_cast<int>(CollisionOrder::Player), .TargetColType = CT_Rect, .ThisColType = CT_Rect }))
		{
			IsIn = true;
		}
		else
		{
			IsIn = false;
			CreateSpl = 1;
		}
	}
}

void Wavesplash::CreateSplash()
{
	Splash* Ex = nullptr;

	Ex = GetLevel()->CreateActor<Splash>();
	Ex->SetPos(GetPos());

	BGMPlayer = GameEngineResources::GetInst().SoundPlayToControl("Splash_water.wav");
	BGMPlayer.Volume(0.1f);
	BGMPlayer.LoopCount(1);
}

void Wavesplash::HealthWater(float _DeltaTime)
{
	if (false == IsIn)
	{
		HealTiem = 0.0f;
	}

	HealTiem += _DeltaTime;

	if (1.0f <= HealTiem)
	{
		HealTiem = 0.0f;

		if (8 > Player::MainPlayer->GetPlayerHP())
		{
			BGMPlayer = GameEngineResources::GetInst().SoundPlayToControl("Player_hp_small.mp3");
			BGMPlayer.Volume(0.1f);
			BGMPlayer.LoopCount(1);

			Player::MainPlayer->PlusPlayerHP(1);
		}
	}

}