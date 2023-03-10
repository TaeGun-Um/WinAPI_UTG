#include "BoomBridge.h"

#include <GameEngineBase/GameEngineDirectory.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineResources.h>
#include <GameEngineCore/GameEngineRender.h>
#include <GameEngineCore/GameEngineCore.h>

#include "BoomBridge_Background.h"
#include "BoomBridge_Map.h"
#include "BoomBridge_ColMap.h"
#include "BoomBridge_Bridge1.h"
#include "BoomBridge_Bridge2.h"
#include "BoomBridge_Bridge3.h"
#include "Bridge_Boom.h"
#include "Sky.h"
#include "TimerCollision.h"

#include "Jar_Big.h"

#include "Soldier_Spider.h"
#include "Soldier_Pile.h"
#include "Player.h"
#include "GemWindow.h"
#include "Health.h"
#include "Inventory.h"

#include "ObjectLoad.h"
#include "BlackBox.h"

BoomBridge::BoomBridge() 
{
}

BoomBridge::~BoomBridge() 
{
}

void BoomBridge::Loading()
{
	ColMap = ObjectLoad::GetObjectLoadPtr()->GetColMap("BoomBridge");

	// Background(순서)
	{
		Sky* Sk = CreateActor<Sky>();
		Sk->SetSkyYPos(300);
		Sk->SetSkySpeed(25.0f);
	}
	
	CreateActor<BoomBridge_Background>();

	// Map
	CreateActor<BoomBridge_Map>();
	CreateActor<BoomBridge_ColMap>();

	// Item
	{
		Jar_Big* jB = CreateActor<Jar_Big>();
		jB->SetPos({ 1450, 6510 });
		jB->SetColMap(ColMap);
	}

	// Monster
	{
		CreateActor<Soldier_Pile>();
		Set_One();
		Set_Two();
		Set_Three();
		Set_Four();
	}

	// Player
	{
		Shantae = CreateActor<Player>();
		SHA = dynamic_cast<Player*>(Shantae);

		SHA->SetColMap(ColMap);
		SHA->SetPos({ 426, 647 });
		Shantae->GetLevel()->SetCameraPos({ 430, 220 });
		SHA->CameraMoveSwitch();
		SHA->SetAnimationStart(false);
		SHA->SetStartAnimationStart(false);

		// UI
		CreateActor<GemWindow>();
		CreateActor<Health>();
		Inven = CreateActor<Inventory>();
	}
}

bool ch = true;

void BoomBridge::Update(float _DeltaTime)
{
	OverlapTime += _DeltaTime;

	BlackBoxOutAnimation();
	LevelSet();
	Debugging();
	CameraAction();

	// 타이머 시작
	TimerStart();

	// 레벨 이동
	if (SHA->GetPos().x >= 1660.0f
		&& PlayerState::MOVE == SHA->GetShantaeState())
	{
		BlackBoxInAnimation();
		SHA->SetAnimationStart(true);
		SHA->SetMoveSpeed(100.0f);
		if (true == SHA->LevelChangeAnimation(_DeltaTime))
		{
			GameEngineCore::GetInst()->ChangeLevel("BeforeBoss");
		}
	}
}

void BoomBridge::LevelChangeStart(GameEngineLevel* _PrevLevel)
{
	Inventory::PlayerInven->DataCopy(Inven);
	Inventory::PlayerInven = Inven;

	SetPlayLevelHP(Player::MainPlayer->GetPlayerHP());
	SetPlayLevelMaxHP(Player::MainPlayer->GetPlayerMaxHP());
	SetPlayLevelGem(Player::MainPlayer->GetPlayerGem());
	SetPlayNewMaxHP(Player::MainPlayer->GetNewMaxHP());
	SetPlayLevelMonsterMilk(Player::MainPlayer->GetPlayerMonsterMilk());
	SetPlayLevelPikeBall(Player::MainPlayer->GetPlayerPikeBall());
	SetPlayLevelBubble(Player::MainPlayer->GetPlayerBubble());
	SetPlayLevelOctopus(Player::MainPlayer->GetPlayerOctopus());
	SetPlayLevelMeat(Player::MainPlayer->GetPlayerMeat());
	SetPlayLevelIDCard(Player::MainPlayer->GetPlayerIDCard());
}

void BoomBridge::LevelChangeEnd(GameEngineLevel* _NextLevel)
{
	InBoxKill();
}

void BoomBridge::BlackBoxOutAnimation()
{
	if (1 == BBoxOutCount)
	{
		BBoxOutCount = 0;
		BBoxOut = CreateActor<BlackBox>();
		BBoxOut->FadeOutStart(2, 0);
	}
}

void BoomBridge::BlackBoxInAnimation()
{
	if (1 == BBoxInCount)
	{
		BBoxInCount = 0;
		BBoxIn = CreateActor<BlackBox>();
		BBoxIn->FadeInStart(2, 0.1f);
	}
}

void BoomBridge::InBoxKill()
{
	if (nullptr != BBoxIn)
	{
		BBoxIn->Death();
		BBoxIn = nullptr;
		BBoxInCount = 1;
		BBoxOutCount = 1;
	}
}

void BoomBridge::LevelSet()
{
	if (1 == Set)
	{
		Set = 0;
		Player::MainPlayer = SHA;
		Player::MainPlayer->SetPlayerHP(GetPlayLevelHP());
		Player::MainPlayer->SetPlayerMaxHP(GetPlayLevelMaxHP());
		Player::MainPlayer->SetPlayerGem(GetPlayLevelGem());
		Player::MainPlayer->SetNewMaxHP(GetPlayNewMaxHP());
		Player::MainPlayer->SetPlayerMonsterMilk(GetPlayLevelMonsterMilk());
		Player::MainPlayer->SetPlayerPikeBall(GetPlayLevelPikeBall());
		Player::MainPlayer->SetPlayerBubble(GetPlayLevelBubble());
		Player::MainPlayer->SetPlayerOctopus(GetPlayLevelOctopus());
		Player::MainPlayer->SetPlayerMeat(GetPlayLevelMeat());
		Player::MainPlayer->SetPlayerIDCard(GetPlayLevelIDCard());
	}
	if (1 == AnimationSet)
	{
		SHA->SetStartAnimationStart(true);
		if (495 <= SHA->GetPos().x)
		{
			SHA->SetStartAnimationStart(false);
			SHA->ChangeState(PlayerState::IDLE);
			AnimationSet = 0;
		}
	}
}

void BoomBridge::CameraAction()
{
	if (6345 <= SHA->GetPos().y)
	{
		YCamera = false;
		ch = false;
	}
	if (650 <= SHA->GetPos().y && true == ch)
	{
		YCamera = true;
	}
	else
	{
		YCamera = false;
	}

	if (true == YCamera)
	{
		float y = SHA->GetPos().y - 430;
		SHA->GetLevel()->SetCameraPos({ 430, y });
	}
}

void BoomBridge::Debugging()
{
	if (GameEngineInput::IsDown("ColMapSwitch"))
	{
		if (OverlapTime > 0.5f)
		{
			BoomBridge_ColMap::ColMap->OnOffSwtich();
			OverlapTime = 0.0f;
		}
	}
	if (GameEngineInput::IsDown("BeforeLevel"))
	{
		if (OverlapTime > 0.5f)
		{
			GameEngineCore::GetInst()->ChangeLevel("Machinegun");
			OverlapTime = 0.0f;
		}
	}
	if (GameEngineInput::IsDown("NextLevel"))
	{
		if (OverlapTime > 0.5f)
		{
			GameEngineCore::GetInst()->ChangeLevel("BeforeBoss");
			OverlapTime = 0.0f;
		}
	}
	if (GameEngineInput::IsDown("Back"))
	{
		GameEngineCore::GetInst()->ChangeLevel("SelectMeun");
	}
}

void BoomBridge::TimerStart()
{
	if (0 == TimerCol1->GetTimerSet())
	{
		SetTimerRenewal_One(TimerCol1->GetAccTime());
	}
	if (0 == TimerCol2->GetTimerSet())
	{
		SetTimerRenewal_Two(TimerCol2->GetAccTime());
	}
	if (0 == TimerCol3->GetTimerSet())
	{
		SetTimerRenewal_Three(TimerCol3->GetAccTime());
	}
	if (0 == TimerCol4->GetTimerSet())
	{
		SetTimerRenewal_Four(TimerCol4->GetAccTime());
	}
}

void BoomBridge::Set_One()
{
	TimerCol1 = CreateActor<TimerCollision>();
	TimerCol1 = TimerCollision::GetTimer();
	TimerCol1->SetPos({ 1200, 550 });

	Plat1 = CreateActor<BoomBridge_Bridge1>();
	Plat1->SetPos({ 727.5f, 672.5f });
	Plat2 = CreateActor<BoomBridge_Bridge2>();
	Plat2->SetPos({ 1077.5f, 672.5f });
	Plat3 = CreateActor<BoomBridge_Bridge3>();
	Plat3->SetPos({ 1427.5f, 672.5f });

	Boom1 = CreateActor<Bridge_Boom>();
	Boom1->SetPos({ 610, 675 });
	Boom1->SetSoundOff();
	Boom1->SetDirect(false);
	Boom2 = CreateActor<Bridge_Boom>();
	Boom2->SetPos({ 1545, 675 });

	Soldier1 = CreateActor<Soldier_Spider>();
	Soldier1->SetPos({ 1077.5f, 683 });
	Soldier1->SetColMap(ColMap);
}

void BoomBridge::SetTimerRenewal_One(float _Time)
{
	Plat1->SetAccTime(_Time);
	Plat2->SetAccTime(_Time);
	Plat3->SetAccTime(_Time);

	Boom1->SetAccTime(_Time);
	Boom2->SetAccTime(_Time);

	Soldier1->SetAccTime(_Time);
}

void BoomBridge::Set_Two()
{
	TimerCol2 = CreateActor<TimerCollision>();
	TimerCol2 = TimerCollision::GetTimer();
	TimerCol2->SetPos({ 1070, 2170 });

	Plat4 = CreateActor<BoomBridge_Bridge1>();
	Plat4->SetPos({ 727.5f, 2292.5f });
	Plat5 = CreateActor<BoomBridge_Bridge2>();
	Plat5->SetPos({ 1077.5f, 2292.5f });
	Plat6 = CreateActor<BoomBridge_Bridge3>();
	Plat6->SetPos({ 1427.5f, 2292.5f });

	Boom3 = CreateActor<Bridge_Boom>();
	Boom3->SetPos({ 610, 2295 });
	Boom3->SetSoundOff();
	Boom3->SetDirect(false);
	Boom4 = CreateActor<Bridge_Boom>();
	Boom4->SetPos({ 1545, 2295 });

	Soldier2 = CreateActor<Soldier_Spider>();
	Soldier2->SetPos({ 900, 2303 });
	Soldier2->SetColMap(ColMap);
	Soldier3 = CreateActor<Soldier_Spider>();
	Soldier3->SetPos({ 1300, 2303 });
	Soldier3->SetColMap(ColMap);
}

void BoomBridge::SetTimerRenewal_Two(float _Time)
{
	Plat4->SetAccTime(_Time);
	Plat5->SetAccTime(_Time);
	Plat6->SetAccTime(_Time);

	Boom3->SetAccTime(_Time);
	Boom4->SetAccTime(_Time);

	Soldier2->SetAccTime(_Time);
	Soldier3->SetAccTime(_Time);
}

void BoomBridge::Set_Three()
{
	TimerCol3 = CreateActor<TimerCollision>();
	TimerCol3 = TimerCollision::GetTimer();
	TimerCol3->SetPos({ 1070, 3590 });

	Plat7 = CreateActor<BoomBridge_Bridge1>();
	Plat7->SetPos({ 727.5f, 3712.5f });
	Plat8 = CreateActor<BoomBridge_Bridge2>();
	Plat8->SetPos({ 1077.5f, 3712.5f });
	Plat9 = CreateActor<BoomBridge_Bridge3>();
	Plat9->SetPos({ 1427.5f, 3712.5f });

	Boom5 = CreateActor<Bridge_Boom>();
	Boom5->SetPos({ 610, 3715 });
	Boom5->SetSoundOff();
	Boom5->SetDirect(false);
	Boom6 = CreateActor<Bridge_Boom>();
	Boom6->SetPos({ 1545, 3715 });

	Soldier4 = CreateActor<Soldier_Spider>();
	Soldier4->SetPos({ 800, 3723 });
	Soldier4->SetColMap(ColMap);
	Soldier4->SetDir("_R");
	Soldier5 = CreateActor<Soldier_Spider>();
	Soldier5->SetPos({ 1100, 3723 });
	Soldier5->SetColMap(ColMap);
	Soldier6 = CreateActor<Soldier_Spider>();
	Soldier6->SetPos({ 1400, 3723 });
	Soldier6->SetColMap(ColMap);
}

void BoomBridge::SetTimerRenewal_Three(float _Time)
{
	Plat7->SetAccTime(_Time);
	Plat8->SetAccTime(_Time);
	Plat9->SetAccTime(_Time);

	Boom5->SetAccTime(_Time);
	Boom6->SetAccTime(_Time);

	Soldier4->SetAccTime(_Time);
	Soldier5->SetAccTime(_Time);
	Soldier6->SetAccTime(_Time);
}


void BoomBridge::Set_Four()
{
	TimerCol4 = CreateActor<TimerCollision>();
	TimerCol4 = TimerCollision::GetTimer();
	TimerCol4->SetPos({ 1070, 5010 });

	Plat10 = CreateActor<BoomBridge_Bridge1>();
	Plat10->SetPos({ 727.5f, 5132.5f });
	Plat11 = CreateActor<BoomBridge_Bridge2>();
	Plat11->SetPos({ 1077.5f, 5132.5f });
	Plat12 = CreateActor<BoomBridge_Bridge3>();
	Plat12->SetPos({ 1427.5f, 5132.5f });

	Boom7 = CreateActor<Bridge_Boom>();
	Boom7->SetPos({ 610, 5135 });
	Boom7->SetSoundOff();
	Boom7->SetDirect(false);
	Boom8 = CreateActor<Bridge_Boom>();
	Boom8->SetPos({ 1545, 5135 });

	Soldier7 = CreateActor<Soldier_Spider>();
	Soldier7->SetPos({ 700, 5140 });
	Soldier7->SetColMap(ColMap);
	Soldier7->SetDir("_R");
	Soldier8 = CreateActor<Soldier_Spider>();
	Soldier8->SetPos({ 950, 5143 });
	Soldier8->SetColMap(ColMap);
	Soldier8->SetDir("_R");
	Soldier9 = CreateActor<Soldier_Spider>();
	Soldier9->SetPos({ 1200, 5143 });
	Soldier9->SetColMap(ColMap);
	Soldier10 = CreateActor<Soldier_Spider>();
	Soldier10->SetPos({ 1400, 5143 });
	Soldier10->SetColMap(ColMap);
}

void BoomBridge::SetTimerRenewal_Four(float _Time)
{
	Plat10->SetAccTime(_Time);
	Plat11->SetAccTime(_Time);
	Plat12->SetAccTime(_Time);

	Boom7->SetAccTime(_Time);
	Boom8->SetAccTime(_Time);

	Soldier7->SetAccTime(_Time);
	Soldier8->SetAccTime(_Time);
	Soldier9->SetAccTime(_Time);
	Soldier10->SetAccTime(_Time);
}