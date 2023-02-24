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
#include "Move1_Sea.h"
#include "Move1_Sky.h"
#include "Player.h"

#include "Soldier_Bomberman.h"

#include "GemWindow.h"
#include "Health.h"
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
	CreateActor<Move1_Sky>();
	CreateActor<Move1_Sea>();
	CreateActor<Move1_ETCBackground>();
	CreateActor<Move1_Buliding>();

	// Map
	CreateActor<Move1_Map>();
	CreateActor<Move1_ColMap>();

	// Monster
	// 스포너사용법   스포너 위치    몹이름    콜맵    몹 젠 위치   리젠시간
	// CreateSpawner({ 250, 300 }, "blue", ColMap, { 350, 590 }, 5);

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

	// UI
	CreateActor<GemWindow>();
	CreateActor<Health>();

	// Player
	Shantae = CreateActor<Player>();
	SHA = dynamic_cast<Player*>(Shantae);

	SHA->SetColMap(ColMap);
	SHA->SetPos({ 106, 653 }); //  106, 653
	Shantae->GetLevel()->SetCameraPos({ 100, 50 }); // 100, 50
	SHA->SetAnimationStart(false);
	SHA->SetStartAnimationStart(false);
}

void Move1::Update(float _DeltaTime)
{
	OverlapTime += _DeltaTime;
	
	LevelSet();
	Debugging();
	CameraAction();

	// 레벨 이동
	if (SHA->GetPos().x >= 11720.0f
		&& PlayerState::MOVE == SHA->GetShantaeState())
	{
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
	SetPlayLevelHP(Player::MainPlayer->GetPlayerHP());
	SetPlayLevelMaxHP(Player::MainPlayer->GetPlayerMaxHP());
	SetPlayLevelGem(Player::MainPlayer->GetPlayerGem());
}

void Move1::LevelChangeEnd(GameEngineLevel* _NextLevel)
{
}

void Move1::BlackBoxOutAnimation()
{
	if (1 == BBoxOutCount)
	{
		BBoxOutCount = 0;
		BBoxOut = CreateActor<BlackBox>();
		BBoxOut->FadeOutStart(0, 0.5f);
	}
}

void Move1::BlackBoxInAnimation()
{
	if (1 == BBoxInCount)
	{
		BBoxInCount = 0;
		BBoxIn = CreateActor<BlackBox>();
		BBoxIn->FadeInStart(0, 0.5f);
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