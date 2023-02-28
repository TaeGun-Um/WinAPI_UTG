#include "EndingLevel.h"

#include <GameEngineBase/GameEngineDirectory.h>
#include <GameEngineCore/GameEngineResources.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineCore.h>

#include "EndingAnimation.h"
#include "GameOverText.h"
#include "House_BlackBox.h"
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
	CreateActor<House_BlackBox>();

	CreateActor<EndingAnimation>();
}

void EndingLevel::Update(float _DeltaTime)
{
	BlackBoxAnimation(_DeltaTime);
	Debugging();
}

void EndingLevel::LevelChangeStart(GameEngineLevel* _PrevLevel)
{
	BGMPlayer = GameEngineResources::GetInst().SoundPlayToControl("Ending.mp3");
	BGMPlayer.Volume(0.2f);
	BGMPlayer.LoopCount(1);
}

void EndingLevel::LevelChangeEnd(GameEngineLevel* _NextLevel)
{
	BGMPlayer.Stop();

	if (nullptr != WBox)
	{
		WBox->Death();
		WBox = nullptr;
		WBoxCount = 1;
	}
}

void EndingLevel::BlackBoxAnimation(float _DeltaTime)
{
	if (true == GameOverText::IsEnd)
	{
		if (true == GameEngineInput::IsAnyKey())
		{
			if (1 == WBoxCount)
			{
				WBoxCount = 0;
				WBox = CreateActor<WhiteBox>();
				WBox->FadeInStart(0, 1.0f);
				BGMPlayer.PauseOn();
			}
		}
	}

	if (0 == WBoxCount)
	{
		if (true == WBox->GetIsFadeInOver())
		{
			GameEngineCore::GetInst()->ChangeLevel("Opening");
		}
	}
}

void EndingLevel::Debugging()
{
	if (GameEngineInput::IsDown("NextLevel"))
	{
		GameEngineCore::GetInst()->ChangeLevel("Opening");
	}
	if (GameEngineInput::IsDown("Back"))
	{
		GameEngineCore::GetInst()->ChangeLevel("SelectMeun");
	}
}