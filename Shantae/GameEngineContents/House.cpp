#include "House.h"

// GE
#include <GameEngineBase/GameEngineDirectory.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineCore.h>
#include <GameEngineCore/GameEngineResources.h>

// Actor
#include "Player.h"
#include "House_Hut.h"
#include "House_Interior.h"
#include "Shantae_Pajamas.h"

#include "GemWindow.h"
#include "Health.h"

House::House() 
{
}

House::~House() 
{
}

void House::Loading()
{
	// Background
	CreateActor<House_Hut>();

	// Map
	CreateActor<House_Interior>();

	// Monster

	// UI
	CreateActor<GemWindow>();
	CreateActor<Health>();

	// Player
	CreateActor<Shantae_Pajamas>();
}

void House::Update(float _DeltaTime)
{
	OverlapTime += _DeltaTime;

	LevelSet();
	Debugging();
	AnimationChange();
	SoundCombination();
}

void House::LevelChangeStart(GameEngineLevel* _PrevLevel)
{
}

void House::LevelChangeEnd(GameEngineLevel* _NextLevel)
{
}

void House::LevelSet()
{
}

void House::Debugging()
{
	if (GameEngineInput::IsDown("NextLevel"))
	{
		if (OverlapTime > 0.5f)
		{
			GameEngineCore::GetInst()->ChangeLevel("HouseFront");
			OverlapTime = 0.0f;
		}
	}
	if (GameEngineInput::IsDown("Back"))
	{
		GameEngineCore::GetInst()->ChangeLevel("SelectMeun");
	}
}

void House::AnimationChange()
{
	if (GameEngineInput::IsDown("Attack"))
	{
		++Change;

		if (1 == Change)
		{
			Shantae_Pajamas::AnimationRender->ChangeAnimation("WakeUp");
		}
		else if (2 == Change)
		{
			Shantae_Pajamas::AnimationRender->ChangeAnimation("Surprise");
		}
		else if (3 == Change)
		{
			Shantae_Pajamas::AnimationRender->ChangeAnimation("SurpriseMaintain");
		}
		else
		{
			GameEngineCore::GetInst()->ChangeLevel("HouseFront");
		}
	}
}
void House::SoundCombination()
{

}