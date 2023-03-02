#include "Stair.h"

#include <GameEngineBase/GameEngineDirectory.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineResources.h>
#include <GameEngineCore/GameEngineRender.h>
#include <GameEngineCore/GameEngineCore.h>

#include "Stair_Bush1.h"
#include "Stair_Bush2.h"
#include "Stair_ColMap.h"
#include "Stair_Map.h"
#include "Stair_Stair.h"
#include "Stair_Tower.h"
#include "Sky.h"

#include "Player.h"
#include "Soldier_Black.h"
#include "Mermaid.h"

#include "Jar.h"
#include "Jar_Big.h"

#include "GemWindow.h"
#include "Health.h"
#include "Inventory.h"

#include "ObjectLoad.h"
#include "BlackBox.h"

Stair::Stair() 
{
}

Stair::~Stair() 
{
}

void Stair::Loading()
{
	ColMap = ObjectLoad::GetObjectLoadPtr()->GetColMap("Stair");

	// Background(순서)
	{
		Sky* Sk = CreateActor<Sky>();
		Sk->SetSkyYPos(200);
		Sk->SetSkySpeed(25.0f);
	}

	CreateActor<Stair_Tower>();
	CreateActor<Stair_Bush2>();
	CreateActor<Stair_Bush1>();
	CreateActor<Stair_Stair>();

	// Map
	CreateActor<Stair_Map>();
	CreateActor<Stair_ColMap>();

	// Item
	{
		Jar* j1 = CreateActor<Jar>();
		j1->SetPos({ 363, 2780 });
		j1->SetColMap(ColMap);
		j1->SetGround(48);

		Jar* j2 = CreateActor<Jar>();
		j2->SetPos({ 415, 2780 });
		j2->SetColMap(ColMap);
		j2->SetGround(48);

		Jar* j3 = CreateActor<Jar>();
		j3->SetPos({ 363 ,1965 });
		j3->SetColMap(ColMap);
		j3->SetGround(48);

		Jar* j4 = CreateActor<Jar>();
		j4->SetPos({ 415, 1965 });
		j4->SetColMap(ColMap);
		j4->SetGround(48);

		Jar* j5 = CreateActor<Jar>();
		j5->SetPos({ 363, 1150 });
		j5->SetColMap(ColMap);
		j5->SetGround(46);

		Jar* j6 = CreateActor<Jar>();
		j6->SetPos({ 415, 1150 });
		j6->SetColMap(ColMap);
		j6->SetGround(46);

		Jar_Big* jB = CreateActor<Jar_Big>();
		jB->SetPos({ 1262, 3560 });
		jB->SetColMap(ColMap);
	}

	// Monster
	// 스포너사용법   스포너 위치   몹이름   콜맵    몹 젠 위치   리젠시간
	{
		CreateSpawner({ 800, 2700 }, "blue", ColMap, { 372, 2015 }, 2);

		Soldier_Black* Spawn3 = CreateActor<Soldier_Black>();
		Spawn3->SetPos({ 1185, 895 });
		Spawn3->SetColMap(ColMap);

		Mermaid* Mer1 = CreateActor<Mermaid>();
		Mer1->SetPos({ 1285, 3250 });
		Mer1->SetColMap(ColMap);

		Mermaid* Mer2 = CreateActor<Mermaid>();
		Mer2->SetPos({ 1285, 2425 });
		Mer2->SetColMap(ColMap);

		Mermaid* Mer3 = CreateActor<Mermaid>();
		Mer3->SetPos({ 475, 1195 });
		Mer3->SetColMap(ColMap);
		Mer3->SetDirect(false);
	}

	// Player
	{
		Shantae = CreateActor<Player>();
		SHA = dynamic_cast<Player*>(Shantae);

		SHA->SetColMap(ColMap);
		SHA->SetPos({ 200, 3563 });
		Shantae->GetLevel()->SetCameraPos({ 200, 3000 });
		SHA->CameraMoveSwitch();
		SHA->SetAnimationStart(false);
		SHA->SetStartAnimationStart(false);

		// UI
		CreateActor<GemWindow>();
		CreateActor<Health>();
		Inven = CreateActor<Inventory>();
	}
}

void Stair::Update(float _DeltaTime)
{
	OverlapTime += _DeltaTime;

	BlackBoxOutAnimation();
	LevelSet();
	Debugging();
	CameraAction();

	// 레벨 이동
	if (SHA->GetPos().x >= 1435.0f
		&& PlayerState::MOVE == SHA->GetShantaeState())
	{
		BlackBoxInAnimation();
		SHA->SetAnimationStart(true);
		SHA->SetMoveSpeed(100.0f);
		if (true == SHA->LevelChangeAnimation(_DeltaTime))
		{
			GameEngineCore::GetInst()->ChangeLevel("Machinegun");
		}
	}
}

void Stair::LevelChangeStart(GameEngineLevel* _PrevLevel)
{
	Inventory::PlayerInven->DataCopy(Inven);
	Inventory::PlayerInven = Inven;

	SetPlayLevelHP(Player::MainPlayer->GetPlayerHP());
	SetPlayLevelMaxHP(Player::MainPlayer->GetPlayerMaxHP());
	SetPlayLevelGem(Player::MainPlayer->GetPlayerGem());
}

void Stair::LevelChangeEnd(GameEngineLevel* _NextLevel)
{
	InBoxKill();
}

void Stair::BlackBoxOutAnimation()
{
	if (1 == BBoxOutCount)
	{
		BBoxOutCount = 0;
		BBoxOut = CreateActor<BlackBox>();
		BBoxOut->FadeOutStart(2, 0.01f);
	}
}

void Stair::BlackBoxInAnimation()
{
	if (1 == BBoxInCount)
	{
		BBoxInCount = 0;
		BBoxIn = CreateActor<BlackBox>();
		BBoxIn->FadeInStart(2, 0.1f);
	}
}

void Stair::InBoxKill()
{
	if (nullptr != BBoxIn)
	{
		BBoxIn->Death();
		BBoxIn = nullptr;
		BBoxInCount = 1;
		BBoxOutCount = 1;
	}
}

void Stair::LevelSet()
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
		if (350 <= SHA->GetPos().x)
		{
			SHA->SetStartAnimationStart(false);
			SHA->ChangeState(PlayerState::IDLE);
			AnimationSet = 0;
		}
	}
}

void Stair::CameraAction()
{
	if (3450 > SHA->GetPos().y)
	{
		YCamera = true;
	}
	if (3450 <= SHA->GetPos().y)
	{
		YCamera = false;
	}
	if (900 >= SHA->GetPos().y)
	{
		YCamera = false;
	}

	if (true == YCamera)
	{
		float y = SHA->GetPos().y - 460;
		SHA->GetLevel()->SetCameraPos({ 200, y });
	}
}

void Stair::Debugging()
{
	if (GameEngineInput::IsDown("ColMapSwitch"))
	{
		if (OverlapTime > 0.5f)
		{
			Stair_ColMap::ColMap->OnOffSwtich();
			OverlapTime = 0.0f;
		}
	}
	if (GameEngineInput::IsDown("BeforeLevel"))
	{
		if (OverlapTime > 0.5f)
		{
			GameEngineCore::GetInst()->ChangeLevel("Move1");
			OverlapTime = 0.0f;
		}
	}
	if (GameEngineInput::IsDown("NextLevel"))
	{
		if (OverlapTime > 0.5f)
		{
			GameEngineCore::GetInst()->ChangeLevel("Machinegun");
			OverlapTime = 0.0f;
		}
	}
	if (GameEngineInput::IsDown("Back"))
	{
		GameEngineCore::GetInst()->ChangeLevel("SelectMeun");
	}
}