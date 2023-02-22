#include "Public_Boom.h"

#include <GameEngineCore/GameEngineResources.h>
#include <GameEngineCore/GameEngineCollision.h>
#include <GameEngineCore/GameEngineRender.h>
#include <GameEngineCore/GameEngineLevel.h>

#include "ContentsEnum.h"

Public_Boom::Public_Boom() 
{
}

Public_Boom::~Public_Boom() 
{
}

void Public_Boom::Start()
{
	// Animation
	AnimationRender = CreateRender(RenderOrder::Effect);
	AnimationRender->SetScale({ 400, 400 });
	AnimationRender->CreateAnimation({ .AnimationName = "Boom",  .ImageName = "Public_Boom.bmp", .Start = 0, .End = 11, .InterTime = 0.08f });
	AnimationRender->ChangeAnimation("Boom");
}

void Public_Boom::Update(float _DeltaTime)
{
	if (1 == BoomSoundCount && true == IsSound)
	{
		BoomSoundCount = 0;

		BGMPlayer = GameEngineResources::GetInst().SoundPlayToControl("Soldier_boom_explosion.mp3");
		BGMPlayer.Volume(0.1f);
		BGMPlayer.LoopCount(1);
	}

	ExPlusTime += _DeltaTime;

	if (1 <= Plus)
	{	
		ExplosionPlus(ExPlusTime);
	}
	if (true == AnimationRender->IsAnimationEnd())
	{
		GameEngineActor* Act = AnimationRender->GetActor();
		Act->Death();
	}
}

void Public_Boom::Render(float _DeltaTime)
{

}

void Public_Boom::ExplosionPlus(float _Time)
{
	if (0.2f <= ExPlusTime)
	{
		Plus = 0;

		Public_Boom* ExPlus = nullptr;
		float4 ExPlusPos = float4::Zero;
		ExPlusPos = GetPos() + (float4::Right * 25) + (float4::Down * 25);

		ExPlus = GetLevel()->CreateActor<Public_Boom>();
		ExPlus->SetPos(ExPlusPos);
		ExPlus->SetSoundOff();
	}
}