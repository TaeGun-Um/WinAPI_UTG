#include "House.h"

// GE
#include <GameEngineBase/GameEngineRandom.h>
#include <GameEngineBase/GameEngineDirectory.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineCore.h>
#include <GameEngineCore/GameEngineResources.h>
#include <GameEngineCore/GameEngineLevel.h>

// Actor
#include "Player.h"
#include "House_Hut.h"
#include "House_Interior.h"
#include "Shantae_Pajamas.h"

#include "GemWindow.h"
#include "Health.h"
#include "ObjectLoad.h"

House::House() 
{
}

House::~House() 
{
}

void House::Loading()
{
	ColMap = ObjectLoad::GetObjectLoadPtr()->GetColMap("House");

	// Background
	CreateActor<House_Hut>();

	// Map
	CreateActor<House_Interior>();

	// Monster

	// UI
	CreateActor<GemWindow>();
	CreateActor<Health>();

	// Player
	CreateActor<Shantae_Pajamas>();

	Shantae = CreateActor<Player>();
	SHA = dynamic_cast<Player*>(Shantae);

	SHA->SetColMap(ColMap);
	SHA->SetPos({ 1000, 1000 });
	SHA->CameraMoveSwitch();
	SHA->SetAnimationStart(false);
	SHA->SetStartAnimationStart(false);
}

void House::Update(float _DeltaTime)
{
	OverlapTime += _DeltaTime;

	LevelSet();
	Debugging();
	AnimationChange(_DeltaTime);
	SoundCombination(_DeltaTime);
}

void House::LevelChangeStart(GameEngineLevel* _PrevLevel)
{
}

void House::LevelChangeEnd(GameEngineLevel* _NextLevel)
{
	// Player::MainPlayer->IsHouseSet(false);
}

void House::LevelSet()
{
	if (1 == Set)
	{
		Set = 0;

		Player::MainPlayer = SHA;
		Player::MainPlayer->SetPlayerHP(GetPlayLevelHP());
		Player::MainPlayer->SetPlayerMaxHP(GetPlayLevelMaxHP());
		Player::MainPlayer->SetPlayerGem(GetPlayLevelGem());
		Player::MainPlayer->IsHouseSet(true);
	}
}

void House::Debugging()
{
	if (GameEngineInput::IsDown("NextLevel"))
	{
		if (OverlapTime > 0.5f)
		{
			GameEngineCore::GetInst()->ChangeLevel("HouseFront");
			OverlapTime = 0.0f;
		}
	}
	if (GameEngineInput::IsDown("Back"))
	{
		GameEngineCore::GetInst()->ChangeLevel("SelectMeun");
	}
}

void House::AnimationChange(float _DeltaTime)
{
	AnimationTime += _DeltaTime;

	if (GameEngineInput::IsDown("Attack"))
	{
		++Change;
	}

	if (3.0f <= AnimationTime)
	{
		if (true == Shantae_Pajamas::AnimationRender->IsAnimationEnd() && 1 == AnimationChangeCount1)
		{
			AnimationChangeCount1 = 0;
			Shantae_Pajamas::AnimationRender->ChangeAnimation("WakeUp");
		}
		
		if (true == Shantae_Pajamas::AnimationRender->IsAnimationEnd() && 1 == AnimationChangeCount2)
		{
			AnimationChangeCount2 = 0;
			Shantae_Pajamas::AnimationRender->ChangeAnimation("WakeUpMaintain");
		}
	}

	if (7.0f <= AnimationTime)
	{
		if (1 == ExplosionCount)
		{
			ExplosionCount = 0;
			BGMPlayer = GameEngineResources::GetInst().SoundPlayToControl("House_explosion.mp3");
			BGMPlayer.Volume(0.5f);
			BGMPlayer.LoopCount(1);

			Player::MainPlayer->SetCameraShaking(1.5f, 3);
		}

		if (true == Shantae_Pajamas::AnimationRender->IsAnimationEnd() && 1 == AnimationChangeCount3)
		{
			AnimationChangeCount3 = 0;
			Shantae_Pajamas::AnimationRender->ChangeAnimation("Surprise");
		}
		
		if (true == Shantae_Pajamas::AnimationRender->IsAnimationEnd() && 1 == AnimationChangeCount4)
		{
			AnimationChangeCount4 = 0;
			Shantae_Pajamas::AnimationRender->ChangeAnimation("SurpriseMaintain");
		}

	}

	if (11.0f <= AnimationTime)
	{
		GameEngineCore::GetInst()->ChangeLevel("HouseFront");
		Change = 0;
		AnimationTime = 0.0f;
	}
}

void House::SoundCombination(float _DeltaTime)
{
	SeagullTime += _DeltaTime;
	WaveTime += _DeltaTime;
	BellTime += _DeltaTime;

	// Seagull
	if (0.8f <= SeagullTime && 0 == SeagullCount)
	{
		SeagullCount = 1;
		SeagullTime = 0.0f;
	}
	if (1 == SeagullCount)
	{
		SeagullCount = 0;

		int RandC = GameEngineRandom::MainRandom.RandomInt(1, 7);

		if (1 == RandC)
		{
			BGMPlayer = GameEngineResources::GetInst().SoundPlayToControl("Housefront_seagull1.wav");
			BGMPlayer.Volume(0.075f);
			BGMPlayer.LoopCount(1);
		}
		else if (2 == RandC)
		{
			BGMPlayer = GameEngineResources::GetInst().SoundPlayToControl("Housefront_seagull2.wav");
			BGMPlayer.Volume(0.075f);
			BGMPlayer.LoopCount(1);
		}

	}

	// Bell
	if (0.8f <= BellTime && 0 == BellCount)
	{
		BellCount = 1;
		BellTime = 0.0f;
	}
	if (1 == BellCount)
	{
		BellCount = 0;
		
		int RandC = GameEngineRandom::MainRandom.RandomInt(1, 5);

		if (1 == RandC)
		{
			BGMPlayer = GameEngineResources::GetInst().SoundPlayToControl("Housefront_bell.wav");
			BGMPlayer.Volume(0.075f);
			BGMPlayer.LoopCount(1);
		}
	}

	if (1.2f <= WaveTime && 0 == WaveCount)
	{
		WaveCount = 1;
		WaveTime = 0.0f;
	}
	if (1 == WaveCount)
	{
		WaveCount = 0;

		int RandC = GameEngineRandom::MainRandom.RandomInt(1, 2);

		if (1 == RandC)
		{
			BGMPlayer = GameEngineResources::GetInst().SoundPlayToControl("Housefront_wave.wav");
			BGMPlayer.Volume(0.075f);
			BGMPlayer.LoopCount(1);
		}
	}
}