#include "Mayor_Scuttlebutt.h"

#include <GameEngineCore/GameEngineRender.h>

#include "ContentsEnum.h"
#include "Player.h"

Mayor_Scuttlebutt::Mayor_Scuttlebutt() 
{
}

Mayor_Scuttlebutt::~Mayor_Scuttlebutt() 
{
}

void Mayor_Scuttlebutt::Start()
{
	AnimationRender = CreateRender(RenderOrder::Monster);
	AnimationRender->SetScale({ 400, 400 });

	// Right
	AnimationRender->CreateAnimation({ .AnimationName = "Move_R",  .ImageName = "Soldier_Blue_R.bmp", .Start = 0, .End = 9, .InterTime = 0.08f });
}
void Mayor_Scuttlebutt::Update(float _DeltaTime)
{

}
void Mayor_Scuttlebutt::Render(float _DeltaTime)
{

}

void Mayor_Scuttlebutt::DirCheck()
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