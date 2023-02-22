#include "Machinegun_PlatPiece1.h"

#include <GameEngineCore/GameEngineResources.h>
#include <GameEngineCore/GameEngineRender.h>
#include <GameEngineCore/GameEngineLevel.h>

#include "ContentsEnum.h"

Machinegun_PlatPiece1::Machinegun_PlatPiece1() 
{
}

Machinegun_PlatPiece1::~Machinegun_PlatPiece1() 
{
}

void Machinegun_PlatPiece1::Start()
{
	AnimationRender = CreateRender("Machinegun_PlatPiece1.Bmp", RenderOrder::BackGround);
	AnimationRender->SetScale({ 50, 50 });
}

void Machinegun_PlatPiece1::Update(float _DeltaTime)
{
	DirectCheckForKill();
	MoveCalculation(_DeltaTime);
}
void Machinegun_PlatPiece1::Render(float _DeltaTime)
{
}

void Machinegun_PlatPiece1::MoveCalculation(float _DeltaTime)
{
	///////////////////////////////////////////////////  ม฿ทย  ///////////////////////////////////////////////////

	MoveDir += float4::Down * 2000.0f * _DeltaTime;

	SetMove(float4::Left * 200.0f * _DeltaTime);

	SetMove(MoveDir * _DeltaTime);
}

void Machinegun_PlatPiece1::DirectCheckForKill()
{
	float4 Pos = OwnerPos + (float4::Down * 250);

	if (GetPos().y >= Pos.y)
	{
		Kill();
	}
}

void Machinegun_PlatPiece1::Kill()
{
	GameEngineActor* ColActor = AnimationRender->GetActor();
	ColActor->Off();
	ColActor->Death();
}