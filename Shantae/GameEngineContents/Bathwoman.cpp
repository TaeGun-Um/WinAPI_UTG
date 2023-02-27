#include "Bathwoman.h"

#include <GameEngineCore/GameEngineRender.h>

#include "ContentsEnum.h"

Bathwoman::Bathwoman() 
{
}

Bathwoman::~Bathwoman() 
{
}

void Bathwoman::Start()
{
	AnimationRender = CreateRender(RenderOrder::Monster);
	AnimationRender->SetScale({ 400, 400 });

	// Right
	AnimationRender->CreateAnimation({ .AnimationName = "Move_R",  .ImageName = "Soldier_Blue_R.bmp", .Start = 0, .End = 9, .InterTime = 0.08f });
}
void Bathwoman::Update(float _DeltaTime)
{

}
void Bathwoman::Render(float _DeltaTime)
{

}

void Bathwoman::CollisionCheck()
{

}