#include "Shantae_Pajamas.h"

#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineRender.h>

#include "ContentsEnum.h"

GameEngineRender* Shantae_Pajamas::AnimationRender = nullptr;

Shantae_Pajamas::Shantae_Pajamas() 
{
}

Shantae_Pajamas::~Shantae_Pajamas() 
{
}

void Shantae_Pajamas::Start()
{
	AnimationRender = CreateRender(RenderOrder::Player);
	AnimationRender->CreateAnimation({ .AnimationName = "Sleep",  .ImageName = "Shantae_Pajamas.bmp", .Start = 0, .End = 3, .InterTime = 0.1f });
	AnimationRender->CreateAnimation({ .AnimationName = "WakeUp",  .ImageName = "Shantae_Pajamas.bmp", .Start = 41, .End = 67, .InterTime = 0.1f });
	AnimationRender->CreateAnimation({ .AnimationName = "Surprise",  .ImageName = "Shantae_Pajamas.bmp", .Start = 4, .End = 40, .InterTime = 0.1f });
	AnimationRender->CreateAnimation({ .AnimationName = "SurpriseMaintain",  .ImageName = "Shantae_Pajamas.bmp", .Start = 7, .End = 40, .InterTime = 0.1f });
	AnimationRender->SetPosition({ 380, 590 });
	AnimationRender->SetScale({ 400, 400 });

	AnimationRender->ChangeAnimation("Sleep");
}
