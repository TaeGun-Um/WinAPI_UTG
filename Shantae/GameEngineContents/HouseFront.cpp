#include "HouseFront.h"

// GE
#include <GameEngineBase/GameEngineRandom.h>
#include <GameEngineBase/GameEngineDirectory.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineResources.h>
#include <GameEngineCore/GameEngineRender.h>
#include <GameEngineCore/GameEngineCore.h>

// Actor
#include "HouseFront_Map.h"
#include "HouseFront_Building.h"
#include "HouseFront_Bush.h"
#include "HouseFront_ColMap.h"
#include "HouseFront_Island.h"
#include "HouseFront_LightHouse.h"
#include "HouseFront_PalmTree.h"
#include "HouseFront_Sea.h"
#include "HouseFront_WindVane.h"
#include "Building0.h"

#include "GemWindow.h"
#include "Health.h"

#include "Soldier_Black.h"

#include "Player.h"
#include "ContentsEnum.h"
#include "ObjectLoad.h"
#include "BlackBox.h"

HouseFront::HouseFront() 
{
}

HouseFront::~HouseFront() 
{
}

void HouseFront::Loading()
{
	ColMap = ObjectLoad::GetObjectLoadPtr()->GetColMap("HouseFront");

	// Background(����)
	CreateActor<HouseFront_Sea>();
	CreateActor<HouseFront_Building>();
	CreateActor<Building0>();
	CreateActor<HouseFront_Island>();
	CreateActor<HouseFront_PalmTree>();
	CreateActor<HouseFront_Bush>();
	CreateActor<HouseFront_LightHouse>();

	// Map
	CreateActor<HouseFront_Map>();
	CreateActor<HouseFront_ColMap>();

	// Monster
	CreateActor<HouseFront_WindVane>();

	// UI
	CreateActor<GemWindow>();
	CreateActor<Health>();

	// Player
	Shantae = CreateActor<Player>();
	SHA = dynamic_cast<Player*>(Shantae);

	SHA->SetColMap(ColMap);
	SHA->SetPos({5, 590});
	SHA->CameraMoveSwitch();
	SHA->SetAnimationStart(false);
	SHA->SetStartAnimationStart(false);
}

void HouseFront::Update(float _DeltaTime)
{
	OverlapTime += _DeltaTime;

	LevelSet();
	Debugging();
	SoundCombination(_DeltaTime);

	// ���� �̵�
	if (SHA->GetPos().x >= 1250.0f
		&& PlayerState::MOVE == SHA->GetShantaeState())
	{
		SHA->SetAnimationStart(true);
		SHA->SetMoveSpeed(100.0f);
		if (true == SHA->LevelChangeAnimation(_DeltaTime))
		{
			GameEngineCore::GetInst()->ChangeLevel("Move0");
		}
	}
}

void HouseFront::LevelChangeStart(GameEngineLevel* _PrevLevel)
{
	SetPlayLevelHP(Player::MainPlayer->GetPlayerHP());
	SetPlayLevelMaxHP(Player::MainPlayer->GetPlayerMaxHP());
	SetPlayLevelGem(Player::MainPlayer->GetPlayerGem());
}

void HouseFront::LevelChangeEnd(GameEngineLevel* _NextLevel)
{
	
}

void HouseFront::BlackBoxOutAnimation()
{
	if (1 == BBoxOutCount)
	{
		BBoxOutCount = 0;
		BBoxOut = CreateActor<BlackBox>();
		BBoxOut->FadeOutStart(0, 0.5f);
	}
}

void HouseFront::BlackBoxInAnimation()
{
	if (1 == BBoxInCount)
	{
		BBoxInCount = 0;
		BBoxIn = CreateActor<BlackBox>();
		BBoxIn->FadeInStart(0, 0.5f);
	}
}

void HouseFront::InBoxKill()
{
	if (nullptr != BBoxIn)
	{
		BBoxIn->Death();
		BBoxIn = nullptr;
		BBoxInCount = 1;
		BBoxOutCount = 1;
	}
}

void HouseFront::LevelSet()
{
	if (1 == Set)
	{
		Set = 0;

		Player::MainPlayer = SHA;
		Player::MainPlayer->SetPlayerHP(GetPlayLevelHP());
		Player::MainPlayer->SetPlayerMaxHP(GetPlayLevelMaxHP());
		Player::MainPlayer->SetPlayerGem(GetPlayLevelGem());
	}
	if (1 == AnimationSet)
	{
		SHA->SetStartAnimationStart(true);
		if (640 <= SHA->GetPos().x)
		{
			SHA->SetStartAnimationStart(false);
			SHA->ChangeState(PlayerState::IDLE);
			AnimationSet = 0;
		}
	}
}

void HouseFront::Debugging()
{
	if (GameEngineInput::IsDown("ColMapSwitch"))
	{
		if (OverlapTime > 0.5f)
		{
			HouseFront_ColMap::ColMap->OnOffSwtich();
			OverlapTime = 0.0f;
		}
	}
	if (GameEngineInput::IsDown("BeforeLevel"))
	{
		if (OverlapTime > 0.5f)
		{
			GameEngineCore::GetInst()->ChangeLevel("House");
			OverlapTime = 0.0f;
		}
	}
	if (GameEngineInput::IsDown("NextLevel"))
	{
		if (OverlapTime > 0.5f)
		{
			GameEngineCore::GetInst()->ChangeLevel("Move0");
			OverlapTime = 0.0f;
		}
	}
	if (GameEngineInput::IsDown("Back"))
	{
		GameEngineCore::GetInst()->ChangeLevel("SelectMeun");
	}
}

void HouseFront::SoundCombination(float _DeltaTime)
{
	SeagullTime += _DeltaTime;
	WaveTime += _DeltaTime;
	BellTime += _DeltaTime;

	// Seagull
	if (1.0f <= SeagullTime && 0 == SeagullCount)
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
	if (1.0f <= BellTime && 0 == BellCount)
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