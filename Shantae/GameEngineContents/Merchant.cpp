#include "Merchant.h"

#include <GameEngineCore/GameEngineRender.h>

#include "ContentsEnum.h"

Merchant::Merchant() 
{
}

Merchant::~Merchant() 
{
}

void Merchant::Start()
{
	AnimationRender = CreateRender(RenderOrder::Monster);
	AnimationRender->SetScale({ 400, 400 });

	// Right
	AnimationRender->CreateAnimation({ .AnimationName = "Move_R",  .ImageName = "Soldier_Blue_R.bmp", .Start = 0, .End = 9, .InterTime = 0.08f });
}
void Merchant::Update(float _DeltaTime)
{

}
void Merchant::Render(float _DeltaTime)
{

}

void Merchant::CollisionCheck()
{

}

void Merchant::Run()
{

}