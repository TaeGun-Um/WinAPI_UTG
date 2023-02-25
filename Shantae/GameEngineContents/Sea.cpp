#include "Sea.h"

#include <GameEngineCore/GameEngineRender.h>
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEnginePlatform/GameEngineInput.h>

#include "Player.h"
#include "ContentsEnum.h"

Sea::Sea()
{
}

Sea::~Sea()
{
}

void Sea::Start()
{
	SeaRender_one = CreateRender("Sea.Bmp", RenderOrder::BackGround);
	SeaRender_one->SetScale(SeaRender_one->GetImage()->GetImageScale());
	SeaRender_one->EffectCameraOff();
}

void Sea::Update(float _DeltaTime)
{
	if (1 == InitCount)
	{
		InitCount = 0;
		InitSeaonePos = SeaRender_one->GetPosition();
		InitSeaYPos = InitSeaonePos.y;
		InitCameraPos = Player::MainPlayer->GetLevel()->GetCameraPos();
	}

	Perspective();
}

void Sea::Perspective()
{
	if (true == Player::MainPlayer->GetCameraMove())
	{
		float4 CameraPos = float4::Zero;
		CameraPos = Player::MainPlayer->GetLevel()->GetCameraPos();

		float4 SeaMove = InitCameraPos - CameraPos;

		SeaRender_one->SetPosition({ (InitSeaonePos.x + SeaMove.x) * 0.05f , InitSeaYPos });
	}
}