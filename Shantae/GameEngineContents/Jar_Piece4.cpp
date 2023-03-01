#include "Jar_Piece4.h"

#include <GameEngineCore/GameEngineRender.h>

#include "ContentsEnum.h"

Jar_Piece4::Jar_Piece4() 
{
}

Jar_Piece4::~Jar_Piece4() 
{
}

void Jar_Piece4::Start()
{
	AnimationRender = CreateRender(RenderOrder::Object);
	AnimationRender->SetScale({ 400, 400 });

	AnimationRender->CreateAnimation({ .AnimationName = "Jar",  .ImageName = "Jar_Piece.bmp", .Start = 16, .End = 23, .InterTime = 0.1f });

	AnimationRender->ChangeAnimation("Jar");
}

void Jar_Piece4::Update(float _DeltaTime)
{
	DirectCheckForKill();
	MoveCalculation(_DeltaTime);
}
void Jar_Piece4::Render(float _DeltaTime)
{
}

void Jar_Piece4::MoveCalculation(float _DeltaTime)
{
	if (true == IsStart)
	{
		IsStart = false;
		MoveDir.y -= 350.0f;
	}

	MoveDir += float4::Down * 2000.0f * _DeltaTime;

	SetMove(float4::Left * 150.0f * _DeltaTime);

	SetMove(MoveDir * _DeltaTime);
}

void Jar_Piece4::DirectCheckForKill()
{
	float4 Pos = OwnerPos + (float4::Down * 50);

	if (GetPos().y >= Pos.y)
	{
		Kill();
	}
}

void Jar_Piece4::Kill()
{
	GameEngineActor* ColActor = AnimationRender->GetActor();
	ColActor->Off();
	ColActor->Death();
}