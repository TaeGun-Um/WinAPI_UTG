#include "Stylist.h"

#include <GameEngineCore/GameEngineRender.h>

#include "ContentsEnum.h"

Stylist::Stylist() 
{
}

Stylist::~Stylist() 
{
}

void Stylist::Start()
{
	AnimationRender = CreateRender(RenderOrder::Monster);
	AnimationRender->SetScale({ 400, 400 });

	// Right
	AnimationRender->CreateAnimation({ .AnimationName = "Move_R",  .ImageName = "Soldier_Blue_R.bmp", .Start = 0, .End = 9, .InterTime = 0.08f });
}
void Stylist::Update(float _DeltaTime)
{

}
void Stylist::Render(float _DeltaTime)
{

}

void Stylist::Run()
{

}

void Stylist::Move()
{

}