#include "Wave.h"

#include <GameEngineCore/GameEngineCollision.h>
#include <GameEngineCore/GameEngineRender.h>

#include "ContentsEnum.h"

Wave::Wave() 
{
}

Wave::~Wave() 
{
}

void Wave::Start()
{
	// Animation
	AnimationRender = CreateRender(RenderOrder::AnimationObject);
	AnimationRender->SetScale({ 800, 800 });
	AnimationRender->CreateAnimation({ .AnimationName = "Wave",  .ImageName = "Wave.bmp", .Start = 0, .End = 7, .InterTime = 0.1f });

	AnimationRender->ChangeAnimation("Wave");
}

void Wave::Update(float _DeltaTime)
{

}
void Wave::Render(float _DeltaTime)
{

}