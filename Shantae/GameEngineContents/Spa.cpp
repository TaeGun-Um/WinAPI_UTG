#include "Spa.h"

#include <GameEngineBase/GameEngineDirectory.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineResources.h>
#include <GameEngineCore/GameEngineRender.h>
#include <GameEngineCore/GameEngineCore.h>

#include "Spa_Background.h"
#include "Spa_ColMap.h"
#include "Spa_Map.h"
#include "Spa_Sky.h"
#include "Player.h"
#include "Sea.h"

#include "GemWindow.h"
#include "Health.h"
#include "ObjectLoad.h"
#include "BlackBox.h"

Spa::Spa() 
{
}

Spa::~Spa() 
{
}

void Spa::Loading()
{
	ColMap = ObjectLoad::GetObjectLoadPtr()->GetColMap("Spa");

	// Background(순서)
	CreateActor<Spa_Sky>();
	CreateActor<Sea>();
	CreateActor<Spa_Background>();

	// Map		
	CreateActor<Spa_Map>();
	CreateActor<Spa_ColMap>();

	// Monster

	// UI
	CreateActor<GemWindow>();
	CreateActor<Health>();

	// Player
	Shantae = CreateActor<Player>();
	SHA = dynamic_cast<Player*>(Shantae);

	SHA->SetColMap(ColMap);
	SHA->SetPos({ 50, 747 });
	Shantae->GetLevel()->SetCameraPos({ 60, 100 });
	SHA->CameraMoveSwitch();
	SHA->SetAnimationStart(false);
}

void Spa::Update(float _DeltaTime)
{
	OverlapTime += _DeltaTime;

	BlackBoxOutAnimation();
	LevelSet();
	Debugging();

	// 레벨 이동
	if (SHA->GetPos().x <= 40.0f)
	{
		GameEngineCore::GetInst()->ChangeLevel("Scuttle");
	}
}

void Spa::LevelChangeStart(GameEngineLevel* _PrevLevel)
{
	SetPlayLevelHP(Player::MainPlayer->GetPlayerHP());
	SetPlayLevelMaxHP(Player::MainPlayer->GetPlayerMaxHP());
	SetPlayLevelGem(Player::MainPlayer->GetPlayerGem());
}

void Spa::LevelChangeEnd(GameEngineLevel* _NextLevel)
{
	// InBoxKill();
}

void Spa::BlackBoxOutAnimation()
{
	if (1 == BBoxOutCount)
	{
		BBoxOutCount = 0;
		BBoxOut = CreateActor<BlackBox>();
		BBoxOut->FadeOutStart(2, 0);
	}
}

void Spa::BlackBoxInAnimation()
{
	if (1 == BBoxInCount)
	{
		BBoxInCount = 0;
		BBoxIn = CreateActor<BlackBox>();
		BBoxIn->FadeInStart(2, 0.5f);
	}
}

void Spa::InBoxKill()
{
	if (nullptr != BBoxIn)
	{
		BBoxIn->Death();
		BBoxIn = nullptr;
		BBoxInCount = 1;
		BBoxOutCount = 1;
	}
}

void Spa::LevelSet()
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
		if (190 <= SHA->GetPos().x)
		{
			SHA->SetStartAnimationStart(false);
			SHA->ChangeState(PlayerState::IDLE);
			AnimationSet = 0;
		}
	}
}

void Spa::Debugging()
{
	if (GameEngineInput::IsDown("ColMapSwitch"))
	{
		if (OverlapTime > 0.5f)
		{
			Spa_ColMap::ColMap->OnOffSwtich();
			OverlapTime = 0.0f;
		}
	}
	if (GameEngineInput::IsDown("BeforeLevel"))
	{
		if (OverlapTime > 0.5f)
		{
			GameEngineCore::GetInst()->ChangeLevel("Scuttle");
			OverlapTime = 0.0f;
		}
	}
	if (GameEngineInput::IsDown("NextLevel"))
	{
		if (OverlapTime > 0.5f)
		{
			GameEngineCore::GetInst()->ChangeLevel("Smith");
			OverlapTime = 0.0f;
		}
	}
	if (GameEngineInput::IsDown("Back"))
	{
		GameEngineCore::GetInst()->ChangeLevel("SelectMeun");
	}
}