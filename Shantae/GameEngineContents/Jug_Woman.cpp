#include "Jug_Woman.h"

#include <GameEngineCore/GameEngineRender.h>

#include "ContentsEnum.h"

Jug_Woman::Jug_Woman() 
{
}

Jug_Woman::~Jug_Woman() 
{
}

void Jug_Woman::Start()
{
	AnimationRender = CreateRender(RenderOrder::Monster);
	AnimationRender->SetScale({ 400, 400 });

	// Right
	AnimationRender->CreateAnimation({ .AnimationName = "Move_R",  .ImageName = "Soldier_Blue_R.bmp", .Start = 0, .End = 9, .InterTime = 0.08f });
}
void Jug_Woman::Update(float _DeltaTime)
{

}
void Jug_Woman::Render(float _DeltaTime)
{

}

void Jug_Woman::Run()
{

}

void Jug_Woman::Move()
{

}