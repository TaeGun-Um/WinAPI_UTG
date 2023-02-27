#include "SkyRoom.h"

#include <GameEngineBase/GameEngineDirectory.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineResources.h>
#include <GameEngineCore/GameEngineRender.h>
#include <GameEngineCore/GameEngineCore.h>

#include "SkyRoom_Background.h"
#include "SkyRoom_ColMap.h"
#include "SkyRoom_Map.h"
#include "Sky.h"
#include "Player.h"
#include "SkyNPC.h"
#include "Wrench.h"

#include "GemWindow.h"
#include "Health.h"
#include "ObjectLoad.h"
#include "BlackBox.h"

SkyRoom::SkyRoom() 
{
}

SkyRoom::~SkyRoom() 
{
}

void SkyRoom::Loading()
{
	ColMap = ObjectLoad::GetObjectLoadPtr()->GetColMap("SkyRoom");

	// Background(순서)
	{
		Sky* Sk = CreateActor<Sky>();
		Sk->SetSkyYPos(300);
		Sk->SetSkySpeed(25.0f);
	}
	
	CreateActor<SkyRoom_Background>();

	// Map		
	CreateActor<SkyRoom_Map>();
	CreateActor<SkyRoom_ColMap>();

	// NPC
	{
		SkyNPC* M = CreateActor<SkyNPC>();
		M->SetPos({ 1130, 837 });

		Wrench* M1 = CreateActor<Wrench>();
		M1->SetPos({ 1330, 498 });
	}

	// Player
	{
		Shantae = CreateActor<Player>();
		SHA = dynamic_cast<Player*>(Shantae);

		SHA->SetColMap(ColMap);
		SHA->SetPos({ 210, 829 });
		Shantae->GetLevel()->SetCameraPos({ 200, 150 });
		SHA->CameraMoveSwitch();
		SHA->SetAnimationStart(false);

		// UI
		CreateActor<GemWindow>();
		CreateActor<Health>();
	}
}

void SkyRoom::Update(float _DeltaTime)
{
	OverlapTime += _DeltaTime;

	BlackBoxOutAnimation();
	LevelSet();
	Debugging();

	// 레벨 이동
	if (SHA->GetPos().x <= 190.0f
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

void SkyRoom::LevelChangeStart(GameEngineLevel* _PrevLevel)
{
	Set = 1;

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
	InBoxKill();
	AnimationSet = 1;
	BBoxOutCount = 1;
	SHA->SetPos({ 210, 829 });
	SHA->SetRoomAnimationStart(false);
}

void SkyRoom::BlackBoxOutAnimation()
{
	if (1 == BBoxOutCount)
	{
		BBoxOutCount = 0;
		BBoxOut = CreateActor<BlackBox>();
		BBoxOut->FadeOutStart(2, 0.05f);
	}
}

void SkyRoom::BlackBoxInAnimation()
{
	if (1 == BBoxInCount)
	{
		BBoxInCount = 0;
		BBoxIn = CreateActor<BlackBox>();
		BBoxIn->FadeInStart(2, 0);
	}
}

void SkyRoom::InBoxKill()
{
	if (nullptr != BBoxIn)
	{
		BBoxIn->Death();
		BBoxIn = nullptr;
		BBoxInCount = 1;
		BBoxOutCount = 1;
	}
}

void SkyRoom::LevelSet()
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
		SHA->SetMoveSpeed(600.0f);
		SHA->SetDir("_R");
		if (390 <= SHA->GetPos().x)
		{
			SHA->SetStartAnimationStart(false);
			SHA->ChangeState(PlayerState::IDLE);
			AnimationSet = 0;
		}
	}
}

void SkyRoom::Debugging()
{
	if (GameEngineInput::IsDown("ColMapSwitch"))
	{
		if (OverlapTime > 0.5f)
		{
			SkyRoom_ColMap::ColMap->OnOffSwtich();
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
			GameEngineCore::GetInst()->ChangeLevel("SaveRoom");
			OverlapTime = 0.0f;
		}
	}
	if (GameEngineInput::IsDown("Back"))
	{
		GameEngineCore::GetInst()->ChangeLevel("SelectMeun");
	}
}