#include "Town_Guard.h"

#include <GameEngineCore/GameEngineRender.h>

#include "ContentsEnum.h"
#include "Player.h"

Town_Guard::Town_Guard() 
{
}

Town_Guard::~Town_Guard() 
{
}

void Town_Guard::Start()
{
	AnimationRender = CreateRender(RenderOrder::Monster);
	AnimationRender->SetScale({ 400, 400 });

	// Right
	AnimationRender->CreateAnimation({ .AnimationName = "Move_R",  .ImageName = "Soldier_Blue_R.bmp", .Start = 0, .End = 9, .InterTime = 0.08f });
}
void Town_Guard::Update(float _DeltaTime)
{

}
void Town_Guard::Render(float _DeltaTime)
{

}

void Town_Guard::CollisionCheck()
{

}

void Town_Guard::DirCheck()
{
	float interval = Player::MainPlayer->GetPos().x - GetPos().x;

	if (0.0f >= interval)
	{
		MoveDirect = true;
	}
	else
	{
		MoveDirect = false;
	}
}