#include "Machinegun.h"

#include <GameEngineBase/GameEngineDirectory.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineResources.h>
#include <GameEngineCore/GameEngineRender.h>
#include <GameEngineCore/GameEngineCore.h>

#include "Machinegun_Background.h"
#include "Machinegun_ColMap.h"
#include "Machinegun_Map.h"
#include "Sky.h"

#include "Player.h"
#include "Machinegun_Plat.h"
#include "Soldier_Machinegun.h"

#include "GemWindow.h"
#include "Health.h"
#include "ObjectLoad.h"
#include "BlackBox.h"

Machinegun::Machinegun() 
{
}

Machinegun::~Machinegun() 
{
}

void Machinegun::Loading()
{
	ColMap = ObjectLoad::GetObjectLoadPtr()->GetColMap("Machinegun");

	// Background(순서)
	CreateActor<Sky>();
	CreateActor<Machinegun_Background>();

	// Map
	CreateActor<Machinegun_Map>();
	CreateActor<Machinegun_ColMap>();

	Machinegun_Plat* Plat1 = CreateActor<Machinegun_Plat>();
	Plat1->SetPos({ 1605, 630 });
	Machinegun_Plat* Plat2 = CreateActor<Machinegun_Plat>();
	Plat2->SetPos({ 1705, 630 });
	Machinegun_Plat* Plat33 = CreateActor<Machinegun_Plat>();
	Plat33->SetPos({ 1805, 630 });
	Machinegun_Plat* Plat44 = CreateActor<Machinegun_Plat>();
	Plat44->SetPos({ 1905, 630 });
	Machinegun_Plat* Plat3 = CreateActor<Machinegun_Plat>();
	Plat3->SetPos({ 2620, 475 });
	Machinegun_Plat* Plat4 = CreateActor<Machinegun_Plat>();
	Plat4->SetPos({ 2850, 475 });
	Machinegun_Plat* Plat5 = CreateActor<Machinegun_Plat>();
	Plat5->SetPos({ 3100, 590 });
	Machinegun_Plat* Plat6 = CreateActor<Machinegun_Plat>();
	Plat6->SetPos({ 4360, 580 });
	Machinegun_Plat* Plat7 = CreateActor<Machinegun_Plat>();
	Plat7->SetPos({ 4460, 580 });
	Machinegun_Plat* Plat8 = CreateActor<Machinegun_Plat>();
	Plat8->SetPos({ 4700, 430 });
	Machinegun_Plat* Plat9 = CreateActor<Machinegun_Plat>();
	Plat9->SetPos({ 4800, 430 });
	Machinegun_Plat* Plat10 = CreateActor<Machinegun_Plat>();
	Plat10->SetPos({ 5652.5f, 390 });
	Machinegun_Plat* Plat11 = CreateActor<Machinegun_Plat>();
	Plat11->SetPos({ 5752.5f, 390 });
	Machinegun_Plat* Plat12 = CreateActor<Machinegun_Plat>();
	Plat12->SetPos({ 6425, 735 });
	Machinegun_Plat* Plat13 = CreateActor<Machinegun_Plat>();
	Plat13->SetPos({ 6595, 590 });
	Machinegun_Plat* Plat14 = CreateActor<Machinegun_Plat>();
	Plat14->SetPos({ 9278, 550 });
	Machinegun_Plat* Plat15 = CreateActor<Machinegun_Plat>();
	Plat15->SetPos({ 9765, 590 });
	Machinegun_Plat* Plat16 = CreateActor<Machinegun_Plat>();
	Plat16->SetPos({ 10505, 590 });
	Machinegun_Plat* Plat17 = CreateActor<Machinegun_Plat>();
	Plat17->SetPos({ 10605, 590 });
	Machinegun_Plat* Plat18 = CreateActor<Machinegun_Plat>();
	Plat18->SetPos({ 10905, 590 });
	Machinegun_Plat* Plat19 = CreateActor<Machinegun_Plat>();
	Plat19->SetPos({ 11005, 590 });

	// Monster
	// 스포너사용법   스포너 위치    몹이름    콜맵    몹 젠 위치   리젠시간
	// CreateSpawner({ 250, 300 }, "blue", ColMap, { 350, 590 }, 5);

	Soldier_Machinegun* Ma1 = CreateActor<Soldier_Machinegun>();
	Ma1->SetPos({ 790, 362 });

	Soldier_Machinegun* Ma2 = CreateActor<Soldier_Machinegun>();
	Ma2->SetPos({ 3748, 362 });

	Soldier_Machinegun* Ma3 = CreateActor<Soldier_Machinegun>();
	Ma3->SetPos({ 7467, 362 });

	Soldier_Machinegun* Ma4 = CreateActor<Soldier_Machinegun>();
	Ma4->SetPos({ 8471, 364 });

	// UI
	CreateActor<GemWindow>();
	CreateActor<Health>();

	// Player
	Shantae = CreateActor<Player>();
	SHA = dynamic_cast<Player*>(Shantae);

	SHA->SetColMap(ColMap);
	SHA->SetPos({ 45, 563 }); // 45, 563
	Shantae->GetLevel()->SetCameraPos({ 55, 120 }); // 55, 120
	SHA->SetAnimationStart(false);
	SHA->SetStartAnimationStart(false);
}

void Machinegun::Update(float _DeltaTime)
{
	OverlapTime += _DeltaTime;
	
	BlackBoxOutAnimation();
	LevelSet();
	Debugging();
	CameraAction();

	// 레벨 이동
	if (SHA->GetPos().x >= 11930.0f
		&& PlayerState::MOVE == SHA->GetShantaeState())
	{
		BlackBoxInAnimation();
		SHA->SetAnimationStart(true);
		SHA->SetMoveSpeed(100.0f);
		if (true == SHA->LevelChangeAnimation(_DeltaTime))
		{
			GameEngineCore::GetInst()->ChangeLevel("BoomBridge");
		}
	}
}

void Machinegun::LevelChangeStart(GameEngineLevel* _PrevLevel)
{
	SetPlayLevelHP(Player::MainPlayer->GetPlayerHP());
	SetPlayLevelMaxHP(Player::MainPlayer->GetPlayerMaxHP());
	SetPlayLevelGem(Player::MainPlayer->GetPlayerGem());
}

void Machinegun::LevelChangeEnd(GameEngineLevel* _NextLevel)
{
	InBoxKill();
}

void Machinegun::BlackBoxOutAnimation()
{
	if (1 == BBoxOutCount)
	{
		BBoxOutCount = 0;
		BBoxOut = CreateActor<BlackBox>();
		BBoxOut->FadeOutStart(2, 0.01f);
	}
}

void Machinegun::BlackBoxInAnimation()
{
	if (1 == BBoxInCount)
	{
		BBoxInCount = 0;
		BBoxIn = CreateActor<BlackBox>();
		BBoxIn->FadeInStart(2, 0.1f);
	}
}

void Machinegun::InBoxKill()
{
	if (nullptr != BBoxIn)
	{
		BBoxIn->Death();
		BBoxIn = nullptr;
		BBoxInCount = 1;
		BBoxOutCount = 1;
	}
}

void Machinegun::LevelSet()
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
		if (200 <= SHA->GetPos().x)
		{
			SHA->SetStartAnimationStart(false);
			SHA->ChangeState(PlayerState::IDLE);
			AnimationSet = 0;
		}
	}
}

void Machinegun::CameraAction()
{
	if (SHA->GetPos().x >= 11250.0f)
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
		Shantae->GetLevel()->SetCameraPos({ 55, 120 });
	}
}

void Machinegun::Debugging()
{
	if (GameEngineInput::IsDown("ColMapSwitch"))
	{
		if (OverlapTime > 0.5f)
		{
			Machinegun_ColMap::ColMap->OnOffSwtich();
			OverlapTime = 0.0f;
		}
	}
	if (GameEngineInput::IsDown("BeforeLevel"))
	{
		if (OverlapTime > 0.5f)
		{
			GameEngineCore::GetInst()->ChangeLevel("Stair");
			OverlapTime = 0.0f;
		}
	}
	if (GameEngineInput::IsDown("NextLevel"))
	{
		if (OverlapTime > 0.5f)
		{
			GameEngineCore::GetInst()->ChangeLevel("BoomBridge");
			OverlapTime = 0.0f;
		}
	}
	if (GameEngineInput::IsDown("Back"))
	{
		GameEngineCore::GetInst()->ChangeLevel("SelectMeun");
	}
}