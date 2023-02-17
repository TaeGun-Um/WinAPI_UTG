#include "BeforeBoss.h"

#include <GameEngineBase/GameEngineDirectory.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineResources.h>
#include <GameEngineCore/GameEngineRender.h>
#include <GameEngineCore/GameEngineCore.h>

#include "Move0.h"
#include "Move0_Sky.h"
#include "BeforeBoss_Background.h"
#include "BeforeBoss_ColMap.h"
#include "BeforeBoss_Map.h"
#include "Player.h"

#include "GemWindow.h"
#include "Health.h"
#include "ObjectLoad.h"

BeforeBoss::BeforeBoss() 
{
}

BeforeBoss::~BeforeBoss() 
{
}

void BeforeBoss::Loading()
{
	ColMap = ObjectLoad::GetObjectLoadPtr()->GetColMap("BeforeBoss");

	// Background(����)
	CreateActor<Move0_Sky>();
	CreateActor<BeforeBoss_Background>();

	// Map
	CreateActor<BeforeBoss_Map>();
	CreateActor<BeforeBoss_ColMap>();

	// Monster

	// UI
	CreateActor<GemWindow>();
	CreateActor<Health>();

	// Player
	Shantae = CreateActor<Player>();
	SHA = dynamic_cast<Player*>(Shantae);

	SHA->SetColMap(ColMap);
	SHA->SetPos({ 200, 550 });
	Shantae->GetLevel()->SetCameraPos({ 0, 50 });
	SHA->CameraMoveSwitch();
}

void BeforeBoss::Update(float _DeltaTime)
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
			BeforeBoss_ColMap::ColMap->OnOffSwtich();
			OverlapTime = 0.0f;
		}
	}
	if (GameEngineInput::IsPress("BeforeLevel"))
	{
		if (OverlapTime > 0.5f)
		{
			GameEngineCore::GetInst()->ChangeLevel("BoomBridge");
			OverlapTime = 0.0f;
		}
	}
	if (GameEngineInput::IsPress("NextLevel"))
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

	if (SHA->GetPos().x >= 1200.0f)
	{
		GameEngineCore::GetInst()->ChangeLevel("Boss");
	}
}

void BeforeBoss::LevelChangeStart(GameEngineLevel* _PrevLevel)
{
	SetPlayLevelHP(Player::MainPlayer->GetPlayerHP());
	SetPlayLevelMaxHP(Player::MainPlayer->GetPlayerMaxHP());
	SetPlayLevelGem(Player::MainPlayer->GetPlayerGem());
}

void BeforeBoss::LevelChangeEnd(GameEngineLevel* _NextLevel)
{
	Move0::FieldBGMPlayer.Stop();
}