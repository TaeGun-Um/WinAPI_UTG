#include "Boss.h"

#include <GameEngineBase/GameEngineDirectory.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineResources.h>
#include <GameEngineCore/GameEngineRender.h>
#include <GameEngineCore/GameEngineCore.h>

#include "Boss_ColMap.h"
#include "Boss_ETCBackground.h"
#include "Boss_Map.h"
#include "Boss_Sky.h"

#include "Player.h"
#include "Boss_Tank.h"
#include "AmmoBaron.h"

#include "GemWindow.h"
#include "Health.h"
#include "ObjectLoad.h"

Boss::Boss() 
{
}

Boss::~Boss() 
{
}

void Boss::Loading()
{
	ColMap = ObjectLoad::GetObjectLoadPtr()->GetColMap("Boss");

	// Background(¼ø¼­)
	CreateActor<Boss_Sky>();
	CreateActor<Boss_ETCBackground>();

	// Map
	CreateActor<Boss_Map>();
	CreateActor<Boss_ColMap>();

	// Monster
	Tank = CreateActor<Boss_Tank>();
	BOS = dynamic_cast<Boss_Tank*>(Tank);
	Tank->SetPos({ 1200, 750 });
	BOS->SetColMap(ColMap);

	GameEngineActor* amo = CreateActor<AmmoBaron>();
	AmmoBaron* AM = dynamic_cast<AmmoBaron*>(amo);
	amo->SetPos({ 1200, 400 });
	AM->SetColMap(ColMap);
	
	// UI
	CreateActor<GemWindow>();
	CreateActor<Health>();

	// Player
	Shantae = CreateActor<Player>();
	SHA = dynamic_cast<Player*>(Shantae);

	SHA->SetColMap(ColMap);
	SHA->SetPos({ 200, 700 });
	Shantae->GetLevel()->SetCameraPos({ 125, 130 });
	SHA->CameraMoveSwitch();
}

void Boss::Update(float _DeltaTime)
{
	if (1 == Set)
	{
		Set = 0;

		Player::MainPlayer = SHA;
		Player::MainPlayer->SetPlayerHP(GetPlayLevelHP());
		Player::MainPlayer->SetPlayerMaxHP(GetPlayLevelMaxHP());
		Player::MainPlayer->SetPlayerGem(GetPlayLevelGem());
	}

	OverlapTime += _DeltaTime;

	if (GameEngineInput::IsDown("ColMapSwitch"))
	{
		if (OverlapTime > 0.5f)
		{
			Boss_ColMap::ColMap->OnOffSwtich();
			OverlapTime = 0.0f;
		}
	}
	if (GameEngineInput::IsPress("BeforeLevel"))
	{
		if (OverlapTime > 0.5f)
		{
			GameEngineCore::GetInst()->ChangeLevel("BeforeBoss");
			OverlapTime = 0.0f;
		}
	}
	if (GameEngineInput::IsPress("NextLevel"))
	{
		if (OverlapTime > 0.5f)
		{
			GameEngineCore::GetInst()->ChangeLevel("Scuttle");
			OverlapTime = 0.0f;
		}
	}
	if (GameEngineInput::IsDown("Back"))
	{
		GameEngineCore::GetInst()->ChangeLevel("SelectMeun");
	}

	if (SHA->GetPos().x >= 1000.0f)
	{
		SHA->CameraMoveFalse();
	}
	else if (SHA->GetPos().x >= 860.0f)
	{
		SHA->CameraMoveTrue();
	}
	else if (SHA->GetPos().x <= 860.0f)
	{
		SHA->CameraMoveFalse();
		Shantae->GetLevel()->SetCameraPos({ 125, 130 });
	}

	if (SHA->GetPos().x >= 1600.0f)
	{
		GameEngineCore::GetInst()->ChangeLevel("Scuttle");
	}
}

void Boss::LevelChangeStart(GameEngineLevel* _PrevLevel)
{
	BGMPlayer = GameEngineResources::GetInst().SoundPlayToControl("Boss_Battle.mp3");
	BGMPlayer.Volume(0.0f); // º¼·ý ²¨³ùÀ½
	BGMPlayer.LoopCount(100);

	SetPlayLevelHP(Player::MainPlayer->GetPlayerHP());
	SetPlayLevelMaxHP(Player::MainPlayer->GetPlayerMaxHP());
	SetPlayLevelGem(Player::MainPlayer->GetPlayerGem());
}

void Boss::LevelChangeEnd(GameEngineLevel* _NextLevel)
{
	BGMPlayer.Stop();
}
