#include "TestRoom2.h"

#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineCore.h>
#include <GameEngineBase/GameEngineDirectory.h>
#include <GameEngineCore/GameEngineActor.h>
#include <GameEngineCore/GameEngineResources.h>

#include "TestRoomMap2.h"
#include "Player.h"

#include "GemWindow.h"
#include "Health.h"
#include "BlackBox.h"
#include "WhiteBox.h"

#include "ContentsEnum.h"
#include "ObjectLoad.h"

TestRoom2::TestRoom2()
{
}

TestRoom2::~TestRoom2()
{
}

void TestRoom2::Loading()
{
	ColMap = ObjectLoad::GetObjectLoadPtr()->GetColMap("TestRoom2");

	CreateActor<TestRoomMap2>();

	CreateActor<GemWindow>();

	CreateActor<Health>();

	Shantae = CreateActor<Player>();
	SHA = dynamic_cast<Player*>(Shantae);
	SHA->SetColMap(ColMap);
	SHA->SetPos({ 300, 750 });
	Shantae->GetLevel()->SetCameraPos({ 20, 50 });
	SHA->CameraMoveSwitch();
}

void TestRoom2::Update(float _DeltaTime)
{
	LevelSet();
	Debugging();

	if (SHA->GetPos().x <= 35.0f)
	{
		GameEngineCore::GetInst()->ChangeLevel("TestLevel");
	}
}

void TestRoom2::LevelChangeStart(GameEngineLevel* _PrevLevel)
{
	//BGMPlayer = GameEngineResources::GetInst().SoundPlayToControl("Sky.mp3");
	//BGMPlayer.Volume(0.1f);
	//BGMPlayer.LoopCount(10);
}

void TestRoom2::LevelChangeEnd(GameEngineLevel* _NextLevel)
{
	SHA->SetPos({ 700, 750 });
	//BGMPlayer.Stop();
}

void TestRoom2::LevelSet()
{
	if (1 == Set)
	{
		Set = 0;

		Player::MainPlayer = SHA;
	}
}

void TestRoom2::Debugging()
{
	if (GameEngineInput::IsDown("BeforeLevel"))
	{
		GameEngineCore::GetInst()->ChangeLevel("TestLevel");
	}

	if (GameEngineInput::IsDown("Back"))
	{
		GameEngineCore::GetInst()->ChangeLevel("SelectMeun");
	}
}