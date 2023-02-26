#include "TestRoom.h"

#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineCore.h>
#include <GameEngineBase/GameEngineDirectory.h>
#include <GameEngineCore/GameEngineActor.h>
#include <GameEngineCore/GameEngineResources.h>

#include "TestRoomMap.h"
#include "Player.h"

#include "GemWindow.h"
#include "Health.h"
#include "BlackBox.h"
#include "WhiteBox.h"

#include "ContentsEnum.h"
#include "ObjectLoad.h"

TestRoom::TestRoom() 
{
}

TestRoom::~TestRoom() 
{
}

void TestRoom::Loading()
{
	ColMap = ObjectLoad::GetObjectLoadPtr()->GetColMap("TestRoom");

	CreateActor<TestRoomMap>();

	CreateActor<GemWindow>();

	CreateActor<Health>();

	Shantae = CreateActor<Player>();
	SHA = dynamic_cast<Player*>(Shantae);
	SHA->SetColMap(ColMap);
	SHA->SetPos({ 300, 750 });
	Shantae->GetLevel()->SetCameraPos({ 20, 50 });
	SHA->CameraMoveSwitch();
}

void TestRoom::Update(float _DeltaTime)
{
	LevelSet();
	Debugging();

	if (SHA->GetPos().x <= 35.0f)
	{
		GameEngineCore::GetInst()->ChangeLevel("TestLevel");
	}
}

void TestRoom::LevelChangeStart(GameEngineLevel* _PrevLevel)
{
	//BGMPlayer = GameEngineResources::GetInst().SoundPlayToControl("Sky.mp3");
	//BGMPlayer.Volume(0.1f);
	//BGMPlayer.LoopCount(10);
}

void TestRoom::LevelChangeEnd(GameEngineLevel* _NextLevel)
{
	SHA->SetPos({ 700, 750 });
	//BGMPlayer.Stop();
}

void TestRoom::LevelSet()
{
}

void TestRoom::Debugging()
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