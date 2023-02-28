#include "GameOverText.h"

#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineRender.h>

#include "ContentsEnum.h"

bool GameOverText::IsEnd = false;

GameOverText::GameOverText() 
{
}

GameOverText::~GameOverText() 
{
}

void GameOverText::Start()
{
	AnimationRender = CreateRender("GameOver.Bmp", RenderOrder::Effect);
	AnimationRender->SetScale(AnimationRender->GetImage()->GetImageScale());
	AnimationRender->SetPosition({ 1120.0f, 610.0f });
	AnimationRender->SetAlpha(0);
}
void GameOverText::Update(float _DeltaTime)
{
	if (GameEngineInput::IsPress("Attack"))
	{
		Doubling = true;
	}
	else
	{
		Doubling = false;
	}

	DelayTime += _DeltaTime;

	if (1.0f <= DelayTime)
	{
		AlphaTime += _DeltaTime;

		if (true == Doubling)
		{
			AlphaTime += _DeltaTime;
		}

		if (0.005f <= AlphaTime)
		{
			AlphaTime = 0.0f;

			if (254 >= AlphaValue)
			{
				++AlphaValue;
			}
			else if (254 <= AlphaValue)
			{
				IsEnd = true;
			}

			if (true == Doubling)
			{
				if (254 >= AlphaValue)
				{
					++AlphaValue;
				}
			}
		}
		AnimationRender->SetAlpha(AlphaValue);
	}
}

void GameOverText::Render(float _DeltaTime)
{

}