#include "Smith.h"

#include <GameEngineBase/GameEngineDirectory.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineResources.h>
#include <GameEngineCore/GameEngineRender.h>
#include <GameEngineCore/GameEngineCore.h>

#include "Smith_Background.h"
#include "Smith_ColMap.h"
#include "Smith_Map.h"
#include "Smith_Sea.h"
#include "Smith_Sky.h"
#include "Player.h"

#include "GemWindow.h"
#include "Health.h"
#include "ObjectLoad.h"

Smith::Smith() 
{
}

Smith::~Smith() 
{
}

void Smith::Loading()
{
	ColMap = ObjectLoad::GetObjectLoadPtr()->GetColMap("Smith");

	// Background(¼ø¼­)
	CreateActor<Smith_Sky>();
	CreateActor<Smith_Sea>();
	CreateActor<Smith_Background>();

	// Map		
	CreateActor<Smith_Map>();
	CreateActor<Smith_ColMap>();

	// Monster

	// UI
	CreateActor<GemWindow>();
	CreateActor<Health>();

	// Player
	Shantae = CreateActor<Player>();
	SHA = dynamic_cast<Player*>(Shantae);

	SHA->SetColMap(ColMap);
	SHA->SetPos({ 155, 841 });
	Shantae->GetLevel()->SetCameraPos({ 150, 150 });
	SHA->CameraMoveSwitch();
	SHA->SetAnimationStart(false);
}

void Smith::Update(float _DeltaTime)
{
	OverlapTime += _DeltaTime;

	LevelSet();
	Debugging();

	if (SHA->GetPos().x <= 50.0f)
	{
		GameEngineCore::GetInst()->ChangeLevel("Scuttle");
	}
}

void Smith::LevelChangeStart(GameEngineLevel* _PrevLevel)
{
	SetPlayLevelHP(Player::MainPlayer->GetPlayerHP());
	SetPlayLevelMaxHP(Player::MainPlayer->GetPlayerMaxHP());
	SetPlayLevelGem(Player::MainPlayer->GetPlayerGem());
}

void Smith::LevelChangeEnd(GameEngineLevel* _NextLevel)
{
}

void Smith::LevelSet()
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
		if (300 <= SHA->GetPos().x)
		{
			SHA->SetStartAnimationStart(false);
			SHA->ChangeState(PlayerState::IDLE);
			AnimationSet = 0;
		}
	}
}

void Smith::Debugging()
{
	if (GameEngineInput::IsDown("ColMapSwitch"))
	{
		if (OverlapTime > 0.5f)
		{
			Smith_ColMap::ColMap->OnOffSwtich();
			OverlapTime = 0.0f;
		}
	}
	if (GameEngineInput::IsPress("BeforeLevel"))
	{
		if (OverlapTime > 0.5f)
		{
			GameEngineCore::GetInst()->ChangeLevel("Scuttle");
			OverlapTime = 0.0f;
		}
	}
	if (GameEngineInput::IsPress("NextLevel"))
	{
		if (OverlapTime > 0.5f)
		{
			GameEngineCore::GetInst()->ChangeLevel("SkyRoom");
			OverlapTime = 0.0f;
		}
	}
	if (GameEngineInput::IsDown("Back"))
	{
		GameEngineCore::GetInst()->ChangeLevel("SelectMeun");
	}
}