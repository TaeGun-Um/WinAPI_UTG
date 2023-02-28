#include "Move0.h"

#include <GameEngineBase/GameEngineRandom.h>
#include <GameEngineBase/GameEngineDirectory.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineResources.h>
#include <GameEngineCore/GameEngineRender.h>
#include <GameEngineCore/GameEngineCore.h>

#include "Move0_Buliding.h"
#include "Move0_ColMap.h"
#include "Move0_Map.h"
#include "Move0_ETCBackground.h"
#include "Wave.h"
#include "Ship.h"
#include "Building1.h"
#include "Building2.h"
#include "Player.h"

#include "Merchant.h"
#include "Boy.h"
#include "Girl.h"
#include "Jug_Woman.h"
#include "Stylist.h"
#include "Desert_Man.h"

#include "Sea.h"
#include "Sky.h"

#include "GemWindow.h"
#include "Health.h"
#include "ObjectLoad.h"
#include "BlackBox.h"

GameEngineSoundPlayer Move0::FieldBGMPlayer = 0;

Move0::Move0() 
{
}

Move0::~Move0() 
{
}

void Move0::Loading()
{
	ColMap = ObjectLoad::GetObjectLoadPtr()->GetColMap("Move0");

	// Background(순서)
	{
		Sky* Sk = CreateActor<Sky>();
		Sk->SetSkyYPos(0);
		Sk->SetSkySpeed(25.0f);
		Sea* Se = CreateActor<Sea>();
		Se->SetPos({ 1000, 500 });
		Se->SetCount();
	}

	CreateActor<Move0_ETCBackground>();

	// rotationActor
	{
		Ship* Ship0 = CreateActor<Ship>();
		Ship0->SetPos({ 1250, 400 });
		Ship0->SetRotationStop();

		Ship* Ship1 = CreateActor<Ship>();
		Ship1->SetPos({ 5850, 400 });

		Building1* B0 = CreateActor<Building1>();
		B0->SetPos({ 3000, 100 });
		B0->SetLeftBreak();

		Building1* B1 = CreateActor<Building1>();
		B1->SetPos({ 5030, 350 });
		B1->SetRightBreak();

		Building2* B2 = CreateActor<Building2>();
		B2->SetPos({ 9550, 300 });
	}
	CreateActor<Move0_Buliding>();

	// Map
	CreateActor<Move0_Map>();
	CreateActor<Move0_ColMap>();

	// wave
	{
		GameEngineActor* W1 = CreateActor<Wave>();
		W1->SetPos({ 7300, 775 });
		GameEngineActor* W2 = CreateActor<Wave>();
		W2->SetPos({ 7691, 775 });
		GameEngineActor* W3 = CreateActor<Wave>();
		W3->SetPos({ 8082, 775 });
		GameEngineActor* W4 = CreateActor<Wave>();
		W4->SetPos({ 8473, 775 });
		GameEngineActor* W5 = CreateActor<Wave>();
		W5->SetPos({ 8864, 775 });
	}

	// NPC
	{
		
		Desert_Man* M12 = CreateActor<Desert_Man>();
		M12->SetPos({ 1390, 641 });
		M12->SetRun();
		M12->SetRunSpeed(230);

		Merchant* M1 = CreateActor<Merchant>();
		M1->SetPos({ 1970, 641 });
		M1->SetRun();
		M1->SetRunSpeed(255);

		Jug_Woman* M8 = CreateActor<Jug_Woman>();
		M8->SetPos({ 1650, 641 });
		M8->SetRun();
		M8->SetRunSpeed(215);

		Boy* M3 = CreateActor<Boy>();
		M3->SetPos({ 1400, 641 });
		M3->SetRun();
		M3->SetRunSpeed(240);

		Stylist* M11 = CreateActor<Stylist>();
		M11->SetPos({ 1590, 641 });
		M11->SetRun();
		M11->SetRunSpeed(205);

		Desert_Man* M13 = CreateActor<Desert_Man>();
		M13->SetPos({ 1700, 641 });
		M13->SetRun();
		M13->SetRunSpeed(225);

		Merchant* M2 = CreateActor<Merchant>();
		M2->SetPos({ 1520, 641 });
		M2->SetRun();
		M2->SetRunSpeed(260);

		Girl* M5 = CreateActor<Girl>();
		M5->SetPos({ 1550, 641 });
		M5->SetRun();
		M5->SetRunSpeed(220);

		Boy* M4 = CreateActor<Boy>();
		M4->SetPos({ 2000, 641 });
		M4->SetRun();
		M4->SetRunSpeed(235);

		Jug_Woman* M7 = CreateActor<Jug_Woman>();
		M7->SetPos({ 2000, 641 });
		M7->SetRun();
		M7->SetRunSpeed(220);

		Girl* M6 = CreateActor<Girl>();
		M6->SetPos({ 1750, 641 });
		M6->SetRun();
		M6->SetRunSpeed(225);

		Jug_Woman* M9 = CreateActor<Jug_Woman>();
		M9->SetPos({ 1290, 641 });
		M9->SetRun();
		M9->SetRunSpeed(195);

		Stylist* M10 = CreateActor<Stylist>();
		M10->SetPos({ 1960, 641 });
		M10->SetRun();
		M10->SetRunSpeed(195);

		Desert_Man* M14 = CreateActor<Desert_Man>();
		M14->SetPos({ 2070, 641 });
		M14->SetRun();
		M14->SetRunSpeed(240);

	}

	// Monster
	// 스포너사용법   스포너 위치    몹이름    콜맵    몹 젠 위치   리젠시간
	// CreateSpawner({ 250, 300 }, "blue", ColMap, { 350, 590 }, 5);
	{
		CreateSpawner({ 1860, 0 }, "blue", ColMap, { 3251, 637 }, 5);
		CreateSpawner({ 3852, 0 }, "blue", ColMap, { 4815, 280 }, 5);
		CreateSpawner({ 4423, 0 }, "blue", ColMap, { 5400, 637 }, 5);
		MonsterSpawner* s1 = CreateSpawner({ 6986, 0 }, "Red", ColMap, { 7357, 900 }, 5); // am
		s1->SetAmbushTrue();
		MonsterSpawner* s2 = CreateSpawner({ 7086, 0 }, "blue", ColMap, { 7457, 900 }, 5); // am
		s2->SetAmbushTrue();
		CreateSpawner({ 7350, 0 }, "blue", ColMap, { 8400, 544 }, 5);
		MonsterSpawner* s3 = CreateSpawner({ 8340, 0 }, "red", ColMap, { 8590, 900 }, 5); // am
		s3->SetAmbushTrue();
		MonsterSpawner* s4 = CreateSpawner({ 8440, 0 }, "blue", ColMap, { 8690, 900 }, 5); // am
		s4->SetAmbushTrue();
		CreateSpawner({ 8590, 0 }, "blue", ColMap, { 9580, 637 }, 5);
		CreateSpawner({ 8640, 0 }, "blue", ColMap, { 9720, 637 }, 5);
		CreateSpawner({ 8690, 0 }, "blue", ColMap, { 9930, 637 }, 5);
		CreateSpawner({ 8740, 0 }, "blue", ColMap, { 10040, 637 }, 5);
		CreateSpawner({ 10110, 0 }, "blue", ColMap, { 11225, 592 }, 5);
	}

	// Player
	{
		Shantae = CreateActor<Player>();
		SHA = dynamic_cast<Player*>(Shantae);

		SHA->SetColMap(ColMap);
		SHA->SetPos({ 49, 641 }); // { 49, 641 }
		Shantae->GetLevel()->SetCameraPos({ 50, 50 }); // { 50, 50 }
		SHA->SetAnimationStart(false);
		SHA->SetStartAnimationStart(false);

		// UI
		CreateActor<GemWindow>();
		CreateActor<Health>();
	}

}

void Move0::Update(float _DeltaTime)
{
	OverlapTime += _DeltaTime;

	BlackBoxOutAnimation();
	LevelSet();
	Debugging();
	CameraAction();

	// 레벨 이동
	if (SHA->GetPos().x >= 11800.0f
		&& PlayerState::MOVE == SHA->GetShantaeState())
	{
		BlackBoxInAnimation();
		SHA->SetAnimationStart(true);
		SHA->SetMoveSpeed(100.0f);
		if (true == SHA->LevelChangeAnimation(_DeltaTime))
		{
			GameEngineCore::GetInst()->ChangeLevel("Move1");
		}
	}

	if (1 == RunAnimation)
	{
		RunAnimation = 0;
		Player::MainPlayer->SetCameraShakinghard(10.0f, 3.0f);
		BGMPlayer = GameEngineResources::GetInst().SoundPlayToControl("Fleeing_crowd.mp3");
		BGMPlayer.Volume(0.35f);
		BGMPlayer.LoopCount(1);
	}
}

void Move0::LevelChangeStart(GameEngineLevel* _PrevLevel)
{
	FieldBGMPlayer = GameEngineResources::GetInst().SoundPlayToControl("We_Love_Burning_Town.mp3");
	FieldBGMPlayer.Volume(0.05f);
	FieldBGMPlayer.LoopCount(100);

	SetPlayLevelHP(Player::MainPlayer->GetPlayerHP());
	SetPlayLevelMaxHP(Player::MainPlayer->GetPlayerMaxHP());
	SetPlayLevelGem(Player::MainPlayer->GetPlayerGem());
}

void Move0::LevelChangeEnd(GameEngineLevel* _NextLevel)
{
	// BGMPlayer.Stop();
	InBoxKill();
}

void Move0::BlackBoxOutAnimation()
{
	if (1 == BBoxOutCount)
	{
		BBoxOutCount = 0;
		BBoxOut = CreateActor<BlackBox>();
		BBoxOut->FadeOutStart(2, 0.25f);
	}
}

void Move0::BlackBoxInAnimation()
{
	if (1 == BBoxInCount)
	{
		BBoxInCount = 0;
		BBoxIn = CreateActor<BlackBox>();
		BBoxIn->FadeInStart(2, 0.1f);
	}
}

void Move0::InBoxKill()
{
	if (nullptr != BBoxIn)
	{
		BBoxIn->Death();
		BBoxIn = nullptr;
		BBoxInCount = 1;
		BBoxOutCount = 1;
	}
}

void Move0::LevelSet()
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
		if (615 <= SHA->GetPos().x)
		{
			SHA->SetStartAnimationStart(false);
			SHA->ChangeState(PlayerState::IDLE);
			AnimationSet = 0;
		}
	}
}

void Move0::CameraAction()
{
	if (SHA->GetPos().x >= 11160.0f)
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
		Shantae->GetLevel()->SetCameraPos({ 50, 50 });
	}
}

void Move0::Debugging()
{
	if (GameEngineInput::IsDown("ColMapSwitch"))
	{
		if (OverlapTime > 0.5f)
		{
			Move0_ColMap::ColMap->OnOffSwtich();
			OverlapTime = 0.0f;
		}
	}
	if (GameEngineInput::IsDown("BeforeLevel"))
	{
		if (OverlapTime > 0.5f)
		{
			GameEngineCore::GetInst()->ChangeLevel("HouseFront");
			OverlapTime = 0.0f;
		}
	}
	if (GameEngineInput::IsDown("NextLevel"))
	{
		if (OverlapTime > 0.5f)
		{
			GameEngineCore::GetInst()->ChangeLevel("Move1");
			OverlapTime = 0.0f;
		}
	}
	if (GameEngineInput::IsDown("Back"))
	{
		GameEngineCore::GetInst()->ChangeLevel("SelectMeun");
	}
}