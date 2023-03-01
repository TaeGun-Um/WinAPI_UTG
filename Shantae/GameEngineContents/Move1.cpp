#include "Move1.h"

#include <GameEngineBase/GameEngineDirectory.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineResources.h>
#include <GameEngineCore/GameEngineRender.h>
#include <GameEngineCore/GameEngineCore.h>

#include "Move1_Buliding.h"
#include "Move1_ColMap.h"
#include "Move1_ETCBackground.h"
#include "Move1_Map.h"
#include "Player.h"
#include "Wave.h"
#include "Sea.h"
#include "Sky.h"
#include "Ship.h"
#include "Building1.h"

#include "Soldier_Bomberman.h"
#include "Jar.h"
#include "Jar_Big.h"

#include "GemWindow.h"
#include "Health.h"
#include "Inventory.h"

#include "ObjectLoad.h"
#include "BlackBox.h"

Move1::Move1() 
{
}

Move1::~Move1() 
{
}

void Move1::Loading()
{
	ColMap = ObjectLoad::GetObjectLoadPtr()->GetColMap("Move1");

	// Background(순서)
	{
		Sky* Sk = CreateActor<Sky>();
		Sk->SetSkyYPos(0);
		Sk->SetSkySpeed(25.0f);
		Sea* Se = CreateActor<Sea>();
		Se->SetPos({ 900, 600 });
		Se->SetCount();
	}

	CreateActor<Move1_ETCBackground>();
	// rotationActor
	{
		Ship* Ship0 = CreateActor<Ship>();
		Ship0->SetPos({ 6475, 425 });
		Ship0->SetRotationStop();

		Building1* B0 = CreateActor<Building1>();
		B0->SetPos({ 1700, 20 });
		B0->SetLeftBreak();

		Building1* B1 = CreateActor<Building1>();
		B1->SetPos({ 3950, 15 });
		B1->SetRightBreak();

		Building1* B2 = CreateActor<Building1>();
		B2->SetPos({ 8350, 70 });
		B2->SetLeftBreak();

		Building1* B3 = CreateActor<Building1>();
		B3->SetPos({ 8800, -65 });
		B3->SetLeftBreak();
	}
	CreateActor<Move1_Buliding>();

	// Map
	CreateActor<Move1_Map>();
	CreateActor<Move1_ColMap>();

	// wave
	{
		GameEngineActor* W1 = CreateActor<Wave>();
		W1->SetPos({ 2480, 775 });
		GameEngineActor* W2 = CreateActor<Wave>();
		W2->SetPos({ 4700, 775 });
		GameEngineActor* W3 = CreateActor<Wave>();
		W3->SetPos({ 5090, 775 });
		GameEngineActor* W4 = CreateActor<Wave>();
		W4->SetPos({ 5480, 775 });
		GameEngineActor* W5 = CreateActor<Wave>();
		W5->SetPos({ 5870, 775 });
		GameEngineActor* W6 = CreateActor<Wave>();
		W6->SetPos({ 7730, 775 });
		GameEngineActor* W10 = CreateActor<Wave>();
		W10->SetPos({ 8120, 775 });
		GameEngineActor* W7 = CreateActor<Wave>();
		W7->SetPos({ 8890, 775 });
		GameEngineActor* W8 = CreateActor<Wave>();
		W8->SetPos({ 9430, 775 });
		GameEngineActor* W9 = CreateActor<Wave>();
		W9->SetPos({ 10280, 775 });
	}

	// Item
	{
		Jar* j1 = CreateActor<Jar>();
		j1->SetPos({ 3080, 600 });
		j1->SetColMap(ColMap);
		j1->SetGround(45);

		Jar* j2 = CreateActor<Jar>();
		j2->SetPos({ 3131, 600 });
		j2->SetColMap(ColMap);
		j2->SetGround(45);

		Jar* j3 = CreateActor<Jar>();
		j3->SetPos({ 4189, 600 });
		j3->SetColMap(ColMap);
		j3->SetGround(45);

		Jar* j4 = CreateActor<Jar>();
		j4->SetPos({ 4239, 600 });
		j4->SetColMap(ColMap);
		j4->SetGround(45);

		Jar_Big* jB = CreateActor<Jar_Big>();
		jB->SetPos({ 11460, 645 });
		jB->SetColMap(ColMap);
	}

	// Monster
	// 스포너사용법   스포너 위치    몹이름    콜맵    몹 젠 위치   리젠시간
	// CreateSpawner({ 250, 300 }, "blue", ColMap, { 350, 590 }, 5);
	{
		Soldier_Bomberman* s1 = CreateActor<Soldier_Bomberman>();
		s1->SetPos({ 1767, 288 });
		s1->SetColMap(ColMap);
		CreateSpawner({ 2300, 0 }, "black", ColMap, { 3145, 651 }, 4);
		CreateSpawner({ 2300, 0 }, "Bomberman", ColMap, { 3277, 345 }, 4);
		CreateSpawner({ 3600, 0 }, "black", ColMap, { 4575, 650 }, 5);
		CreateSpawner({ 5850, 0 }, "Bomberman", ColMap, { 6755, 447 }, 5);
		CreateSpawner({ 5850, 0 }, "black", ColMap, { 7500, 650 }, 5);
		CreateSpawner({ 7845, 0 }, "Bomberman", ColMap, { 8718, 381 }, 5);
		CreateSpawner({ 7845, 0 }, "Bomberman", ColMap, { 9278, 545 }, 5);
		CreateSpawner({ 7845, 0 }, "Bomberman", ColMap, { 9932, 282 }, 5);
		CreateSpawner({ 9465, 0 }, "Bomberman", ColMap, { 10545, 446 }, 5);
	}

	// Player
	{
		Shantae = CreateActor<Player>();
		SHA = dynamic_cast<Player*>(Shantae);

		SHA->SetColMap(ColMap);
		SHA->SetPos({ 106, 653 }); //  106, 653
		Shantae->GetLevel()->SetCameraPos({ 100, 50 }); // 100, 50
		SHA->SetAnimationStart(false);
		SHA->SetStartAnimationStart(false);

		// UI
		CreateActor<GemWindow>();
		CreateActor<Health>();
		Inven = CreateActor<Inventory>();
	}
}

void Move1::Update(float _DeltaTime)
{
	OverlapTime += _DeltaTime;
	
	BlackBoxOutAnimation();
	LevelSet();
	Debugging();
	CameraAction();

	// 레벨 이동
	if (SHA->GetPos().x >= 11720.0f
		&& PlayerState::MOVE == SHA->GetShantaeState())
	{
		BlackBoxInAnimation();
		SHA->SetAnimationStart(true);
		SHA->SetMoveSpeed(100.0f);
		if (true == SHA->LevelChangeAnimation(_DeltaTime))
		{
			GameEngineCore::GetInst()->ChangeLevel("Stair");
		}
	}
}

void Move1::LevelChangeStart(GameEngineLevel* _PrevLevel)
{
	Inventory::PlayerInven = Inven;

	SetPlayLevelHP(Player::MainPlayer->GetPlayerHP());
	SetPlayLevelMaxHP(Player::MainPlayer->GetPlayerMaxHP());
	SetPlayLevelGem(Player::MainPlayer->GetPlayerGem());
}

void Move1::LevelChangeEnd(GameEngineLevel* _NextLevel)
{
	InBoxKill();
}

void Move1::BlackBoxOutAnimation()
{
	if (1 == BBoxOutCount)
	{
		BBoxOutCount = 0;
		BBoxOut = CreateActor<BlackBox>();
		BBoxOut->FadeOutStart(2, 0.1f);
	}
}

void Move1::BlackBoxInAnimation()
{
	if (1 == BBoxInCount)
	{
		BBoxInCount = 0;
		BBoxIn = CreateActor<BlackBox>();
		BBoxIn->FadeInStart(2, 0.1f);
	}
}

void Move1::InBoxKill()
{
	if (nullptr != BBoxIn)
	{
		BBoxIn->Death();
		BBoxIn = nullptr;
		BBoxInCount = 1;
		BBoxOutCount = 1;
	}
}

void Move1::LevelSet()
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
		if (575 <= SHA->GetPos().x)
		{
			SHA->SetStartAnimationStart(false);
			SHA->ChangeState(PlayerState::IDLE);
			AnimationSet = 0;
		}
	}
}

void Move1::CameraAction()
{
	if (SHA->GetPos().x >= 11040.0f)
	{
		SHA->CameraMoveFalse();
	}
	else if (SHA->GetPos().x >= 640.0f)
	{
		SHA->CameraMoveTrue();
	}
	else if (SHA->GetPos().x <= 640.0f)
	{
		SHA->CameraMoveFalse();
		Shantae->GetLevel()->SetCameraPos({ 100, 50 });
	}
}

void Move1::Debugging()
{
	if (GameEngineInput::IsDown("ColMapSwitch"))
	{
		if (OverlapTime > 0.5f)
		{
			Move1_ColMap::ColMap->OnOffSwtich();
			OverlapTime = 0.0f;
		}
	}
	if (GameEngineInput::IsDown("BeforeLevel"))
	{
		if (OverlapTime > 0.5f)
		{
			GameEngineCore::GetInst()->ChangeLevel("Move0");
			OverlapTime = 0.0f;
		}
	}
	if (GameEngineInput::IsDown("NextLevel"))
	{
		if (OverlapTime > 0.5f)
		{
			GameEngineCore::GetInst()->ChangeLevel("Stair");
			OverlapTime = 0.0f;
		}
	}
	if (GameEngineInput::IsDown("Back"))
	{
		GameEngineCore::GetInst()->ChangeLevel("SelectMeun");
	}
}