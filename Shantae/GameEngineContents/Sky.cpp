#include "Sky.h"

#include <GameEngineCore/GameEngineRender.h>

#include "ContentsEnum.h"

Sky::Sky()
{
}

Sky::~Sky()
{
}

void Sky::Start()
{
	Sky_one = CreateRender("Sky.Bmp", RenderOrder::BackGround);
	Sky_one->SetScale(Sky_one->GetImage()->GetImageScale());
	Sky_one->SetPosition({ 1100, 200 });
	Sky_one->EffectCameraOff();
	OneInitPos = Sky_one->GetPosition();

	Sky_two = CreateRender("Sky.Bmp", RenderOrder::BackGround);
	Sky_two->SetScale(Sky_two->GetImage()->GetImageScale());
	Sky_two->SetPosition({ 3300, 200 });
	Sky_two->EffectCameraOff();
	TwoInitPos = Sky_two->GetPosition();
}

void Sky::Update(float _DeltaTime)
{
	if (1 == InitCount)
	{
		InitCount = 0;
		Sky_one->SetPosition({ 1100, YPos });
		Sky_two->SetPosition({ 3300, YPos });
	}

	SkyMove(_DeltaTime);
}

void Sky::SkyMove(float _DeltaTime)
{
	Sky_one->SetMove(float4::Left * MoveSpeed * _DeltaTime);
	Sky_two->SetMove(float4::Left * MoveSpeed * _DeltaTime);

	if (Sky_one->GetPosition().x <= -1100)
	{
		++Minus;
		Sky_one->SetPosition({ 3300.0f - (Minus * 2), YPos });
	}

	if (Sky_two->GetPosition().x <= -1100)
	{
		++Minus;
		Sky_two->SetPosition({ 3300.0f - (Minus * 2), YPos });
	}
}
