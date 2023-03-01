#include "Jar_Piece1.h"

#include <GameEngineCore/GameEngineRender.h>

#include "ContentsEnum.h"

Jar_Piece1::Jar_Piece1() 
{
}

Jar_Piece1::~Jar_Piece1() 
{
}

void Jar_Piece1::Start()
{
	AnimationRender = CreateRender(RenderOrder::Object);
	AnimationRender->SetScale({ 400, 400 });

	AnimationRender->CreateAnimation({ .AnimationName = "Jar",  .ImageName = "Jar_Piece.bmp", .Start = 0, .End = 7, .InterTime = 0.1f });

	AnimationRender->ChangeAnimation("Jar");
}

void Jar_Piece1::Update(float _DeltaTime)
{
	DirectCheckForKill();
	MoveCalculation(_DeltaTime);
}
void Jar_Piece1::Render(float _DeltaTime)
{
}

void Jar_Piece1::MoveCalculation(float _DeltaTime)
{
	if (true == IsStart)
	{
		IsStart = false;
		MoveDir.y -= 800.0f;
	}

	MoveDir += float4::Down * 2000.0f * _DeltaTime;

	SetMove(float4::Left * 200.0f * _DeltaTime);

	SetMove(MoveDir * _DeltaTime);
}

void Jar_Piece1::DirectCheckForKill()
{
	float4 Pos = OwnerPos + (float4::Down * 50);

	if (GetPos().y >= Pos.y)
	{
		Kill();
	}
}

void Jar_Piece1::Kill()
{
	GameEngineActor* ColActor = AnimationRender->GetActor();
	ColActor->Off();
	ColActor->Death();
}