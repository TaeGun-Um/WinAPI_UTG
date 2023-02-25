#include "Move0.h"

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
#include "Player.h"

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

	// Monster
	// 스포너사용법   스포너 위치    몹이름    콜맵    몹 젠 위치   리젠시간
	// CreateSpawner({ 250, 300 }, "blue", ColMap, { 350, 590 }, 5);
	{
		CreateSpawner({ 1860, 0 }, "blue", ColMap, { 3251, 340 }, 5);
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