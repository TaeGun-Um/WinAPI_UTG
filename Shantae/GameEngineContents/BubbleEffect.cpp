#include "BubbleEffect.h"

#include <GameEngineCore/GameEngineRender.h>

#include "ContentsEnum.h"
#include "Player.h"

BubbleEffect::BubbleEffect() 
{
}

BubbleEffect::~BubbleEffect() 
{
}

void BubbleEffect::Start()
{
	AnimationRender = CreateRender("Bubble.Bmp", RenderOrder::Effect);
	AnimationRender->SetScale({ 200, 200 });
	AnimationRender->SetAlpha(120);
}

void BubbleEffect::Update(float _DeltaTime)
{
	SetPos(Player::MainPlayer->GetPos() + float4::Up * 55);

	EndTime += _DeltaTime;

	if (EndTime > 8.0f)
	{
		AnimationRender->SetAlpha(60);
	}
}

void BubbleEffect::Render(float _DeltaTime)
{

}

void BubbleEffect::Kill()
{
	GameEngineActor* ColActor = AnimationRender->GetActor();
	ColActor->Off();
	ColActor->Death();
}
