#include "Scuttle.h"

#include <GameEngineBase/GameEngineDirectory.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineResources.h>
#include <GameEngineCore/GameEngineRender.h>
#include <GameEngineCore/GameEngineCore.h>

#include "Scuttle_Background.h"
#include "Scuttle_ColMap.h"
#include "Scuttle_Map.h"
#include "Scuttle_Sky.h"
#include "Player.h"
#include "Sea.h"

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

	// Background(순서)
	CreateActor<Scuttle_Sky>();
	CreateActor<Sea>();
	CreateActor<Scuttle_Background>();

	// Map
	CreateActor<Scuttle_Map>();
	CreateActor<Scuttle_ColMap>();

	// Monster

	// UI
	CreateActor<GemWindow>();
	CreateActor<Health>();

	// Player
	Shantae = CreateActor<Player>();
	SHA = dynamic_cast<Player*>(Shantae);

	SHA->SetColMap(ColMap);
	SHA->SetPos({ 0, 1316 });
	Shantae->GetLevel()->SetCameraPos({ 0, 680 });
	SHA->SetAnimationStart(false);
	SHA->SetStartAnimationStart(false);
}

void Scuttle::Update(float _DeltaTime)
{
	OverlapTime += _DeltaTime;

	BlackBoxOutAnimation();
	LevelSet();
	Debugging();
	CameraAction();

	// 레벨 이동
	Portal();

	if (SHA->GetPos().x >= 8355.0f)
	{
		GameEngineCore::GetInst()->ChangeLevel("Opening");
	}
}

void Scuttle::LevelChangeStart(GameEngineLevel* _PrevLevel)
{
	if (false == ScuttlePalyer)
	{
		ScuttleBGMPlayer = GameEngineResources::GetInst().SoundPlayToControl("Scuttle_Town.mp3");
		ScuttleBGMPlayer.Volume(0.1f);
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

void Scuttle::Portal()
{
	if (GameEngineInput::IsPress("UpMove"))
	{
		if (2545.0f <= SHA->GetPos().x && SHA->GetPos().x <= 2680.0f && SHA->GetPos().y >= 1175.0f)
		{
			GameEngineCore::GetInst()->ChangeLevel("UncleRoom");
			OverlapTime = 0.0f;
			ScuttleBGMPlayer.Stop();
			ScuttlePalyer = false;
		}
		if (4705.0f <= SHA->GetPos().x && SHA->GetPos().x <= 4795.0f && SHA->GetPos().y >= 1175.0f)
		{
			GameEngineCore::GetInst()->ChangeLevel("Smith");
			OverlapTime = 0.0f;
			ScuttleBGMPlayer.Stop();
			ScuttlePalyer = false;
		}
		if (5330.0f <= SHA->GetPos().x && SHA->GetPos().x <= 5495.0f && SHA->GetPos().y >= 1175.0f)
		{
			GameEngineCore::GetInst()->ChangeLevel("Shop");
			OverlapTime = 0.0f;
			ScuttleBGMPlayer.Stop();
			ScuttlePalyer = false;
		}
		if (6160.0f <= SHA->GetPos().x && SHA->GetPos().x <= 6280.0f && SHA->GetPos().y >= 1175.0f)
		{
			GameEngineCore::GetInst()->ChangeLevel("SaveRoom");
			OverlapTime = 0.0f;
			ScuttlePalyer = true;
		}
		if (4840.0f <= SHA->GetPos().x && SHA->GetPos().x <= 4960.0f && SHA->GetPos().y <= 1175.0f)
		{
			GameEngineCore::GetInst()->ChangeLevel("Spa");
			OverlapTime = 0.0f;
			ScuttlePalyer = true;
		}
		if (5330.0f <= SHA->GetPos().x && SHA->GetPos().x <= 5495.0f && SHA->GetPos().y <= 1175.0f)
		{
			GameEngineCore::GetInst()->ChangeLevel("SkyRoom");
			OverlapTime = 0.0f;
			ScuttleBGMPlayer.Stop();
			ScuttlePalyer = false;
		}
	}
}