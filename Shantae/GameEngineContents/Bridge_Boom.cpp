#include "Bridge_Boom.h"

#include <GameEngineCore/GameEngineResources.h>
#include <GameEngineCore/GameEngineCollision.h>
#include <GameEngineCore/GameEngineRender.h>
#include <GameEngineCore/GameEngineLevel.h>

#include "ContentsEnum.h"
#include "Public_Boom.h"

Bridge_Boom::Bridge_Boom() 
{
}

Bridge_Boom::~Bridge_Boom() 
{
}

void Bridge_Boom::Start()
{
	// Animation
	AnimationRender = CreateRender(RenderOrder::Effect);
	AnimationRender->SetScale({ 400, 400 });
	AnimationRender->CreateAnimation({ .AnimationName = "Basic",  .ImageName = "Bridge_Boom.bmp", .Start = 0, .End = 2, .InterTime = 0.1f });
	AnimationRender->CreateAnimation({ .AnimationName = "On",  .ImageName = "Bridge_Boom.bmp", .Start = 0, .End = 2, .InterTime = 0.035f });

	AnimationRender->ChangeAnimation("Basic");
}
void Bridge_Boom::Update(float _DeltaTime)
{
	if (0.01f <= AccTime)
	{
		if (5.0f <= AccTime)
		{
			AnimationRender->ChangeAnimation("On");
		}

		if (7.0f <= AccTime)
		{
			IsDeath = true;

			if (true == Direct)
			{
				LeftCreateExplosion(_DeltaTime);
			}
			else
			{
				RightCreateExplosion(_DeltaTime);
			}
		}

		if (true == IsSound)
		{
			if (1 == AnimationRender->GetFrame() && 1 == SoundCount && false == IsDeath)
			{
				SoundCount = 0;
				BGMPlayer = GameEngineResources::GetInst().SoundPlayToControl("Bridgeboom.wav");
				BGMPlayer.Volume(0.07f);
				BGMPlayer.LoopCount(1);
			}
			else if (2 == AnimationRender->GetFrame() && false == IsDeath)
			{
				SoundCount = 1;
			}
		}
	}
}

void Bridge_Boom::Render(float _DeltaTime)
{
}

void Bridge_Boom::Kill()
{
	GameEngineActor* ColActor = AnimationRender->GetActor();
	ColActor->Death();
}

void Bridge_Boom::Explosion()
{
	Public_Boom* Ex = nullptr;
	float4 ExPos = float4::Zero;
	ExPos = GetPos() + (float4::Down * 20);

	Ex = GetLevel()->CreateActor<Public_Boom>();
	Ex->SetPos(ExPos);
}

void Bridge_Boom::Explosions(float4 _Value)
{
	Public_Boom* Ex = nullptr;

	Ex = GetLevel()->CreateActor<Public_Boom>();
	Ex->SetPos(_Value);
	Ex->SetExPlus(0);
	if (false == Direct)
	{
		Ex->SetSoundOff();
	}
}

void Bridge_Boom::RightCreateExplosion(float _DeltaTime)
{
	AnimationRender->Off();
	BoomTime += _DeltaTime;

	if (0.1f <= BoomTime)
	{
		if (4 == BoomCount)
		{
			Explosions(GetPos());
			BoomTime = 0.0f;
			BoomCount--;
		}
		else if (3 == BoomCount)
		{
			Explosions(GetPos() + (float4::Right * 100));
			BoomTime = 0.0f;
			BoomCount--;
		}
		else if (2 == BoomCount)
		{
			Explosions(GetPos() + (float4::Right * 200));
			BoomTime = 0.0f;
			BoomCount--;
		}
		else if (1 == BoomCount)
		{
			Explosions(GetPos() + (float4::Right * 300));
			BoomTime = 0.0f;
			BoomCount--;
		}
		else if (0 == BoomCount)
		{
			Explosions(GetPos() + (float4::Right * 400));
			BoomTime = 0.0f;
			BoomCount--;
		}
		else
		{
			Kill();
		}
	}
}

void Bridge_Boom::LeftCreateExplosion(float _DeltaTime)
{
	AnimationRender->Off();
	BoomTime += _DeltaTime;

	if (0.1f <= BoomTime)
	{
		if (4 == BoomCount)
		{
			Explosions(GetPos());
			BoomTime = 0.0f;
			BoomCount--;
		}
		else if (3 == BoomCount)
		{
			Explosions(GetPos() + (float4::Left * 100));
			BoomTime = 0.0f;
			BoomCount--;
		}
		else if (2 == BoomCount)
		{
			Explosions(GetPos() + (float4::Left * 200));
			BoomTime = 0.0f;
			BoomCount--;
		}
		else if (1 == BoomCount)
		{
			Explosions(GetPos() + (float4::Left * 300));
			BoomTime = 0.0f;
			BoomCount--;
		}
		else if (0 == BoomCount)
		{
			Explosions(GetPos() + (float4::Left * 400));
			BoomTime = 0.0f;
			BoomCount--;
		}
		else
		{
			Kill();
		}
	}
}