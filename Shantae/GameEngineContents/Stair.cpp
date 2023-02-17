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

#include "Soldier_Blue.h"

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

	// Background(¼ø¼­)
	CreateActor<Stair_Sky>();
	CreateActor<Stair_Tower>();
	CreateActor<Stair_Bush2>();
	CreateActor<Stair_Bush1>();
	CreateActor<Stair_Stair>();

	// Map
	CreateActor<Stair_Map>();
	CreateActor<Stair_ColMap>();

	// Monster
	// ½ºÆ÷³Ê»ç¿ë¹ý   ½ºÆ÷³Ê À§Ä¡    ¸÷ÀÌ¸§    ÄÝ¸Ê    ¸÷ Á¨ À§Ä¡   ¸®Á¨½Ã°£
	CreateSpawner({ 800, 2700 }, "blue", ColMap, { 372, 2018 }, 2);

	// UI
	CreateActor<GemWindow>();
	CreateActor<Health>();

	// Player
	Shantae = CreateActor<Player>();
	SHA = dynamic_cast<Player*>(Shantae);

	SHA->SetColMap(ColMap);
	SHA->SetPos({ 400, 3562 });
	Shantae->GetLevel()->SetCameraPos({ 200, 3000 });
	SHA->CameraMoveSwitch();
}

void Stair::Update(float _DeltaTime)
{
	if (1 == Set)
	{
		Set = 0;

		Player::MainPlayer = SHA;
		Player::MainPlayer->SetPlayerHP(GetPlayLevelHP());
		Player::MainPlayer->SetPlayerMaxHP(GetPlayLevelMaxHP());
		Player::MainPlayer->SetPlayerGem(GetPlayLevelGem());
	}

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
		// SHA Pos 200 3550
		float y = SHA->GetPos().y - 460;
		SHA->GetLevel()->SetCameraPos({ 200, y });
	}

	OverlapTime += _DeltaTime;

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

	if (SHA->GetPos().x >= 1485.0f)
	{
		GameEngineCore::GetInst()->ChangeLevel("Machinegun");
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