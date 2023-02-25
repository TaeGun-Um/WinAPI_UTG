#include "Building1.h"

#include <GameEngineCore/GameEngineCollision.h>
#include <GameEngineCore/GameEngineRender.h>

#include "ContentsEnum.h"

Building1::Building1() 
{
}

Building1::~Building1() 
{
}

void Building1::Start()
{
	//AnimationRender = CreateRender("Building1.Bmp", RenderOrder::BackGround);
	//AnimationRender->SetRotFilter("Building1_F.bmp");
	//AnimationRender->SetScale(AnimationRender->GetImage()->GetImageScale());
	// AnimationRender->SetAngleAdd(30);

	// Collision
	BodyCollision = CreateCollision(CollisionOrder::Effect);
	BodyCollision->SetDebugRenderType(CT_Rect);
	BodyCollision->SetScale({ 50, 75 });
	BodyCollision->SetPosition({ 0, 0 });
}

void Building1::Update(float _DeltaTime)
{
	CollisionCheck();
	MoveCalculation(_DeltaTime);
}
void Building1::Render(float _DeltaTime)
{

}

// 중력, 점프, 맵타일
void Building1::MoveCalculation(float _DeltaTime)
{
}

void Building1::CollisionCheck()
{
	if (nullptr != BodyCollision)
	{
		if (true == BodyCollision->Collision({ .TargetGroup = static_cast<int>(CollisionOrder::Ground), .TargetColType = CT_Rect, .ThisColType = CT_Rect }))
		{
		}
	}
}