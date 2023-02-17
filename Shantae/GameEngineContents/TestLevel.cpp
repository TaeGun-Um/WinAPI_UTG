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

#include "GemWindow.h"
#include "Health.h"

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

	CreateActor<GemWindow>();

	CreateActor<Health>();

	// MonsterSpawner* s = CreateSpawner({ 500, 200 }, "Red", ColMap, { 400, 1000 });
	//s->SetAmbushTrue();

	//GameEngineActor* Spawn1 = CreateActor<MonsterSpawner>();
	//MonsterSpawner* SPA1 = dynamic_cast<MonsterSpawner*>(Spawn1);
	//Spawn1->SetPos({ 500, 200 });
	//SPA1->SpawnerSetting("blue", ColMap, {400, 1000});
	//SPA1->SetAmbushTrue();

	//Soldier_Red* Spawn1 = CreateActor<Soldier_Red>();
	//Soldier_Red* SPA1 = dynamic_cast<Soldier_Red*>(Spawn1);
	//Spawn1->SetPos({ 750, 850 });
	//SPA1->SetColMap(ColMap);

	//Soldier_Blue* Spawn3 = CreateActor<Soldier_Blue>();
	//Soldier_Blue* SPA3 = dynamic_cast<Soldier_Blue*>(Spawn3);
	//Spawn3->SetPos({ 400, 850 });
	//SPA3->SetColMap(ColMap);

	//Soldier_Black* Spawn2 = CreateActor<Soldier_Black>();
	//Soldier_Black* SPA2 = dynamic_cast<Soldier_Black*>(Spawn2);
	//Spawn2->SetPos({ 750, 850 });
	//SPA2->SetColMap(ColMap);

	//Soldier_Bomberman* Spawn3 = CreateActor<Soldier_Bomberman>();
	//Soldier_Bomberman* SPA3 = dynamic_cast<Soldier_Bomberman*>(Spawn3);
	//Spawn3->SetPos({ 1100, 500 });
	//SPA3->SetColMap(ColMap);

	Machinegun_Plat* Spawn3 = CreateActor<Machinegun_Plat>();
	Machinegun_Plat* SPA3 = dynamic_cast<Machinegun_Plat*>(Spawn3);
	Spawn3->SetPos({ 500, 750 });

	Machinegun_Plat* Spawn4 = CreateActor<Machinegun_Plat>();
	Machinegun_Plat* SPA4 = dynamic_cast<Machinegun_Plat*>(Spawn4);
	Spawn4->SetPos({ 600, 750 });

	Machinegun_Plat* Spawn5 = CreateActor<Machinegun_Plat>();
	Machinegun_Plat* SPA5 = dynamic_cast<Machinegun_Plat*>(Spawn5);
	Spawn5->SetPos({ 700, 750 });

	Shantae = CreateActor<Player>();
	SHA = dynamic_cast<Player*>(Shantae);
	SHA->SetColMap(ColMap);
	SHA->SetPos({ 300, 850 });
	Shantae->GetLevel()->SetCameraPos({ 0, 200 });

	// 罚待备开 soldier 积己
	//srand(static_cast<unsigned int>(time(nullptr)));
	//for (size_t i = 0; i < 2; i++)
	//{
	//	Soldier* Actor = CreateActor<Soldier>(RenderOrder::Monster);
	//	Actor->SetMove(float4(static_cast<float>(rand() % GameEngineWindow::GetScreenSize().ix()), static_cast<float>(rand() % GameEngineWindow::GetScreenSize().iy())));
	//}

}

//MonsterSpawner* TestLevel::CreateSpawner(const float4& _SpawnerPos, const std::string_view& _MonsterType, GameEngineImage* _MonsterColMap, const float4& _MonstorPos)
//{
//	GameEngineActor* Spawner = CreateActor<MonsterSpawner>();
//	MonsterSpawner* SPA = dynamic_cast<MonsterSpawner*>(Spawner);
//	Spawner->SetPos(_SpawnerPos);
//	SPA->SpawnerSetting(_MonsterType, _MonsterColMap, _MonstorPos);
//
//	return SPA;
//}

void TestLevel::Update(float _DeltaTime)
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
	if (GameEngineInput::IsDown("Back"))
	{
		GameEngineCore::GetInst()->ChangeLevel("SelectMeun");
	}
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