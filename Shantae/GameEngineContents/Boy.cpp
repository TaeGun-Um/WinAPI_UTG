#include "Boy.h"

#include <GameEngineCore/GameEngineRender.h>

#include "ContentsEnum.h"

Boy::Boy() 
{
}

Boy::~Boy() 
{
}

void Boy::Start()
{
	AnimationRender = CreateRender(RenderOrder::Monster);
	AnimationRender->SetScale({ 400, 400 });

	// Right
	AnimationRender->CreateAnimation({ .AnimationName = "Move_R",  .ImageName = "Soldier_Blue_R.bmp", .Start = 0, .End = 9, .InterTime = 0.08f });
}
void Boy::Update(float _DeltaTime)
{

}
void Boy::Render(float _DeltaTime)
{

}

void Boy::Run()
{

}

void Boy::Move()
{

}