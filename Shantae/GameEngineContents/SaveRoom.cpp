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
#include "Player.h"
#include "Sky.h"
#include "Sea.h"

#include "ItemBox.h"

#include "GemWindow.h"
#include "Health.h"
#include "Inventory.h"
#include "BlueTextBox.h"

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
	{
		Sky* Sk = CreateActor<Sky>();
		Sk->SetSkyYPos(250);
		Sk->SetSkySpeed(25.0f);
	}

	CreateActor<SaveRoom_Background>();

	// Map		
	CreateActor<SaveRoom_Map>();
	CreateActor<SaveRoom_Front>();
	CreateActor<SaveRoom_ColMap>();

	// Item
	{
		ItemBox* Box = CreateActor<ItemBox>();
		Box->SetPos({ 790, 789 });
		Box->SetColMap(ColMap);
		Box->SetItemValue(OCT);
	}

	// Player
	{
		Shantae = CreateActor<Player>();
		SHA = dynamic_cast<Player*>(Shantae);

		SHA->SetColMap(ColMap);
		SHA->SetPos({ 170, 789 });
		Shantae->GetLevel()->SetCameraPos({ 150, 150 });
		SHA->CameraMoveSwitch();
		SHA->SetAnimationStart(false);

		// UI
		CreateActor<GemWindow>();
		CreateActor<Health>();
		Inven = CreateActor<Inventory>();
	}
}

void SaveRoom::Update(float _DeltaTime)
{
	OverlapTime += _DeltaTime;

	BlackBoxOutAnimation();
	LevelSet();
	Debugging();

	// 레벨 이동
	if (SHA->GetPos().x <= 155.0f
		&& PlayerState::MOVE == SHA->GetShantaeState())
	{
		BlackBoxInAnimation();
		SHA->SetRoomAnimationStart(true);
		SHA->SetMoveSpeed(100.0f);
		if (true == SHA->RoomChangeAnimation(_DeltaTime))
		{
			GameEngineCore::GetInst()->ChangeLevel("Scuttle");
		}
	}
}

void SaveRoom::LevelChangeStart(GameEngineLevel* _PrevLevel)
{
	if (1 == StartCount)
	{
		Inven->Elimination();
	}

	if (true == IsStart)
	{
		IsStart = false;
		StartCount = 1;
	}
	Inventory::PlayerInven = Inven;
	BlueTextBox::DialogTextBox = BTB;

	Set = 1;

	SetPlayLevelHP(Player::MainPlayer->GetPlayerHP());
	SetPlayLevelMaxHP(Player::MainPlayer->GetPlayerMaxHP());
	SetPlayLevelGem(Player::MainPlayer->GetPlayerGem());
	SetPlayLevelMonsterMilk(Player::MainPlayer->GetPlayerMonsterMilk());
	SetPlayLevelPikeBall(Player::MainPlayer->GetPlayerPikeBall());
	SetPlayLevelBubble(Player::MainPlayer->GetPlayerBubble());
	SetPlayLevelOctopus(Player::MainPlayer->GetPlayerOctopus());
	SetPlayLevelMeat(Player::MainPlayer->GetPlayerMeat());
	SetPlayLevelIDCard(Player::MainPlayer->GetPlayerIDCard());
}

void SaveRoom::LevelChangeEnd(GameEngineLevel* _NextLevel)
{
	InBoxKill();
	AnimationSet = 1;
	BBoxOutCount = 1;
	SHA->SetPos({ 170, 789 });
	SHA->SetRoomAnimationStart(false);
}

void SaveRoom::BlackBoxOutAnimation()
{
	if (1 == BBoxOutCount)
	{
		BBoxOutCount = 0;
		BBoxOut = CreateActor<BlackBox>();
		BBoxOut->FadeOutStart(2, 0.05f);
	}
}

void SaveRoom::BlackBoxInAnimation()
{
	if (1 == BBoxInCount)
	{
		BBoxInCount = 0;
		BBoxIn = CreateActor<BlackBox>();
		BBoxIn->FadeInStart(2, 0);
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
		Player::MainPlayer->SetPlayerMonsterMilk(GetPlayLevelMonsterMilk());
		Player::MainPlayer->SetPlayerPikeBall(GetPlayLevelPikeBall());
		Player::MainPlayer->SetPlayerBubble(GetPlayLevelBubble());
		Player::MainPlayer->SetPlayerOctopus(GetPlayLevelOctopus());
		Player::MainPlayer->SetPlayerMeat(GetPlayLevelMeat());
		Player::MainPlayer->SetPlayerIDCard(GetPlayLevelIDCard());
	}
	if (1 == AnimationSet)
	{
		SHA->SetStartAnimationStart(true);
		SHA->SetMoveSpeed(600.0f);
		SHA->SetDir("_R");
		if (300 <= SHA->GetPos().x)
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