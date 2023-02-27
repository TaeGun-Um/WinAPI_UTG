#include "Wrench.h"

#include <GameEngineCore/GameEngineRender.h>

#include "ContentsEnum.h"

Wrench::Wrench() 
{
}

Wrench::~Wrench() 
{
}

void Wrench::Start()
{
	AnimationRender = CreateRender(RenderOrder::Monster);
	AnimationRender->SetScale({ 400, 400 });

	// Right
	AnimationRender->CreateAnimation({ .AnimationName = "Idle",  .ImageName = "Wrench.bmp", .Start = 0, .End = 13, .InterTime = 0.1f });

	AnimationRender->ChangeAnimation("Idle");
}
void Wrench::Update(float _DeltaTime)
{

}
void Wrench::Render(float _DeltaTime)
{

}