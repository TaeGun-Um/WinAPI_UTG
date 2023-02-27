#include "Dancer.h"

#include <GameEngineCore/GameEngineRender.h>

#include "ContentsEnum.h"

Dancer::Dancer() 
{
}

Dancer::~Dancer() 
{
}

void Dancer::Start()
{
	AnimationRender = CreateRender(RenderOrder::Monster);
	AnimationRender->SetScale({ 400, 400 });

	// Right
	AnimationRender->CreateAnimation({ .AnimationName = "Move_R",  .ImageName = "Soldier_Blue_R.bmp", .Start = 0, .End = 9, .InterTime = 0.08f });
}
void Dancer::Update(float _DeltaTime)
{

}
void Dancer::Render(float _DeltaTime)
{

}