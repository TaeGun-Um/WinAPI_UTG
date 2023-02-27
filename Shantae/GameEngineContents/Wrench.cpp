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
	AnimationRender->CreateAnimation({ .AnimationName = "Move_R",  .ImageName = "Soldier_Blue_R.bmp", .Start = 0, .End = 9, .InterTime = 0.08f });
}
void Wrench::Update(float _DeltaTime)
{

}
void Wrench::Render(float _DeltaTime)
{

}