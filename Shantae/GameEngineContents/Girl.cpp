#include "Girl.h"

#include <GameEngineCore/GameEngineRender.h>

#include "ContentsEnum.h"

Girl::Girl() 
{
}

Girl::~Girl() 
{
}

void Girl::Start()
{
	AnimationRender = CreateRender(RenderOrder::Monster);
	AnimationRender->SetScale({ 400, 400 });

	// Right
	AnimationRender->CreateAnimation({ .AnimationName = "Move_R",  .ImageName = "Soldier_Blue_R.bmp", .Start = 0, .End = 9, .InterTime = 0.08f });
}
void Girl::Update(float _DeltaTime)
{

}
void Girl::Render(float _DeltaTime)
{

}

void Girl::Run()
{

}

void Girl::Move()
{

}