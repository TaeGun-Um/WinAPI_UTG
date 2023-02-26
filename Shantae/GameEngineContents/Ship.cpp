#include "Ship.h"

#include <GameEngineCore/GameEngineCollision.h>
#include <GameEngineCore/GameEngineRender.h>

#include "ContentsEnum.h"
#include "Player.h"

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
	
}

void Ship::Update(float _DeltaTime)
{
	if (1 == InitCount)
	{
		InitCount = 0;
		InitPos = GetPos();
	}

	PlayerCheck();

	if (false == Stop)
	{
		MoveCalculation(_DeltaTime);
	}
	
}
void Ship::Render(float _DeltaTime)
{

}

void Ship::PlayerCheck()
{
	float4 PlayerPos = Player::MainPlayer->GetPos();

	if (InitPos.x + 850.0f <= PlayerPos.x)
	{
		Stop = true;
	}
	else if (InitPos.x - 1000 >= PlayerPos.x)
	{
		Stop = true;
	}
	else
	{
		Stop = false;

		if (true == forceStop)
		{
			Stop = true;
		}
	}
}

// 중력, 점프, 맵타일
void Ship::MoveCalculation(float _DeltaTime)
{
	if (0 == MotionCount)
	{
		SetMove(float4::Down * 10.0f * _DeltaTime);

		if (GetPos().y >= InitPos.y + 5.0f)
		{
			MotionCount = 1;
		}
	}
	else if (1 == MotionCount)
	{
		SetMove(float4::Down * 5.0f * _DeltaTime);

		if (GetPos().y >= InitPos.y + 10.0f)
		{
			MotionCount = 2;
		}
	}
	else if (2 == MotionCount)
	{
		DelayTime += _DeltaTime;

		if (1.0f <= DelayTime)
		{
			DelayTime = 0.0f;
			MotionCount = 3;
		}
	}
	else if (3 == MotionCount)
	{
		SetMove(float4::Up * 10.0f * _DeltaTime);

		if (GetPos().y <= InitPos.y)
		{
			MotionCount = 4;
		}
	}
	else if (4 == MotionCount)
	{
		SetMove(float4::Up * 5.0f * _DeltaTime);

		if (GetPos().y <= InitPos.y - 5.0f)
		{
			MotionCount = 5;
		}
	}
	else if (5 == MotionCount)
	{
		DelayTime += _DeltaTime;

		if (1.0f <= DelayTime)
		{
			DelayTime = 0.0f;
			MotionCount = 0;
		}
	}

	if (0 == MotionCount || 1 == MotionCount)
	{
		AngleTime += _DeltaTime;
		if (0.1f <= AngleTime)
		{
			AngleTime = 0.0f;

			if (Angle <= 1.0f)
			{
				Angle += 0.01f;
			}

			AnimationRender->SetAngleAdd(Angle);
		}
	}
	else if (2 == MotionCount)
	{
		AngleTime += _DeltaTime;
		if (0.1f <= AngleTime)
		{
			AngleTime = 0.0f;

			if (Angle >= -1.0f)
			{
				Angle -= 0.01f;
			}

			AnimationRender->SetAngleAdd(Angle);
		}
	}
	else if (3 == MotionCount || 4 == MotionCount)
	{
		AngleTime += _DeltaTime;
		if (0.1f <= AngleTime)
		{
			AngleTime = 0.0f;

			if (Angle >= -1.0f)
			{
				Angle -= 0.01f;
			}

			AnimationRender->SetAngleAdd(Angle);
		}
	}
	else if (5 == MotionCount)
	{
		AngleTime += _DeltaTime;
		if (0.1f <= AngleTime)
		{
			AngleTime = 0.0f;

			if (Angle <= 1.0f)
			{
				Angle += 0.01f;
			}

			AnimationRender->SetAngleAdd(Angle);
		}
	}
}