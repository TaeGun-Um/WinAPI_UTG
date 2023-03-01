#include "Jar_Piece2.h"

#include <GameEngineCore/GameEngineRender.h>

#include "ContentsEnum.h"

Jar_Piece2::Jar_Piece2() 
{
}

Jar_Piece2::~Jar_Piece2() 
{
}

void Jar_Piece2::Start()
{
	AnimationRender = CreateRender(RenderOrder::Object);
	AnimationRender->SetScale({ 400, 400 });

	AnimationRender->CreateAnimation({ .AnimationName = "Jar",  .ImageName = "Jar_Piece.bmp", .Start = 8, .End = 15, .InterTime = 0.1f });

	AnimationRender->ChangeAnimation("Jar");
}

void Jar_Piece2::Update(float _DeltaTime)
{
	DirectCheckForKill();
	MoveCalculation(_DeltaTime);
}
void Jar_Piece2::Render(float _DeltaTime)
{
}

void Jar_Piece2::MoveCalculation(float _DeltaTime)
{
	if (true == IsStart)
	{
		IsStart = false;
		MoveDir.y -= 600.0f;
	}

	MoveDir += float4::Down * 2000.0f * _DeltaTime;

	SetMove(float4::Right * 250.0f * _DeltaTime);

	SetMove(MoveDir * _DeltaTime);
}

void Jar_Piece2::DirectCheckForKill()
{
	float4 Pos = OwnerPos + (float4::Down * 50);

	if (GetPos().y >= Pos.y)
	{
		Kill();
	}
}

void Jar_Piece2::Kill()
{
	GameEngineActor* ColActor = AnimationRender->GetActor();
	ColActor->Off();
	ColActor->Death();
}