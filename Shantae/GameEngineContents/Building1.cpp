#include "Building1.h"

#include <GameEngineCore/GameEngineCollision.h>
#include <GameEngineCore/GameEngineRender.h>

#include "ContentsEnum.h"
#include "Player.h"

Building1::Building1() 
{
}

Building1::~Building1() 
{
}

void Building1::Start()
{
	AnimationRender = CreateRender("Building1.Bmp", RenderOrder::BackGround);
	AnimationRender->SetRotFilter("Building1_F.bmp");
	AnimationRender->SetScale(AnimationRender->GetImage()->GetImageScale());

	// Collision
	BodyCollision = CreateCollision(CollisionOrder::Trigger);
	BodyCollision->SetDebugRenderType(CT_Rect);
	BodyCollision->SetScale({ 10, 700 });
	BodyCollision->SetPosition({ -350, 300 });
}

void Building1::Update(float _DeltaTime)
{
	if (1 == InitCount)
	{
		InitCount = 0;
		InitPos = GetPos();
	}

	CollisionCheck();

	if (true == Break)
	{
		if (true == Left)
		{
			LeftBreak(_DeltaTime);
		}		
		else if (true == Right)
		{
			RightBreak(_DeltaTime);
		}

		BreakDelay += _DeltaTime;

		if (0.5f <= BreakDelay)
		{
			MoveCalculation(_DeltaTime);
		}
		
		DirectCheckForKill();
	}
}
void Building1::Render(float _DeltaTime)
{

}

void Building1::MoveCalculation(float _DeltaTime)
{
	MoveDir += float4::Down * 100.0f * _DeltaTime;

	SetMove(MoveDir * _DeltaTime);
}

void Building1::DirectCheckForKill()
{
	float4 Pos = InitPos + (float4::Down * 500);

	if (GetPos().y >= Pos.y)
	{
		Kill();
	}
}

void Building1::Kill()
{
	GameEngineActor* ColActor = AnimationRender->GetActor();
	ColActor->Off();
	ColActor->Death();
}

void Building1::LeftBreak(float _DeltaTime)
{
	LeftBTime += _DeltaTime;

	if (0.25f <= LeftBTime)
	{
		if (0.35f <= LeftBTime)
		{
			LeftB -= 0.05f;
		}
		else if (0.5f <= LeftBTime && LeftB >= -50.0f)
		{
			LeftB -= 0.15f;
		}
		
		AnimationRender->SetAngle(LeftB);
	}
}

void Building1::RightBreak(float _DeltaTime)
{
	RightBTime += _DeltaTime;

	if (0.25f <= RightBTime)
	{
		if (0.35f <= RightBTime)
		{
			RightB += 0.05f;
		}
		else if (0.5f <= RightBTime && RightB <= 50.0f)
		{
			RightB += 0.15f;
		}

		AnimationRender->SetAngle(RightB);
	}
}

void Building1::CollisionCheck()
{
	if (nullptr != BodyCollision)
	{
		if (true == BodyCollision->Collision({ .TargetGroup = static_cast<int>(CollisionOrder::Player), .TargetColType = CT_Rect, .ThisColType = CT_Rect }))
		{
			BodyCollision->Off();
			Break = true;
			Player::MainPlayer->SetCameraShaking(3.0f, 3.0f);
		}
	}
}