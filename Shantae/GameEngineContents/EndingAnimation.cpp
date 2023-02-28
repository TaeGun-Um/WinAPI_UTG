#include "EndingAnimation.h"

#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineRender.h>
#include <GameEngineCore/GameEngineLevel.h>

#include "ContentsEnum.h"
#include "GameOverText.h"

EndingAnimation::EndingAnimation() 
{
}

EndingAnimation::~EndingAnimation() 
{
}

void EndingAnimation::Start()
{
	AnimationRender = CreateRender(RenderOrder::AnimationObject);
	AnimationRender->SetScale({ 1280.0f, 720.0f }); 
	AnimationRender->SetPosition({ 640.0f, 360.0f });

	AnimationRender->CreateAnimation({ .AnimationName = "Cut1",  .ImageName = "EndingCredit.bmp", .Start = 0, .End = 0, .InterTime = 0.1f, .Loop = false });
	AnimationRender->CreateAnimation({ .AnimationName = "Cut2",  .ImageName = "EndingCredit.bmp", .Start = 1, .End = 1, .InterTime = 0.1f, .Loop = false });
	AnimationRender->CreateAnimation({ .AnimationName = "Cut3",  .ImageName = "EndingCredit.bmp", .Start = 2, .End = 2, .InterTime = 0.1f, .Loop = false });
	AnimationRender->CreateAnimation({ .AnimationName = "Cut4",  .ImageName = "EndingCredit.bmp", .Start = 3, .End = 3, .InterTime = 0.1f, .Loop = false });
	AnimationRender->CreateAnimation({ .AnimationName = "Cut5",  .ImageName = "EndingCredit.bmp", .Start = 4, .End = 4, .InterTime = 0.1f, .Loop = false });
	AnimationRender->CreateAnimation({ .AnimationName = "Cut6",  .ImageName = "EndingCredit.bmp", .Start = 5, .End = 5, .InterTime = 0.1f, .Loop = false });
	AnimationRender->CreateAnimation({ .AnimationName = "Cut7",  .ImageName = "EndingCredit.bmp", .Start = 6, .End = 6, .InterTime = 0.1f, .Loop = false });
	AnimationRender->CreateAnimation({ .AnimationName = "Cut8",  .ImageName = "EndingCredit.bmp", .Start = 7, .End = 7, .InterTime = 0.1f, .Loop = false });

	AnimationRender->SetAlpha(0);
	AnimationRender->ChangeAnimation("Cut1");
}

void EndingAnimation::Update(float _DeltaTime)
{
	if (GameEngineInput::IsPress("Attack"))
	{
		Doubling = true;
	}
	else
	{
		Doubling = false;
	}

	AnimationCutTime += _DeltaTime;

	if (true == Doubling)
	{
		AnimationCutTime += _DeltaTime;
	}

	if (8.0f <= AnimationCutTime && false == IsEnd)
	{
		AnimationCutTime = 0.0f;
		++AnimationCount;
		CutChange = 1;
	}
	if (6.0f <= AnimationCutTime && true == IsEnd)
	{
		if (1 == CreateTextCount)
		{
			CreateTextCount = 0;
			CreateText();
		}
	}
	else if (6.0f <= AnimationCutTime)
	{
		if (1 <= AlphaValue)
		{
			--AlphaValue;
		}
		if (true == Doubling)
		{
			if (1 <= AlphaValue)
			{
				--AlphaValue;
			}
		}

		AnimationRender->SetAlpha(AlphaValue);
	}
	else if (1.0f <= AnimationCutTime)
	{
		if (1 == CutChange)
		{
			CutChange = 0;
			CutCheck("Cut");
		}

		if (254 >= AlphaValue)
		{
			++AlphaValue;
		}
		if (true == Doubling)
		{
			if (254 >= AlphaValue)
			{
				++AlphaValue;
			}
		}

		AnimationRender->SetAlpha(AlphaValue);
	}
}

void EndingAnimation::Render(float _DeltaTime)
{

}

void EndingAnimation::CreateText()
{
	GameOverText* Ex = nullptr;
	Ex = GetLevel()->CreateActor<GameOverText>();
}

void EndingAnimation::CutCheck(const std::string_view& _AnimationName)
{
	if (0 == AnimationCount)
	{
		DirString = "1";
	}
	else if (1 == AnimationCount)
	{
		DirString = "2";
	}
	else if (2 == AnimationCount)
	{
		DirString = "3";
	}
	else if (3 == AnimationCount)
	{
		DirString = "4";
	}
	else if (4 == AnimationCount)
	{
		DirString = "5";
	}
	else if (5 == AnimationCount)
	{
		DirString = "6";
	}
	else if (6 == AnimationCount)
	{
		DirString = "7";
	}
	else if (7 == AnimationCount)
	{
		DirString = "8";
		IsEnd = true;
	}
	else 
	{
		DirString = "8";
	}

	AnimationRender->ChangeAnimation(_AnimationName.data() + DirString);

}