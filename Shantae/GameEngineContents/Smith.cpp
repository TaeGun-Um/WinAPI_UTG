#include "Smith.h"

#include <GameEngineBase/GameEngineDirectory.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineResources.h>
#include <GameEngineCore/GameEngineRender.h>
#include <GameEngineCore/GameEngineCore.h>

#include "Smith_Background.h"
#include "Smith_ColMap.h"
#include "Smith_Map.h"
#include "Sky.h"
#include "Sea.h"
#include "Player.h"
#include "Squidsmith.h"

#include "Heart_Octopus.h"

#include "GemWindow.h"
#include "Health.h"
#include "ObjectLoad.h"
#include "BlackBox.h"

Smith::Smith() 
{
}

Smith::~Smith() 
{
}

void Smith::Loading()
{
	ColMap = ObjectLoad::GetObjectLoadPtr()->GetColMap("Smith");

	// Background(순서)
	{
		Sky* Sk = CreateActor<Sky>();
		Sk->SetSkyYPos(200);
		Sk->SetSkySpeed(25.0f);
		Sea* Se = CreateActor<Sea>();
		Se->SetPos({ 600, 700 });
	}

	CreateActor<Smith_Background>();

	// Map		
	CreateActor<Smith_Map>();
	CreateActor<Smith_ColMap>();

	// NPC
	{
		Squidsmith* M = CreateActor<Squidsmith>();
		M->SetPos({ 880, 637 });
	}

	// Item
	{
		Heart_Octopus* Oct = CreateActor<Heart_Octopus>();
		Oct->SetPos({ 1334, 840 });
		Oct->SetColMap(ColMap);
		Oct->SetJumpZero();
	}

	// Player
	{
		Shantae = CreateActor<Player>();
		SHA = dynamic_cast<Player*>(Shantae);

		SHA->SetColMap(ColMap);
		SHA->SetPos({ 155, 841 });
		Shantae->GetLevel()->SetCameraPos({ 150, 150 });
		SHA->CameraMoveSwitch();
		SHA->SetAnimationStart(false);

		// UI
		CreateActor<GemWindow>();
		CreateActor<Health>();
	}
}

void Smith::Update(float _DeltaTime)
{
	OverlapTime += _DeltaTime;

	BlackBoxOutAnimation();
	LevelSet();
	Debugging();

	// 레벨 이동
	if (SHA->GetPos().x <= 140.0f
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

void Smith::LevelChangeStart(GameEngineLevel* _PrevLevel)
{
	Set = 1;

	BGMPlayer = GameEngineResources::GetInst().SoundPlayToControl("Customer.mp3");
	BGMPlayer.Volume(0.1f);
	BGMPlayer.LoopCount(100);

	SetPlayLevelHP(Player::MainPlayer->GetPlayerHP());
	SetPlayLevelMaxHP(Player::MainPlayer->GetPlayerMaxHP());
	SetPlayLevelGem(Player::MainPlayer->GetPlayerGem());
}

void Smith::LevelChangeEnd(GameEngineLevel* _NextLevel)
{
	BGMPlayer.Stop();
	InBoxKill();
	AnimationSet = 1;
	BBoxOutCount = 1;
	SHA->SetPos({ 155, 841 });
	SHA->SetRoomAnimationStart(false);
}

void Smith::BlackBoxOutAnimation()
{
	if (1 == BBoxOutCount)
	{
		BBoxOutCount = 0;
		BBoxOut = CreateActor<BlackBox>();
		BBoxOut->FadeOutStart(2, 0.05f);
	}
}

void Smith::BlackBoxInAnimation()
{
	if (1 == BBoxInCount)
	{
		BBoxInCount = 0;
		BBoxIn = CreateActor<BlackBox>();
		BBoxIn->FadeInStart(2, 0);
	}
}

void Smith::InBoxKill()
{
	if (nullptr != BBoxIn)
	{
		BBoxIn->Death();
		BBoxIn = nullptr;
		BBoxInCount = 1;
		BBoxOutCount = 1;
	}
}

void Smith::LevelSet()
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
		if (300 <= SHA->GetPos().x)
		{
			SHA->SetStartAnimationStart(false);
			SHA->ChangeState(PlayerState::IDLE);
			AnimationSet = 0;
		}
	}
}

void Smith::Debugging()
{
	if (GameEngineInput::IsDown("ColMapSwitch"))
	{
		if (OverlapTime > 0.5f)
		{
			Smith_ColMap::ColMap->OnOffSwtich();
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
			GameEngineCore::GetInst()->ChangeLevel("SkyRoom");
			OverlapTime = 0.0f;
		}
	}
	if (GameEngineInput::IsDown("Back"))
	{
		GameEngineCore::GetInst()->ChangeLevel("SelectMeun");
	}
}