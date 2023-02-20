#include "SkyRoom.h"

#include <GameEngineBase/GameEngineDirectory.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineResources.h>
#include <GameEngineCore/GameEngineRender.h>
#include <GameEngineCore/GameEngineCore.h>

#include "SkyRoom_Background.h"
#include "SkyRoom_ColMap.h"
#include "SkyRoom_Map.h"
#include "SkyRoom_Sky.h"
#include "Player.h"

#include "GemWindow.h"
#include "Health.h"
#include "ObjectLoad.h"

SkyRoom::SkyRoom() 
{
}

SkyRoom::~SkyRoom() 
{
}

void SkyRoom::Loading()
{
	ColMap = ObjectLoad::GetObjectLoadPtr()->GetColMap("SkyRoom");

	// Background(¼ø¼­)
	CreateActor<SkyRoom_Sky>();
	CreateActor<SkyRoom_Background>();

	// Map		
	CreateActor<SkyRoom_Map>();
	CreateActor<SkyRoom_ColMap>();

	// Monster

	// UI
	CreateActor<GemWindow>();
	CreateActor<Health>();

	// Player
	Shantae = CreateActor<Player>();
	SHA = dynamic_cast<Player*>(Shantae);

	SHA->SetColMap(ColMap);
	SHA->SetPos({ 192, 829 });
	Shantae->GetLevel()->SetCameraPos({ 200, 150 });
	SHA->CameraMoveSwitch();
	SHA->SetAnimationStart(false);
}

void SkyRoom::Update(float _DeltaTime)
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
		if (360 <= SHA->GetPos().x)
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
			SkyRoom_ColMap::ColMap->OnOffSwtich();
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
			GameEngineCore::GetInst()->ChangeLevel("SaveRoom");
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

void SkyRoom::LevelChangeStart(GameEngineLevel* _PrevLevel)
{
	BGMPlayer = GameEngineResources::GetInst().SoundPlayToControl("Sky.mp3");
	BGMPlayer.Volume(0.1f);
	BGMPlayer.LoopCount(100);

	SetPlayLevelHP(Player::MainPlayer->GetPlayerHP());
	SetPlayLevelMaxHP(Player::MainPlayer->GetPlayerMaxHP());
	SetPlayLevelGem(Player::MainPlayer->GetPlayerGem());
}

void SkyRoom::LevelChangeEnd(GameEngineLevel* _NextLevel)
{
	BGMPlayer.Stop();
}