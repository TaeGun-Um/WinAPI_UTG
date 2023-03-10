#include "Spa.h"

#include <GameEngineBase/GameEngineDirectory.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineResources.h>
#include <GameEngineCore/GameEngineRender.h>
#include <GameEngineCore/GameEngineCore.h>

#include "Spa_Background.h"
#include "Spa_ColMap.h"
#include "Spa_Map.h"
#include "Sky.h"
#include "Sea.h"
#include "Player.h"
#include "Bathwoman.h"

#include "GemWindow.h"
#include "Health.h"
#include "Inventory.h"
#include "BlueTextBox.h"

#include "ObjectLoad.h"
#include "BlackBox.h"
#include "Wavesplash.h"

Spa::Spa() 
{
}

Spa::~Spa() 
{
}

void Spa::Loading()
{
	ColMap = ObjectLoad::GetObjectLoadPtr()->GetColMap("Spa");

	// Background(순서)
	{
		Sky* Sk = CreateActor<Sky>();
		Sk->SetSkyYPos(200);
		Sk->SetSkySpeed(25.0f);
		Sea* Se = CreateActor<Sea>();
		Se->SetPos({ 620, 700 });
	}

	CreateActor<Spa_Background>();

	// Map		
	CreateActor<Spa_Map>();
	CreateActor<Spa_ColMap>();

	// Splashcollision
	{
		Wavesplash* S = CreateActor<Wavesplash>();
		S->SetPos({ 700, 650});
		S->SetScale({ 490, 10});
		S->SetHealthWater();
	}

	// NPC
	{
		Bathwoman* M = CreateActor<Bathwoman>();
		M->SetPos({ 1110, 745 });
	}

	// Player
	{
		Shantae = CreateActor<Player>();
		SHA = dynamic_cast<Player*>(Shantae);

		SHA->SetColMap(ColMap);
		SHA->SetPos({ 50, 747 });
		Shantae->GetLevel()->SetCameraPos({ 60, 100 });
		SHA->CameraMoveSwitch();
		SHA->SetAnimationStart(false);

		// UI
		CreateActor<GemWindow>();
		CreateActor<Health>();
		Inven = CreateActor<Inventory>();
	}
}

void Spa::Update(float _DeltaTime)
{
	OverlapTime += _DeltaTime;

	BlackBoxOutAnimation();
	LevelSet();
	Debugging();

	// 레벨 이동
	if (SHA->GetPos().x <= 35.0f
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

void Spa::LevelChangeStart(GameEngineLevel* _PrevLevel)
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
	Inventory::PlayerInven->DataCopy(Inven);
	Inventory::PlayerInven = Inven;

	Set = 1;

	SetPlayLevelHP(Player::MainPlayer->GetPlayerHP());
	SetPlayLevelMaxHP(Player::MainPlayer->GetPlayerMaxHP());
	SetPlayLevelGem(Player::MainPlayer->GetPlayerGem());
	SetPlayNewMaxHP(Player::MainPlayer->GetNewMaxHP());
	SetPlayLevelMonsterMilk(Player::MainPlayer->GetPlayerMonsterMilk());
	SetPlayLevelPikeBall(Player::MainPlayer->GetPlayerPikeBall());
	SetPlayLevelBubble(Player::MainPlayer->GetPlayerBubble());
	SetPlayLevelOctopus(Player::MainPlayer->GetPlayerOctopus());
	SetPlayLevelMeat(Player::MainPlayer->GetPlayerMeat());
	SetPlayLevelIDCard(Player::MainPlayer->GetPlayerIDCard());
}

void Spa::LevelChangeEnd(GameEngineLevel* _NextLevel)
{
	InBoxKill();
	AnimationSet = 1;
	BBoxOutCount = 1;
	SHA->SetPos({ 50, 747 });
	SHA->SetRoomAnimationStart(false);
}

void Spa::BlackBoxOutAnimation()
{
	if (1 == BBoxOutCount)
	{
		BBoxOutCount = 0;
		BBoxOut = CreateActor<BlackBox>();
		BBoxOut->FadeOutStart(2, 0.05f);
	}
}

void Spa::BlackBoxInAnimation()
{
	if (1 == BBoxInCount)
	{
		BBoxInCount = 0;
		BBoxIn = CreateActor<BlackBox>();
		BBoxIn->FadeInStart(2, 0);
	}
}

void Spa::InBoxKill()
{
	if (nullptr != BBoxIn)
	{
		BBoxIn->Death();
		BBoxIn = nullptr;
		BBoxInCount = 1;
		BBoxOutCount = 1;
	}
}

void Spa::LevelSet()
{
	if (1 == Set)
	{
		Set = 0;
		Player::MainPlayer = SHA;
		Player::MainPlayer->SetPlayerHP(GetPlayLevelHP());
		Player::MainPlayer->SetPlayerMaxHP(GetPlayLevelMaxHP());
		Player::MainPlayer->SetPlayerGem(GetPlayLevelGem());
		Player::MainPlayer->SetNewMaxHP(GetPlayNewMaxHP());
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
		if (190 <= SHA->GetPos().x)
		{
			SHA->SetStartAnimationStart(false);
			SHA->ChangeState(PlayerState::IDLE);
			AnimationSet = 0;
		}
	}
}

void Spa::Debugging()
{
	if (GameEngineInput::IsDown("ColMapSwitch"))
	{
		if (OverlapTime > 0.5f)
		{
			Spa_ColMap::ColMap->OnOffSwtich();
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
			GameEngineCore::GetInst()->ChangeLevel("Smith");
			OverlapTime = 0.0f;
		}
	}
	if (GameEngineInput::IsDown("Back"))
	{
		GameEngineCore::GetInst()->ChangeLevel("SelectMeun");
	}
}