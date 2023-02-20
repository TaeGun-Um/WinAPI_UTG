#include "UncleRoom.h"

#include <GameEngineBase/GameEngineDirectory.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineResources.h>
#include <GameEngineCore/GameEngineRender.h>
#include <GameEngineCore/GameEngineCore.h>

#include "UncleRoom_Background.h"
#include "UncleRoom_ColMap.h"
#include "UncleRoom_Front.h"
#include "UncleRoom_Map.h"
#include "UncleRoom_Sea.h"
#include "UncleRoom_Sky.h"
#include "Player.h"

#include "GemWindow.h"
#include "Health.h"
#include "ObjectLoad.h"

UncleRoom::UncleRoom() 
{
}

UncleRoom::~UncleRoom() 
{
}

void UncleRoom::Loading()
{
	ColMap = ObjectLoad::GetObjectLoadPtr()->GetColMap("UncleRoom");

	// Background(¼ø¼­)
	CreateActor<UncleRoom_Sky>();
	CreateActor<UncleRoom_Sea>();
	CreateActor<UncleRoom_Background>();
				
	// Map		
	CreateActor<UncleRoom_Map>();
	CreateActor<UncleRoom_Front>();
	CreateActor<UncleRoom_ColMap>();

	// Monster

	// UI
	CreateActor<GemWindow>();
	CreateActor<Health>();

	// Player
	Shantae = CreateActor<Player>();
	SHA = dynamic_cast<Player*>(Shantae);

	SHA->SetColMap(ColMap);
	SHA->SetPos({ 90, 781 });
	Shantae->GetLevel()->SetCameraPos({ 50, 100 });
	SHA->CameraMoveSwitch();
	SHA->SetAnimationStart(false);
}

void UncleRoom::Update(float _DeltaTime)
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
		if (200 <= SHA->GetPos().x)
		{
			SHA->SetStartAnimationStart(false);
			SHA->ChangeState(PlayerState::IDLE);
			AnimationSet = 0;
		}
	}

	OverlapTime += _DeltaTime;

	if (GameEngineInput::IsDown("ColMapSwitch"))
	{
		if (OverlapTime > 0.5f)
		{
			UncleRoom_ColMap::ColMap->OnOffSwtich();
			OverlapTime = 0.0f;
		}
	}
	if (GameEngineInput::IsPress("BeforeLevel"))
	{
		if (OverlapTime > 0.5f)
		{
			GameEngineCore::GetInst()->ChangeLevel("Scuttle");
			OverlapTime = 0.0f;
		}
	}
	if (GameEngineInput::IsPress("NextLevel"))
	{
		if (OverlapTime > 0.5f)
		{
			GameEngineCore::GetInst()->ChangeLevel("Shop");
			OverlapTime = 0.0f;
		}
	}
	if (GameEngineInput::IsDown("Back"))
	{
		GameEngineCore::GetInst()->ChangeLevel("SelectMeun");
	}

	if (SHA->GetPos().x <= 50.0f)
	{
		GameEngineCore::GetInst()->ChangeLevel("Scuttle");
	}
}

void UncleRoom::LevelChangeStart(GameEngineLevel* _PrevLevel)
{
	SetPlayLevelHP(Player::MainPlayer->GetPlayerHP());
	SetPlayLevelMaxHP(Player::MainPlayer->GetPlayerMaxHP());
	SetPlayLevelGem(Player::MainPlayer->GetPlayerGem());
}

void UncleRoom::LevelChangeEnd(GameEngineLevel* _NextLevel)
{
}