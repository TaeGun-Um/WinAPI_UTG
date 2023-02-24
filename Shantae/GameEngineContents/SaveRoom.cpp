#include "SaveRoom.h"

#include <GameEngineBase/GameEngineDirectory.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineResources.h>
#include <GameEngineCore/GameEngineRender.h>
#include <GameEngineCore/GameEngineCore.h>

#include "SaveRoom_Background.h"
#include "SaveRoom_ColMap.h"
#include "SaveRoom_Front.h"
#include "SaveRoom_Map.h"
#include "SaveRoom_Sea.h"
#include "SaveRoom_Sky.h"
#include "Player.h"

#include "GemWindow.h"
#include "Health.h"
#include "ObjectLoad.h"
#include "BlackBox.h"

SaveRoom::SaveRoom() 
{
}

SaveRoom::~SaveRoom() 
{
}

void SaveRoom::Loading()
{
	ColMap = ObjectLoad::GetObjectLoadPtr()->GetColMap("SaveRoom");

	// Background(순서)
	CreateActor<SaveRoom_Sky>();
	CreateActor<SaveRoom_Sea>();
	CreateActor<SaveRoom_Background>();

	// Map		
	CreateActor<SaveRoom_Map>();
	CreateActor<SaveRoom_Front>();
	CreateActor<SaveRoom_ColMap>();

	// Monster

	// UI
	CreateActor<GemWindow>();
	CreateActor<Health>();

	// Player
	Shantae = CreateActor<Player>();
	SHA = dynamic_cast<Player*>(Shantae);

	SHA->SetColMap(ColMap);
	SHA->SetPos({ 157, 789 });
	Shantae->GetLevel()->SetCameraPos({ 150, 150 });
	SHA->CameraMoveSwitch();
	SHA->SetAnimationStart(false);
}

void SaveRoom::Update(float _DeltaTime)
{
	OverlapTime += _DeltaTime;

	LevelSet();
	Debugging();

	// 레벨 이동
	if (SHA->GetPos().x <= 50.0f)
	{
		GameEngineCore::GetInst()->ChangeLevel("Scuttle");
	}
}

void SaveRoom::LevelChangeStart(GameEngineLevel* _PrevLevel)
{
	SetPlayLevelHP(Player::MainPlayer->GetPlayerHP());
	SetPlayLevelMaxHP(Player::MainPlayer->GetPlayerMaxHP());
	SetPlayLevelGem(Player::MainPlayer->GetPlayerGem());
}

void SaveRoom::LevelChangeEnd(GameEngineLevel* _NextLevel)
{
}

void SaveRoom::BlackBoxOutAnimation()
{
	if (1 == BBoxOutCount)
	{
		BBoxOutCount = 0;
		BBoxOut = CreateActor<BlackBox>();
		BBoxOut->FadeOutStart(0, 0.5f);
	}
}

void SaveRoom::BlackBoxInAnimation()
{
	if (1 == BBoxInCount)
	{
		BBoxInCount = 0;
		BBoxIn = CreateActor<BlackBox>();
		BBoxIn->FadeInStart(0, 0.5f);
	}
}

void SaveRoom::InBoxKill()
{
	if (nullptr != BBoxIn)
	{
		BBoxIn->Death();
		BBoxIn = nullptr;
		BBoxInCount = 1;
		BBoxOutCount = 1;
	}
}

void SaveRoom::LevelSet()
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
		if (290 <= SHA->GetPos().x)
		{
			SHA->SetStartAnimationStart(false);
			SHA->ChangeState(PlayerState::IDLE);
			AnimationSet = 0;
		}
	}
}

void SaveRoom::Debugging()
{
	if (GameEngineInput::IsDown("ColMapSwitch"))
	{
		if (OverlapTime > 0.5f)
		{
			SaveRoom_ColMap::ColMap->OnOffSwtich();
			OverlapTime = 0.0f;
		}
	}
	if (GameEngineInput::IsDown("BeforeLevel"))
	{
		if (OverlapTime > 0.5f)
		{
			GameEngineCore::GetInst()->ChangeLevel("Scuttle");
			OverlapTime = 0.0f;
		}
	}
	if (GameEngineInput::IsDown("NextLevel"))
	{
		if (OverlapTime > 0.5f)
		{
			GameEngineCore::GetInst()->ChangeLevel("Opening");
			OverlapTime = 0.0f;
		}
	}
	if (GameEngineInput::IsDown("Back"))
	{
		GameEngineCore::GetInst()->ChangeLevel("SelectMeun");
	}
}