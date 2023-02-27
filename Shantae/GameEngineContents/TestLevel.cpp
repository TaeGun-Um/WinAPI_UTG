#include "TestLevel.h"

// GE
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineCore.h>
#include <GameEngineBase/GameEngineDirectory.h>
#include <GameEngineCore/GameEngineActor.h>
#include <GameEngineCore/GameEngineResources.h>

// Actor
#include "AnimationBox.h"
#include "TestMap.h"
#include "Player.h"
#include "Soldier_Blue.h"
#include "Soldier_Black.h"
#include "Soldier_Bomberman.h"
#include "Soldier_Red.h"
#include "Soldier_Boom.h"
#include "Public_Boom.h"
#include "Misillie.h"
#include "Bridge_Boom.h"
#include "MonsterSpawner.h"
#include "Machinegun_Plat.h"
#include "Ship.h"
#include "Wave.h"
#include "Building1.h"
#include "Building2.h"
#include "Sky.h"
#include "Sea.h"

#include "Town_Guard.h"
#include "Sailor.h"
#include "Boy.h"
#include "Girl.h"
#include "Jug_Woman.h"
#include "Stylist.h"
#include "Desert_Man.h"
#include "Mayor_Scuttlebutt.h"
#include "Dancer.h"
#include "Merchant.h"

#include "AnimationBox_Door.h"

#include "GemWindow.h"
#include "Health.h"
#include "BlackBox.h"
#include "WhiteBox.h"

#include "ContentsEnum.h"
#include "ObjectLoad.h"

TestLevel::TestLevel() 
{
}

TestLevel::~TestLevel() 
{
}

void TestLevel::Loading()
{
	ColMap = ObjectLoad::GetObjectLoadPtr()->GetColMap("Test");

	CreateActor<TestMap>();

	//AnimationBox_Door* Door = CreateActor<AnimationBox_Door>();
	//Door->SetPos({ 600, 675 });
	//Door->SetPortalValue(PortalType::TestRoom);

	//AnimationBox_Door* Door2 = CreateActor<AnimationBox_Door>();
	//Door2->SetPos({ 800, 675 });
	//Door2->SetPortalValue(PortalType::TestRoom2);

	CreateActor<GemWindow>();

	CreateActor<Health>();

	// NPC
	{
		//Boy* M3 = CreateActor<Boy>();
		//M3->SetPos({ 400, 900 });
		//M3->SetRun();

		//Girl* M4 = CreateActor<Girl>();
		//M4->SetPos({ 400, 900 });
		//M4->SetRun();

		//Jug_Woman* M5 = CreateActor<Jug_Woman>();
		//M5->SetPos({ 400, 900 });

		//Stylist* M6 = CreateActor<Stylist>();
		//M6->SetPos({ 400, 900 });

		Desert_Man* M7 = CreateActor<Desert_Man>();
		M7->SetPos({ 400, 900 });

		//Merchant* M7 = CreateActor<Merchant>();
		//M7->SetPos({ 400, 900 });
		//M7->SetRun();
		

	}


	//Soldier_Black* s = CreateActor<Soldier_Black>();
	//s->SetPos({ 500, 850 });
	//s->SetColMap(ColMap);

	//Soldier_Bomberman* s1 = CreateActor<Soldier_Bomberman>();
	//s1->SetPos({ 500, 850 });
	//s1->SetColMap(ColMap);

	Shantae = CreateActor<Player>();
	SHA = dynamic_cast<Player*>(Shantae);
	SHA->SetColMap(ColMap);
	SHA->SetPos({ 300, 850 });
	Shantae->GetLevel()->SetCameraPos({ -300, 200 });

	// 罚待备开 soldier 积己
	//srand(static_cast<unsigned int>(time(nullptr)));
	//for (size_t i = 0; i < 2; i++)
	//{
	//	Soldier* Actor = CreateActor<Soldier>(RenderOrder::Monster);
	//	Actor->SetMove(float4(static_cast<float>(rand() % GameEngineWindow::GetScreenSize().ix()), static_cast<float>(rand() % GameEngineWindow::GetScreenSize().iy())));
	//}

}

void TestLevel::Update(float _DeltaTime)
{
	LevelSet();
	Debugging();
	// Portal();

	// CameraAction();

}

void TestLevel::LevelChangeStart(GameEngineLevel* _PrevLevel)
{
	//BGMPlayer = GameEngineResources::GetInst().SoundPlayToControl("Sky.mp3");
	//BGMPlayer.Volume(0.1f);
	//BGMPlayer.LoopCount(10);
}

void TestLevel::LevelChangeEnd(GameEngineLevel* _NextLevel)
{
	//BGMPlayer.Stop();
	Set = 1;
}

void TestLevel::LevelSet()
{
	if (1 == Set)
	{
		Set = 0;

		Player::MainPlayer = SHA;
	}
}

void TestLevel::CameraAction()
{
	if (SHA->GetPos().x >= 4900.0f)
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
		Shantae->GetLevel()->SetCameraPos({ 0, 200 });
	}
}

void TestLevel::Debugging()
{
	if (GameEngineInput::IsDown("NextLevel"))
	{
		GameEngineCore::GetInst()->ChangeLevel("TestRoom");
	}

	if (GameEngineInput::IsDown("Back"))
	{
		GameEngineCore::GetInst()->ChangeLevel("SelectMeun");
	}
}

void TestLevel::Portal()
{
	//if (GameEngineInput::IsDown("UpMove"))
	//{
	//	if (600 <= SHA->GetPos().x && SHA->GetPos().x <= 750 && SHA->GetPos().y >= 690)
	//	{
	//		GameEngineCore::GetInst()->ChangeLevel("TestRoom");
	//	}

	//	if (800 <= SHA->GetPos().x && SHA->GetPos().x <= 950 && SHA->GetPos().y >= 690)
	//	{
	//		GameEngineCore::GetInst()->ChangeLevel("TestRoom2");
	//	}
	//}
}