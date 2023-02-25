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

	// CreateActor<AnimationBox>();

	CreateActor<TestMap>();

	//GameEngineActor* A1 = CreateActor<Ship>();
	//A1->SetPos({ 500, 300 });

	//GameEngineActor* A1 = CreateActor<Sea>();
	//A1->SetPos({ 1000, 300 });

	//Building1* A3 = CreateActor<Building1>();
	//A3->SetPos({ 800, 300 });
	//A3->SetLeftBreak();

	GameEngineActor* A4 = CreateActor<Building2>();
	A4->SetPos({ 800, 300 });

	CreateActor<GemWindow>();

	CreateActor<Health>();

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
}

void TestLevel::LevelSet()
{
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
	if (GameEngineInput::IsDown("Back"))
	{
		GameEngineCore::GetInst()->ChangeLevel("SelectMeun");
	}
}