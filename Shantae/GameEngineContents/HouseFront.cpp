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
#include "HouseFront_WindVane.h"
#include "Building0.h"
#include "Wave.h"
#include "Sea.h"
#include "Sky.h"

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

	// Background(순서)
	{
		Sky* Sk = CreateActor<Sky>();
		Sk->SetSkyYPos(0);
		Sk->SetSkySpeed(25.0f);
		Sea* Se = CreateActor<Sea>();
		Se->SetPos({500, 600});
		Se->SetCount();
	}

	CreateActor<HouseFront_Building>();
	CreateActor<Building0>();
	CreateActor<HouseFront_Island>();
	CreateActor<HouseFront_PalmTree>();
	CreateActor<HouseFront_Bush>();
	CreateActor<HouseFront_LightHouse>();
	CreateActor<HouseFront_WindVane>();
	
	// wave
	{
		GameEngineActor* W1 = CreateActor<Wave>();
		W1->SetPos({ 150, 725 });
		GameEngineActor* W2 = CreateActor<Wave>();
		W2->SetPos({ 600, 725 });
		GameEngineActor* W3 = CreateActor<Wave>();
		W3->SetPos({ 991, 725 });
	}

	// Map
	CreateActor<HouseFront_Map>();
	CreateActor<HouseFront_ColMap>();

	// Player
	{
		Shantae = CreateActor<Player>();
		SHA = dynamic_cast<Player*>(Shantae);

		SHA->SetColMap(ColMap);
		SHA->SetPos({ 5, 590 });
		SHA->CameraMoveSwitch();
		SHA->SetAnimationStart(false);
		SHA->SetStartAnimationStart(false);

		// UI
		CreateActor<GemWindow>();
		CreateActor<Health>();
	}
}

void HouseFront::Update(float _DeltaTime)
{
	OverlapTime += _DeltaTime;

	BlackBoxOutAnimation();
	LevelSet();
	Debugging();
	SoundCombination(_DeltaTime);

	// 레벨 이동
	if (SHA->GetPos().x >= 1250.0f
		&& PlayerState::MOVE == SHA->GetShantaeState())
	{
		BlackBoxInAnimation();
		SHA->SetAnimationStart(true);
		SHA->SetMoveSpeed(100.0f);
		if (true == SHA->LevelChangeAnimation(_DeltaTime))
		{
			GameEngineCore::GetInst()->ChangeLevel("Move0");
		}
	}

	RandExplosion(_DeltaTime);
}

void HouseFront::LevelChangeStart(GameEngineLevel* _PrevLevel)
{
	SetPlayLevelHP(Player::MainPlayer->GetPlayerHP());
	SetPlayLevelMaxHP(Player::MainPlayer->GetPlayerMaxHP());
	SetPlayLevelGem(Player::MainPlayer->GetPlayerGem());
}

void HouseFront::LevelChangeEnd(GameEngineLevel* _NextLevel)
{
	InBoxKill();
}

void HouseFront::RandExplosion(float _DeltaTime)
{
	RandTime += _DeltaTime;

	int RandC = GameEngineRandom::MainRandom.RandomInt(1, 500);

	if (1 == RandC && 0.2f <= RandTime)
	{
		RandTime = 0.0f;
		Player::MainPlayer->SetCameraShakinghard(0.25f, 3.0f);
		BGMPlayer = GameEngineResources::GetInst().SoundPlayToControl("Explosion1.mp3");
		BGMPlayer.Volume(0.25f);
		BGMPlayer.LoopCount(1);
	}
	else if (250 == RandC && 0.2f <= RandTime)
	{
		RandTime = 0.0f;
		Player::MainPlayer->SetCameraShakinghard(0.25f, 3.0f);
		BGMPlayer = GameEngineResources::GetInst().SoundPlayToControl("Explosion2.mp3");
		BGMPlayer.Volume(0.25f);
		BGMPlayer.LoopCount(1);
	}
}

void HouseFront::BlackBoxOutAnimation()
{
	if (1 == BBoxOutCount)
	{
		BBoxOutCount = 0;
		BBoxOut = CreateActor<BlackBox>();
		BBoxOut->FadeOutStart(1, 0.25f);
	}
}

void HouseFront::BlackBoxInAnimation()
{
	if (1 == BBoxInCount)
	{
		BBoxInCount = 0;
		BBoxIn = CreateActor<BlackBox>();
		BBoxIn->FadeInStart(2, 0.25f);
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