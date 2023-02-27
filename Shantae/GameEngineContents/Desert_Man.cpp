#include "Desert_Man.h"

#include <GameEngineCore/GameEngineRender.h>

#include "ContentsEnum.h"

Desert_Man::Desert_Man() 
{
}

Desert_Man::~Desert_Man() 
{
}

void Desert_Man::Start()
{
	AnimationRender = CreateRender(RenderOrder::Monster);
	AnimationRender->SetScale({ 400, 400 });

	// Right
	AnimationRender->CreateAnimation({ .AnimationName = "Move_R",  .ImageName = "Soldier_Blue_R.bmp", .Start = 0, .End = 9, .InterTime = 0.08f });
}
void Desert_Man::Update(float _DeltaTime)
{

}
void Desert_Man::Render(float _DeltaTime)
{

}

void Desert_Man::Run()
{

}

void Desert_Man::Move()
{

}