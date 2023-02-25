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
	// 768 417 1.84
	GameEngineRender* Render = CreateRender("Sky.Bmp", RenderOrder::BackGround);
	Render->SetPosition({ 640, -80 });
	Render->SetScale({ 2200, 1177 });
	Render->EffectCameraOff();
}


void Sky::Update(float _DeltaTime)
{
	// SHA->SetPos({ 300, 600 });
	// float4 Dir = float4::Left;
	// SetMove(Dir * 1000.0f * _DeltaTime);

	//if (GetPos().x > 0)
	//{
	//	SetMove({ 640, -80 });
	//}
}