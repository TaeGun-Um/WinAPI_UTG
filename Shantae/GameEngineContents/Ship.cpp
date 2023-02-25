#include "Ship.h"

#include <GameEngineCore/GameEngineCollision.h>
#include <GameEngineCore/GameEngineRender.h>

#include "ContentsEnum.h"

Ship::Ship() 
{
}

Ship::~Ship() 
{
}

void Ship::Start()
{
	// Animation
	AnimationRender = CreateRender("Ship.Bmp", RenderOrder::BackGround);
	AnimationRender->SetRotFilter("Ship_F.bmp");
	AnimationRender->SetScale(AnimationRender->GetImage()->GetImageScale());
	AnimationRender->SetAngleAdd(30);
}

void Ship::Update(float _DeltaTime)
{
	MoveCalculation(_DeltaTime);
}
void Ship::Render(float _DeltaTime)
{

}

// 중력, 점프, 맵타일
void Ship::MoveCalculation(float _DeltaTime)
{
}