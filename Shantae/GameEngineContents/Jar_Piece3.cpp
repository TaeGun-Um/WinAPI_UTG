#include "Jar_Piece3.h"

#include <GameEngineCore/GameEngineRender.h>

#include "ContentsEnum.h"

Jar_Piece3::Jar_Piece3() 
{
}

Jar_Piece3::~Jar_Piece3() 
{
}

void Jar_Piece3::Start()
{
	AnimationRender = CreateRender(RenderOrder::Object);
	AnimationRender->SetScale({ 400, 400 });

	AnimationRender->CreateAnimation({ .AnimationName = "Jar",  .ImageName = "Jar_Piece.bmp", .Start = 16, .End = 23, .InterTime = 0.1f });

	AnimationRender->ChangeAnimation("Jar");
}

void Jar_Piece3::Update(float _DeltaTime)
{
	DirectCheckForKill();
	MoveCalculation(_DeltaTime);
}
void Jar_Piece3::Render(float _DeltaTime)
{
}

void Jar_Piece3::MoveCalculation(float _DeltaTime)
{
	MoveDir += float4::Down * 2000.0f * _DeltaTime;

	SetMove(float4::Right * 100.0f * _DeltaTime);

	SetMove(MoveDir * _DeltaTime);
}

void Jar_Piece3::DirectCheckForKill()
{
	float4 Pos = OwnerPos + (float4::Down * 50);

	if (GetPos().y >= Pos.y)
	{
		Kill();
	}
}

void Jar_Piece3::Kill()
{
	GameEngineActor* ColActor = AnimationRender->GetActor();
	ColActor->Off();
	ColActor->Death();
}