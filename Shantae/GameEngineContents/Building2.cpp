#include "Building2.h"

#include <GameEngineCore/GameEngineCollision.h>
#include <GameEngineCore/GameEngineRender.h>

#include "ContentsEnum.h"

Building2::Building2() 
{
}

Building2::~Building2() 
{
}

void Building2::Start()
{
	//AnimationRender = CreateRender("Building2.Bmp", RenderOrder::BackGround);
	//AnimationRender->SetRotFilter("Building2_F.bmp");
	//AnimationRender->SetScale(AnimationRender->GetImage()->GetImageScale());
	// AnimationRender->SetAngleAdd(30);

	// Collision
	BodyCollision = CreateCollision(CollisionOrder::Effect);
	BodyCollision->SetDebugRenderType(CT_Rect);
	BodyCollision->SetScale({ 50, 75 });
	BodyCollision->SetPosition({ 0, 0 });
}

void Building2::Update(float _DeltaTime)
{
	CollisionCheck();
	MoveCalculation(_DeltaTime);
}
void Building2::Render(float _DeltaTime)
{

}

// 중력, 점프, 맵타일
void Building2::MoveCalculation(float _DeltaTime)
{
	MoveSpeed = 900.0f;
	SetMove(float4::Up * MoveSpeed * _DeltaTime);
}

void Building2::CollisionCheck()
{
	if (nullptr != BodyCollision)
	{
		if (true == BodyCollision->Collision({ .TargetGroup = static_cast<int>(CollisionOrder::Ground), .TargetColType = CT_Rect, .ThisColType = CT_Rect }))
		{
		}
	}
}