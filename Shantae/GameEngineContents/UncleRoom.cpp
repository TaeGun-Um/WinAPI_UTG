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
#include "Player.h"
#include "Sky.h"
#include "Sea.h"

#include "GemWindow.h"
#include "Health.h"
#include "ObjectLoad.h"
#include "BlackBox.h"

UncleRoom::UncleRoom() 
{
}

UncleRoom::~UncleRoom() 
{
}

void UncleRoom::Loading()
{
	ColMap = ObjectLoad::GetObjectLoadPtr()->GetColMap("UncleRoom");

	// Background(순서)
	{
		Sky* Sk = CreateActor<Sky>();
		Sk->SetSkyYPos(200);
		Sk->SetSkySpeed(25.0f);
		Sea* Se = CreateActor<Sea>();
		Se->SetPos({ 650, 700 });
	}

	CreateActor<UncleRoom_Background>();
				
	// Map		
	CreateActor<UncleRoom_Map>();
	CreateActor<UncleRoom_Front>();
	CreateActor<UncleRoom_ColMap>();

	// Player
	{
		Shantae = CreateActor<Player>();
		SHA = dynamic_cast<Player*>(Shantae);

		SHA->SetColMap(ColMap);
		SHA->SetPos({ 90, 781 });
		Shantae->GetLevel()->SetCameraPos({ 50, 100 });
		SHA->CameraMoveSwitch();
		SHA->SetAnimationStart(false);

		// UI
		CreateActor<GemWindow>();
		CreateActor<Health>();
	}

}

void UncleRoom::Update(float _DeltaTime)
{
	OverlapTime += _DeltaTime;

	BlackBoxOutAnimation();
	LevelSet();
	Debugging();

	// 레벨 이동
	if (SHA->GetPos().x <= 50.0f)
	{
		GameEngineCore::GetInst()->ChangeLevel("Scuttle");
	}
}

void UncleRoom::LevelChangeStart(GameEngineLevel* _PrevLevel)
{
	BGMPlayer = GameEngineResources::GetInst().SoundPlayToControl("Uncle_Room.mp3");
	BGMPlayer.Volume(0.1f);
	BGMPlayer.LoopCount(100);

	SetPlayLevelHP(Player::MainPlayer->GetPlayerHP());
	SetPlayLevelMaxHP(Player::MainPlayer->GetPlayerMaxHP());
	SetPlayLevelGem(Player::MainPlayer->GetPlayerGem());
}

void UncleRoom::LevelChangeEnd(GameEngineLevel* _NextLevel)
{
	BGMPlayer.Stop();
	// InBoxKill();
}

void UncleRoom::BlackBoxOutAnimation()
{
	if (1 == BBoxOutCount)
	{
		BBoxOutCount = 0;
		BBoxOut = CreateActor<BlackBox>();
		BBoxOut->FadeOutStart(2, 0);
	}
}

void UncleRoom::BlackBoxInAnimation()
{
	if (1 == BBoxInCount)
	{
		BBoxInCount = 0;
		BBoxIn = CreateActor<BlackBox>();
		BBoxIn->FadeInStart(2, 0.5f);
	}
}

void UncleRoom::InBoxKill()
{
	if (nullptr != BBoxIn)
	{
		BBoxIn->Death();
		BBoxIn = nullptr;
		BBoxInCount = 1;
		BBoxOutCount = 1;
	}
}

void UncleRoom::LevelSet()
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
}

void UncleRoom::Debugging()
{
	if (GameEngineInput::IsDown("ColMapSwitch"))
	{
		if (OverlapTime > 0.5f)
		{
			UncleRoom_ColMap::ColMap->OnOffSwtich();
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
			GameEngineCore::GetInst()->ChangeLevel("Shop");
			OverlapTime = 0.0f;
		}
	}
	if (GameEngineInput::IsDown("Back"))
	{
		GameEngineCore::GetInst()->ChangeLevel("SelectMeun");
	}
}