#include "BeforeBoss.h"

#include <GameEngineBase/GameEngineDirectory.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineResources.h>
#include <GameEngineCore/GameEngineRender.h>
#include <GameEngineCore/GameEngineCore.h>

#include "Move0.h"
#include "BeforeBoss_Background.h"
#include "BeforeBoss_ColMap.h"
#include "BeforeBoss_Map.h"
#include "Sky.h"
#include "Wave.h"
#include "Player.h"
#include "ItemBox.h"

#include "GemWindow.h"
#include "Health.h"
#include "Inventory.h"

#include "ObjectLoad.h"
#include "BlackBox.h"

BeforeBoss::BeforeBoss() 
{
}

BeforeBoss::~BeforeBoss() 
{
}

void BeforeBoss::Loading()
{
	ColMap = ObjectLoad::GetObjectLoadPtr()->GetColMap("BeforeBoss");

	// Background(순서)
	{
		Sky* Sk = CreateActor<Sky>();
		Sk->SetSkyYPos(-50);
		Sk->SetSkySpeed(25.0f);
	}
	
	CreateActor<BeforeBoss_Background>();

	// Map
	CreateActor<BeforeBoss_Map>();
	CreateActor<BeforeBoss_ColMap>();

	// wave
	{
		GameEngineActor* W1 = CreateActor<Wave>();
		W1->SetPos({ 190, 780 });
		GameEngineActor* W2 = CreateActor<Wave>();
		W2->SetPos({ 581, 780 });
		GameEngineActor* W3 = CreateActor<Wave>();
		W3->SetPos({ 972, 780 });
		GameEngineActor* W4 = CreateActor<Wave>();
		W4->SetPos({ 1363, 780 });
	}

	// Item
	{
		ItemBox* Box = CreateActor<ItemBox>();
		Box->SetPos({ 640, 600 });
		Box->SetColMap(ColMap);
		Box->SetItemValue(OCT);
	}

	// Player
	{
		Shantae = CreateActor<Player>();
		SHA = dynamic_cast<Player*>(Shantae);

		SHA->SetColMap(ColMap);
		SHA->SetPos({ 5, 603 });
		Shantae->GetLevel()->SetCameraPos({ 0, 50 });
		SHA->CameraMoveSwitch();
		SHA->SetAnimationStart(false);
		SHA->SetStartAnimationStart(false);

		// UI
		CreateActor<GemWindow>();
		CreateActor<Health>();
		Inven = CreateActor<Inventory>();
	}
}

void BeforeBoss::Update(float _DeltaTime)
{
	OverlapTime += _DeltaTime;

	BlackBoxOutAnimation();
	LevelSet();
	Debugging();
		
	if (GameEngineInput::IsDown("MonsterTest"))
	{
		IsBossDeath = true;
	}

	if (true == IsBossDeath)
	{
		// 레벨 이동
		if (SHA->GetPos().x >= 1250.0f
			&& PlayerState::MOVE == SHA->GetShantaeState())
		{
			BlackBoxInAnimation();
			SHA->SetAnimationStart(true);
			SHA->SetMoveSpeed(100.0f);
			if (true == SHA->LevelChangeAnimation(_DeltaTime))
			{
				GameEngineCore::GetInst()->ChangeLevel("Boss");
			}
		}
	}
}

void BeforeBoss::LevelChangeStart(GameEngineLevel* _PrevLevel)
{
	Inventory::PlayerInven->DataCopy(Inven);
	Inventory::PlayerInven = Inven;

	SetPlayLevelHP(Player::MainPlayer->GetPlayerHP());
	SetPlayLevelMaxHP(Player::MainPlayer->GetPlayerMaxHP());
	SetPlayLevelGem(Player::MainPlayer->GetPlayerGem());
}

void BeforeBoss::LevelChangeEnd(GameEngineLevel* _NextLevel)
{
	Move0::FieldBGMPlayer.Stop();
	InBoxKill();
}

void BeforeBoss::BlackBoxOutAnimation()
{
	if (1 == BBoxOutCount)
	{
		BBoxOutCount = 0;
		BBoxOut = CreateActor<BlackBox>();
		BBoxOut->FadeOutStart(2, 0.01f);
	}
}

void BeforeBoss::BlackBoxInAnimation()
{
	if (1 == BBoxInCount)
	{
		BBoxInCount = 0;
		BBoxIn = CreateActor<BlackBox>();
		BBoxIn->FadeInStart(2, 0.1f);
	}
}

void BeforeBoss::InBoxKill()
{
	if (nullptr != BBoxIn)
	{
		BBoxIn->Death();
		BBoxIn = nullptr;
		BBoxInCount = 1;
		BBoxOutCount = 1;
	}
}

void BeforeBoss::LevelSet()
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
		if (130 <= SHA->GetPos().x)
		{
			SHA->SetStartAnimationStart(false);
			SHA->ChangeState(PlayerState::IDLE);
			AnimationSet = 0;
		}
	}
}

void BeforeBoss::Debugging()
{
	if (GameEngineInput::IsDown("ColMapSwitch"))
	{
		if (OverlapTime > 0.5f)
		{
			BeforeBoss_ColMap::ColMap->OnOffSwtich();
			OverlapTime = 0.0f;
		}
	}
	if (GameEngineInput::IsDown("BeforeLevel"))
	{
		if (OverlapTime > 0.5f)
		{
			GameEngineCore::GetInst()->ChangeLevel("BoomBridge");
			OverlapTime = 0.0f;
		}
	}
	if (GameEngineInput::IsDown("NextLevel"))
	{
		if (OverlapTime > 0.5f)
		{
			GameEngineCore::GetInst()->ChangeLevel("Boss");
			OverlapTime = 0.0f;
		}
	}
	if (GameEngineInput::IsDown("Back"))
	{
		GameEngineCore::GetInst()->ChangeLevel("SelectMeun");
	}
}