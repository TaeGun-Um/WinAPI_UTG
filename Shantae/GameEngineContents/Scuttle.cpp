#include "Scuttle.h"

#include <GameEngineBase/GameEngineDirectory.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineResources.h>
#include <GameEngineCore/GameEngineRender.h>
#include <GameEngineCore/GameEngineCore.h>

#include "Scuttle_Background.h"
#include "Scuttle_ColMap.h"
#include "Scuttle_Map.h"
#include "Player.h"
#include "Sky.h"
#include "Sea.h"
#include "PortalDoor.h"

#include "GemWindow.h"
#include "Health.h"
#include "ObjectLoad.h"
#include "BlackBox.h"

GameEngineSoundPlayer Scuttle::ScuttleBGMPlayer = 0;

Scuttle::Scuttle()
{
}

Scuttle::~Scuttle()
{
}

void Scuttle::Loading()
{
	ColMap = ObjectLoad::GetObjectLoadPtr()->GetColMap("Scuttle");

	// Background(����)
	{
		Sky* Sk = CreateActor<Sky>();
		Sk->SetSkyYPos(50);
		Sk->SetSkySpeed(25.0f);
		Se = CreateActor<Sea>();
		Se->SetPos({ 1000, 700 });
		Se->SetCount();
	}

	CreateActor<Scuttle_Background>();

	// Map
	CreateActor<Scuttle_Map>();
	CreateActor<Scuttle_ColMap>();

	// Portal
	{
		PortalDoor* Door = CreateActor<PortalDoor>();
		Door->SetPos({ 2535.0f, 1100.0f });
		Door->SetPortalValue(PortalType::UncleRoom);

		PortalDoor* Door2 = CreateActor<PortalDoor>();
		Door2->SetPos({ 5340.0f, 1100.0f });
		Door2->SetPortalValue(PortalType::Shop);

		PortalDoor* Door3 = CreateActor<PortalDoor>();
		Door3->SetPos({ 4825.0f, 820.0f });
		Door3->SetPortalValue(PortalType::Spa);

		PortalDoor* Door4 = CreateActor<PortalDoor>();
		Door4->SetPos({ 4675.0f, 1100.0f });
		Door4->SetPortalValue(PortalType::Smith);

		PortalDoor* Door5 = CreateActor<PortalDoor>();
		Door5->SetPos({ 5340.0f, 540.0f });
		Door5->SetPortalValue(PortalType::SkyRoom);

		PortalDoor* Door6 = CreateActor<PortalDoor>();
		Door6->SetPos({ 6145.0f, 1100.0f });
		Door6->SetPortalValue(PortalType::SaveRoom);
	}

	// Player
	{
		Shantae = CreateActor<Player>();
		SHA = dynamic_cast<Player*>(Shantae);

		SHA->SetColMap(ColMap);
		SHA->SetPos({ 0, 1316 });
		Shantae->GetLevel()->SetCameraPos({ 0, 680 });
		SHA->SetAnimationStart(false);
		SHA->SetStartAnimationStart(false);

		// UI
		CreateActor<GemWindow>();
		CreateActor<Health>();
	}

}

// asdf
void Scuttle::Portal()
{

			GameEngineCore::GetInst()->ChangeLevel("UncleRoom");
			OverlapTime = 0.0f;
			ScuttleBGMPlayer.Stop();
			ScuttlePalyer = false;

			GameEngineCore::GetInst()->ChangeLevel("Smith");
			OverlapTime = 0.0f;
			ScuttleBGMPlayer.Stop();
			ScuttlePalyer = false;

			GameEngineCore::GetInst()->ChangeLevel("Shop");
			OverlapTime = 0.0f;
			ScuttleBGMPlayer.Stop();
			ScuttlePalyer = false;

			GameEngineCore::GetInst()->ChangeLevel("SaveRoom");
			OverlapTime = 0.0f;
			ScuttlePalyer = true;

			GameEngineCore::GetInst()->ChangeLevel("Spa");
			OverlapTime = 0.0f;
			ScuttlePalyer = true;

			GameEngineCore::GetInst()->ChangeLevel("SkyRoom");
			OverlapTime = 0.0f;
			ScuttleBGMPlayer.Stop();
			ScuttlePalyer = false;

}

void Scuttle::Update(float _DeltaTime)
{
	OverlapTime += _DeltaTime;

	BlackBoxOutAnimation();
	LevelSet();
	Debugging();
	CameraAction();

	if (SHA->GetPos().x >= 8355.0f)
	{
		GameEngineCore::GetInst()->ChangeLevel("Opening");
	}
}

void Scuttle::LevelChangeStart(GameEngineLevel* _PrevLevel)
{
	Set = 1;

	if (false == ScuttlePalyer)
	{
		ScuttleBGMPlayer = GameEngineResources::GetInst().SoundPlayToControl("Scuttle_Town.mp3");
		ScuttleBGMPlayer.Volume(0.0f);
		ScuttleBGMPlayer.LoopCount(100);
	}

	SetPlayLevelHP(Player::MainPlayer->GetPlayerHP());
	SetPlayLevelMaxHP(Player::MainPlayer->GetPlayerMaxHP());
	SetPlayLevelGem(Player::MainPlayer->GetPlayerGem());
}

void Scuttle::LevelChangeEnd(GameEngineLevel* _NextLevel)
{
	// InBoxKill();
}

void Scuttle::BlackBoxOutAnimation()
{
	if (1 == BBoxOutCount)
	{
		BBoxOutCount = 0;
		BBoxOut = CreateActor<BlackBox>();
		BBoxOut->FadeOutStart(2, 0.25f);
	}
}

void Scuttle::BlackBoxInAnimation()
{
	if (1 == BBoxInCount)
	{
		BBoxInCount = 0;
		BBoxIn = CreateActor<BlackBox>();
		BBoxIn->FadeInStart(2, 0.25f);
	}
}

void Scuttle::InBoxKill()
{
	if (nullptr != BBoxIn)
	{
		BBoxIn->Death();
		BBoxIn = nullptr;
		BBoxInCount = 1;
		BBoxOutCount = 1;
	}
}

void Scuttle::LevelSet()
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
		if (500 <= SHA->GetPos().x)
		{
			SHA->SetStartAnimationStart(false);
			SHA->ChangeState(PlayerState::IDLE);
			AnimationSet = 0;
		}
	}
}

void Scuttle::CameraAction()
{
	if (1200 >= SHA->GetPos().y)
	{
		YCamera = true;
	}
	else if (1200 < SHA->GetPos().y)
	{
		YCamera = false;
	}

	float x = SHA->GetPos().x - 620;
	float y = SHA->GetPos().y - 520;

	if (true == YCamera)
	{
		SHA->GetLevel()->SetCameraPos({ x, y });
	}

	if (SHA->GetPos().x >= 7715.0f)
	{
		SHA->CameraMoveFalse();
	}
	else if (SHA->GetPos().x >= 620.0f)
	{
		SHA->CameraMoveTrue();
	}
	else if (SHA->GetPos().x <= 620.0f)
	{
		SHA->CameraMoveFalse();
		Shantae->GetLevel()->SetCameraPos({ 0, 680 });
	}
}

void Scuttle::Debugging()
{
	if (GameEngineInput::IsDown("ColMapSwitch"))
	{
		if (OverlapTime > 0.5f)
		{
			Scuttle_ColMap::ColMap->OnOffSwtich();
			OverlapTime = 0.0f;
		}
	}
	if (GameEngineInput::IsDown("BeforeLevel"))
	{
		if (OverlapTime > 0.5f)
		{
			GameEngineCore::GetInst()->ChangeLevel("Boss");
			OverlapTime = 0.0f;
		}
	}
	if (GameEngineInput::IsDown("NextLevel"))
	{
		if (OverlapTime > 0.5f)
		{
			GameEngineCore::GetInst()->ChangeLevel("UncleRoom");
			OverlapTime = 0.0f;
			ScuttleBGMPlayer.Stop();
			ScuttlePalyer = false;
		}
	}
	if (GameEngineInput::IsDown("Back"))
	{
		GameEngineCore::GetInst()->ChangeLevel("SelectMeun");
	}
}