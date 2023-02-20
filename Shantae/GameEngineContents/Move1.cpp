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

Move1::Move1() 
{
}

Move1::~Move1() 
{
}

void Move1::Loading()
{
	ColMap = ObjectLoad::GetObjectLoadPtr()->GetColMap("Move1");

	// Background(¼ø¼­)
	CreateActor<Move1_Sky>();
	CreateActor<Move1_Sea>();
	CreateActor<Move1_ETCBackground>();
	CreateActor<Move1_Buliding>();

	// Map
	CreateActor<Move1_Map>();
	CreateActor<Move1_ColMap>();

	// Monster
	// ½ºÆ÷³Ê»ç¿ë¹ý   ½ºÆ÷³Ê À§Ä¡    ¸÷ÀÌ¸§    ÄÝ¸Ê    ¸÷ Á¨ À§Ä¡   ¸®Á¨½Ã°£
	// CreateSpawner({ 250, 300 }, "blue", ColMap, { 350, 590 }, 5);

	// CreateSpawner({ 800, 0 }, "Bomberman", ColMap, { 1767, 288 }, 5);

	Soldier_Bomberman* sss = CreateActor<Soldier_Bomberman>();
	sss->SetPos({ 1767, 288 });
	sss->SetColMap(ColMap);

	CreateSpawner({ 2300, 0 }, "black", ColMap, { 3145, 654 }, 6);
	CreateSpawner({ 2300, 0 }, "Bomberman", ColMap, { 3277, 348 }, 5);
	CreateSpawner({ 3600, 0 }, "black", ColMap, { 4575, 653 }, 5);
	CreateSpawner({ 5850, 0 }, "Bomberman", ColMap, { 6755, 450 }, 5);
	CreateSpawner({ 7845, 0 }, "Bomberman", ColMap, { 8718, 384 }, 5);
	CreateSpawner({ 7845, 0 }, "Bomberman", ColMap, { 9278, 548 }, 5);
	CreateSpawner({ 7845, 0 }, "Bomberman", ColMap, { 9932, 285 }, 5);
	CreateSpawner({ 9465, 0 }, "Bomberman", ColMap, { 10545, 449 }, 5);

	// UI
	CreateActor<GemWindow>();
	CreateActor<Health>();

	// Player
	Shantae = CreateActor<Player>();
	SHA = dynamic_cast<Player*>(Shantae);

	SHA->SetColMap(ColMap);
	SHA->SetPos({ 106, 653 });
	Shantae->GetLevel()->SetCameraPos({ 100, 50 });
	SHA->SetAnimationStart(false);
}

void Move1::Update(float _DeltaTime)
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

	OverlapTime += _DeltaTime;

	if (GameEngineInput::IsDown("ColMapSwitch"))
	{
		if (OverlapTime > 0.5f)
		{
			Move1_ColMap::ColMap->OnOffSwtich();
			OverlapTime = 0.0f;
		}
	}
	if (GameEngineInput::IsPress("BeforeLevel"))
	{
		if (OverlapTime > 0.5f)
		{
			GameEngineCore::GetInst()->ChangeLevel("Move0");
			OverlapTime = 0.0f;
		}
	}
	if (GameEngineInput::IsPress("NextLevel"))
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