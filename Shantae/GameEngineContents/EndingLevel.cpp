#include "EndingLevel.h"

#include <GameEngineBase/GameEngineDirectory.h>
#include <GameEngineCore/GameEngineResources.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineCore.h>

#include "BlackBox.h"
#include "WhiteBox.h"

EndingLevel::EndingLevel() 
{
}

EndingLevel::~EndingLevel() 
{
}

void EndingLevel::Loading()
{
	// CreateActor<Opening_Background>();
}

void EndingLevel::Update(float _DeltaTime)
{
	// BlackBoxAnimation(_DeltaTime);
}

void EndingLevel::LevelChangeStart(GameEngineLevel* _PrevLevel)
{
	//BGMPlayer = GameEngineResources::GetInst().SoundPlayToControl("Title_announce.wav");
	//BGMPlayer.Volume(0.1f);
	//BGMPlayer.LoopCount(1);
}

void EndingLevel::LevelChangeEnd(GameEngineLevel* _NextLevel)
{
	BGMPlayer.Stop();

	if (nullptr != BBox)
	{
		BBox->Death();
		BBox = nullptr;
		BBoxCount = 1;
	}
}

void EndingLevel::BlackBoxAnimation(float _DeltaTime)
{
	if (1 == WBoxCount)
	{
		WBoxCount = 0;
		WBox = CreateActor<WhiteBox>();
		WBox->FadeOutStart(1, 0.0f);
	}

	// AnyKey == true 시 Level Change(Window 매크로 함수와 연결)
	//if (true == GameEngineInput::IsAnyKey())
	//{
	//	if (1 == BBoxCount)
	//	{
	//		BBoxCount = 0;
	//		BBox = CreateActor<BlackBox>();
	//		BBox->FadeInStart(1, 0.0f);

	//		SelectPlayer = GameEngineResources::GetInst().SoundPlayToControl("Botton_select.wav");
	//		SelectPlayer.Volume(0.1f);
	//		SelectPlayer.LoopCount(1);
	//	}
	//}

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