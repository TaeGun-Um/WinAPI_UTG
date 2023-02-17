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
	SHA->SetPos({150, 590});
	SHA->CameraMoveSwitch();
}

void HouseFront::Update(float _DeltaTime)
{
	if (1 == Set)
	{
		Set = 0;

		Player::MainPlayer = SHA;
		Player::MainPlayer->SetPlayerHP(GetPlayLevelHP());
		Player::MainPlayer->SetPlayerMaxHP(GetPlayLevelMaxHP());
		Player::MainPlayer->SetPlayerGem(GetPlayLevelGem());
	}

	OverlapTime += _DeltaTime;

	if (GameEngineInput::IsDown("ColMapSwitch"))
	{
		if (OverlapTime > 0.5f)
		{
			HouseFront_ColMap::ColMap->OnOffSwtich();
			OverlapTime = 0.0f;
		}
	}
	if (GameEngineInput::IsPress("BeforeLevel"))
	{
		if (OverlapTime > 0.5f)
		{
			GameEngineCore::GetInst()->ChangeLevel("House");
			OverlapTime = 0.0f;
		}
	}
	if (GameEngineInput::IsPress("NextLevel"))
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

	if (SHA->GetPos().x >= 1200.0f)
	{
		GameEngineCore::GetInst()->ChangeLevel("Move0");
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