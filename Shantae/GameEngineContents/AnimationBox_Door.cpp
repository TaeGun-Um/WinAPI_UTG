#include "AnimationBox_Door.h"

#include <GameEngineCore/GameEngineRender.h>
#include <GameEngineCore/GameEngineCollision.h>

#include "ContentsEnum.h"

AnimationBox_Door::AnimationBox_Door() 
{
}

AnimationBox_Door::~AnimationBox_Door() 
{
}

void AnimationBox_Door::Start()
{
	GameEngineRender* Render3 = CreateRender("AnimationBox_Door.Bmp", RenderOrder::BackGround);
	Render3->SetPosition(Render3->GetImage()->GetImageScale().half());
	Render3->SetScale(Render3->GetImage()->GetImageScale());

	BodyCollision = CreateCollision(CollisionOrder::Trigger);
	BodyCollision->SetDebugRenderType(CT_Rect);
	BodyCollision->SetScale({ 150, 225 });
	BodyCollision->SetPosition({ 75, 112.5f });
}

void AnimationBox_Door::Update(float _DeltaTime)
{
	CollisionCheck();
}

void AnimationBox_Door::CollisionCheck()
{
	if (nullptr != BodyCollision)
	{
		if (true == BodyCollision->Collision({ .TargetGroup = static_cast<int>(CollisionOrder::Player), .TargetColType = CT_Rect, .ThisColType = CT_Rect }))
		{
			int a = 0;
		}
	}
}