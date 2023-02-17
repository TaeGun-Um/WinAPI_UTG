#include "Opening.h"

// GE header
#include <GameEngineBase/GameEngineDirectory.h>
#include <GameEngineCore/GameEngineResources.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineCore.h>

// Actor header
#include "Opening_Background.h"

Opening::Opening()
{
}

Opening::~Opening()
{
}

void Opening::Loading()
{
	CreateActor<Opening_Background>();
}

void Opening::Update(float _DeltaTime)
{
	// AnyKey == true 시 Level Change(Window 매크로 함수와 연결)
	if (true == GameEngineInput::IsAnyKey())
	{
		// BGMPlayer.Stop();
		GameEngineCore::GetInst()->ChangeLevel("SelectMeun");
	}
}

void Opening::LevelChangeStart(GameEngineLevel* _PrevLevel)
{
	BGMPlayer = GameEngineResources::GetInst().SoundPlayToControl("Title_Theme.mp3");
	BGMPlayer.Volume(0.1f);
	BGMPlayer.LoopCount(10);
}

void Opening::LevelChangeEnd(GameEngineLevel* _NextLevel)
{
	BGMPlayer.Stop();
}