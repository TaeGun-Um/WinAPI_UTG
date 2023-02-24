#include "Opening.h"

// GE header
#include <GameEngineBase/GameEngineDirectory.h>
#include <GameEngineCore/GameEngineResources.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineCore.h>

// Actor header
#include "Opening_Background.h"
#include "BlackBox.h"
#include "WhiteBox.h"

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
	BlackBoxAnimation(_DeltaTime);
}

void Opening::LevelChangeStart(GameEngineLevel* _PrevLevel)
{
	AnnouncePlayer = GameEngineResources::GetInst().SoundPlayToControl("Title_announce.wav");
	AnnouncePlayer.Volume(0.1f);
	AnnouncePlayer.LoopCount(1);

	BGMPlayer = GameEngineResources::GetInst().SoundPlayToControl("Title_Theme.mp3");
	BGMPlayer.Volume(0.08f);
	BGMPlayer.LoopCount(10);
}

void Opening::LevelChangeEnd(GameEngineLevel* _NextLevel)
{
	BGMPlayer.Stop();
	AnnouncePlayer.Stop();

	if (nullptr != BBox)
	{
		BBox->Death();
		BBox = nullptr;
		BBoxCount = 1;
	}
}

void Opening::BlackBoxAnimation(float _DeltaTime)
{
	if (1 == WBoxCount)
	{
		WBoxCount = 0;
		WBox = CreateActor<WhiteBox>();
		WBox->FadeOutStart(1, 0.0f);
	}

	// AnyKey == true 시 Level Change(Window 매크로 함수와 연결)
	if (true == GameEngineInput::IsAnyKey())
	{
		if (1 == BBoxCount)
		{
			BBoxCount = 0;
			BBox = CreateActor<BlackBox>();
			BBox->FadeInStart(1, 0.0f);

			SelectPlayer = GameEngineResources::GetInst().SoundPlayToControl("Botton_select.wav");
			SelectPlayer.Volume(0.1f);
			SelectPlayer.LoopCount(1);
		}
	}

	if (0 == BBoxCount)
	{
		if (true == BBox->GetIsFadeInOver())
		{
			Delay += _DeltaTime;

			if (Delay >= 0.5f)
			{
				GameEngineCore::GetInst()->ChangeLevel("SelectMeun");
			}
		}
	}
}