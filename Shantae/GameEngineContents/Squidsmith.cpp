#include "Squidsmith.h"

#include <GameEngineCore/GameEngineRender.h>

#include "ContentsEnum.h"

Squidsmith::Squidsmith() 
{
}

Squidsmith::~Squidsmith() 
{
}

void Squidsmith::Start()
{
	AnimationRender = CreateRender(RenderOrder::Monster);
	AnimationRender->SetScale({ 400, 400 });

	// Right
	AnimationRender->CreateAnimation({ .AnimationName = "Move_R",  .ImageName = "Soldier_Blue_R.bmp", .Start = 0, .End = 9, .InterTime = 0.08f });
}
void Squidsmith::Update(float _DeltaTime)
{

}
void Squidsmith::Render(float _DeltaTime)
{

}

void Squidsmith::CollisionCheck()
{

}