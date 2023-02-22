#include "Machinegun_PlatPiece2.h"

#include <GameEngineCore/GameEngineResources.h>
#include <GameEngineCore/GameEngineRender.h>
#include <GameEngineCore/GameEngineLevel.h>

#include "ContentsEnum.h"

Machinegun_PlatPiece2::Machinegun_PlatPiece2() 
{
}

Machinegun_PlatPiece2::~Machinegun_PlatPiece2() 
{
}

void Machinegun_PlatPiece2::Start()
{
	AnimationRender = CreateRender("Machinegun_PlatPiece2.Bmp", RenderOrder::BackGround);
	AnimationRender->SetScale({ 50, 50 });
}

void Machinegun_PlatPiece2::Update(float _DeltaTime)
{
	DirectCheckForKill();
	MoveCalculation(_DeltaTime);
}
void Machinegun_PlatPiece2::Render(float _DeltaTime)
{
}

void Machinegun_PlatPiece2::MoveCalculation(float _DeltaTime)
{
	///////////////////////////////////////////////////  ม฿ทย  ///////////////////////////////////////////////////

	MoveDir += float4::Down * 2000.0f * _DeltaTime;

	SetMove(float4::Right * 200.0f * _DeltaTime);

	SetMove(MoveDir * _DeltaTime);
}

void Machinegun_PlatPiece2::DirectCheckForKill()
{
	float4 Pos = OwnerPos + (float4::Down * 250);

	if (GetPos().y >= Pos.y)
	{
		Kill();
	}
}

void Machinegun_PlatPiece2::Kill()
{
	GameEngineActor* ColActor = AnimationRender->GetActor();
	ColActor->Off();
	ColActor->Death();
}