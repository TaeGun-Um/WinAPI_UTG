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
#include "BlackBox.h"
#include "WhiteBox.h"

Boss::Boss() 
{
}

Boss::~Boss() 
{
}

void Boss::Loading()
{
	ColMap = ObjectLoad::GetObjectLoadPtr()->GetColMap("Boss");

	// Background(순서)
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

	// UI
	CreateActor<GemWindow>();
	CreateActor<Health>();

	// Player
	Shantae = CreateActor<Player>();
	SHA = dynamic_cast<Player*>(Shantae);

	SHA->SetColMap(ColMap);
	SHA->SetPos({ 131, 734 });
	Shantae->GetLevel()->SetCameraPos({ 125, 130 });
	SHA->CameraMoveSwitch();
	SHA->SetAnimationStart(false);
	SHA->SetStartAnimationStart(false);
}

void Boss::Update(float _DeltaTime)
{
	OverlapTime += _DeltaTime;

	LevelSet();
	Debugging();
	CameraAction();

	// 레벨 이동
	if (SHA->GetPos().x >= 1530.0f
		&& PlayerState::MOVE == SHA->GetShantaeState())
	{
		SHA->SetAnimationStart(true);
		SHA->SetMoveSpeed(100.0f);
		if (true == SHA->LevelChangeAnimation(_DeltaTime))
		{
			GameEngineCore::GetInst()->ChangeLevel("Scuttle");
		}
	}
}

void Boss::LevelChangeStart(GameEngineLevel* _PrevLevel)
{
	BGMPlayer = GameEngineResources::GetInst().SoundPlayToControl("Boss_Battle.mp3");
	BGMPlayer.Volume(0.05f);
	BGMPlayer.LoopCount(100);

	SetPlayLevelHP(Player::MainPlayer->GetPlayerHP());
	SetPlayLevelMaxHP(Player::MainPlayer->GetPlayerMaxHP());
	SetPlayLevelGem(Player::MainPlayer->GetPlayerGem());
}

void Boss::LevelChangeEnd(GameEngineLevel* _NextLevel)
{
	BGMPlayer.Stop();
}

void Boss::LevelSet()
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
		if (255 <= SHA->GetPos().x)
		{
			SHA->SetStartAnimationStart(false);
			SHA->ChangeState(PlayerState::IDLE);
			AnimationSet = 0;
		}
	}
}

void Boss::BlackBoxOutAnimation()
{
	if (1 == BBoxOutCount)
	{
		BBoxOutCount = 0;
		BBoxOut = CreateActor<BlackBox>();
		BBoxOut->FadeOutStart(0, 0.5f);
	}
}

void Boss::BlackBoxInAnimation()
{
	if (1 == BBoxInCount)
	{
		BBoxInCount = 0;
		BBoxIn = CreateActor<BlackBox>();
		BBoxIn->FadeInStart(0, 0.5f);
	}
}

void Boss::InBoxKill()
{
	if (nullptr != BBoxIn)
	{
		BBoxIn->Death();
		BBoxIn = nullptr;
		BBoxInCount = 1;
		BBoxOutCount = 1;
	}
}

void Boss::CameraAction()
{
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
}

void Boss::Debugging()
{
	if (GameEngineInput::IsDown("ColMapSwitch"))
	{
		if (OverlapTime > 0.5f)
		{
			Boss_ColMap::ColMap->OnOffSwtich();
			OverlapTime = 0.0f;
		}
	}
	if (GameEngineInput::IsDown("BeforeLevel"))
	{
		if (OverlapTime > 0.5f)
		{
			GameEngineCore::GetInst()->ChangeLevel("BeforeBoss");
			OverlapTime = 0.0f;
		}
	}
	if (GameEngineInput::IsDown("NextLevel"))
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
}