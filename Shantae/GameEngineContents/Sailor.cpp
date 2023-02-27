#include "Sailor.h"

#include <GameEngineCore/GameEngineRender.h>

#include "ContentsEnum.h"
#include "Player.h"

Sailor::Sailor() 
{
}

Sailor::~Sailor() 
{
}

void Sailor::Start()
{
	AnimationRender = CreateRender(RenderOrder::Monster);
	AnimationRender->SetScale({ 400, 400 });

	// Right
	AnimationRender->CreateAnimation({ .AnimationName = "Move_R",  .ImageName = "Soldier_Blue_R.bmp", .Start = 0, .End = 9, .InterTime = 0.08f });
}
void Sailor::Update(float _DeltaTime)
{

}
void Sailor::Render(float _DeltaTime)
{

}

void Sailor::DirCheck()
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