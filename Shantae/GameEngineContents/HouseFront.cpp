#include "HouseFront.h"

// GE
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

HouseFront::HouseFront() 
{
}

HouseFront::~HouseFront() 
{
}

void HouseFront::Loading()
{
	ColMap = ObjectLoad::GetObjectLoadPtr()->GetColMap("HouseFront");

	// Background(¼ø¼­)
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
	LevelSet();
	Debugging();

	OverlapTime += _DeltaTime;

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