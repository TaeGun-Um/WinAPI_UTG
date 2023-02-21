#include "Stair.h"

#include <GameEngineBase/GameEngineDirectory.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineResources.h>
#include <GameEngineCore/GameEngineRender.h>
#include <GameEngineCore/GameEngineCore.h>

#include "Stair_Sky.h"
#include "Stair_Bush1.h"
#include "Stair_Bush2.h"
#include "Stair_ColMap.h"
#include "Stair_Map.h"
#include "Stair_Stair.h"
#include "Stair_Tower.h"

#include "Soldier_Black.h"

#include "Player.h"

#include "GemWindow.h"
#include "Health.h"
#include "ObjectLoad.h"

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
	CreateActor<Stair_Sky>();
	CreateActor<Stair_Tower>();
	CreateActor<Stair_Bush2>();
	CreateActor<Stair_Bush1>();
	CreateActor<Stair_Stair>();

	// Map
	CreateActor<Stair_Map>();
	CreateActor<Stair_ColMap>();

	// Monster
	// 스포너사용법   스포너 위치   몹이름   콜맵    몹 젠 위치   리젠시간
	CreateSpawner({ 800, 2700 }, "blue", ColMap, { 372, 2018 }, 2);

	Soldier_Black* Spawn3 = CreateActor<Soldier_Black>();
	Spawn3->SetPos({ 1185, 895 });
	Spawn3->SetColMap(ColMap);

	// UI
	CreateActor<GemWindow>();
	CreateActor<Health>();

	// Player
	Shantae = CreateActor<Player>();
	SHA = dynamic_cast<Player*>(Shantae);

	SHA->SetColMap(ColMap);
	SHA->SetPos({ 200, 3563 });
	Shantae->GetLevel()->SetCameraPos({ 200, 3000 });
	SHA->CameraMoveSwitch();
	SHA->SetAnimationStart(false);
	SHA->SetStartAnimationStart(false);
}

void Stair::Update(float _DeltaTime)
{
	OverlapTime += _DeltaTime;

	LevelSet();
	Debugging();
	CameraAction();

	// 레벨 이동
	if (SHA->GetPos().x >= 1435.0f
		&& PlayerState::MOVE == SHA->GetShantaeState())
	{
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
	SetPlayLevelHP(Player::MainPlayer->GetPlayerHP());
	SetPlayLevelMaxHP(Player::MainPlayer->GetPlayerMaxHP());
	SetPlayLevelGem(Player::MainPlayer->GetPlayerGem());
}

void Stair::LevelChangeEnd(GameEngineLevel* _NextLevel)
{
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
	if (GameEngineInput::IsPress("BeforeLevel"))
	{
		if (OverlapTime > 0.5f)
		{
			GameEngineCore::GetInst()->ChangeLevel("Move1");
			OverlapTime = 0.0f;
		}
	}
	if (GameEngineInput::IsPress("NextLevel"))
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