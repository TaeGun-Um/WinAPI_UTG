#include "Jar.h"

#include <GameEngineCore/GameEngineRender.h>
#include <GameEngineCore/GameEngineCollision.h>
#include <GameEngineCore/GameEngineLevel.h>

#include "ContentsEnum.h"

#include "Jar_Piece1.h"
#include "Jar_Piece2.h"
#include "Jar_Piece3.h"

Jar::Jar() 
{
}

Jar::~Jar() 
{
}

void Jar::Start()
{
	AnimationRender = CreateRender(RenderOrder::Object);
	AnimationRender->SetScale({ 400, 400 });

	AnimationRender->CreateAnimation({ .AnimationName = "Jar",  .ImageName = "Jar.bmp", .Start = 0, .End = 3, .InterTime = 0.1f });

	BodyCollision = CreateCollision(CollisionOrder::Item);
	BodyCollision->SetDebugRenderType(CT_Rect);
	BodyCollision->SetScale({ 25, 50 });
	BodyCollision->SetPosition({ 0, -25 });

	AnimationRender->ChangeAnimation("Jar");
}

void Jar::Update(float _DeltaTime)
{
	MoveCalculation(_DeltaTime);
	CollisionCheck(_DeltaTime);
}

void Jar::Render(float _DeltaTime)
{

}

// 중력, 점프, 맵타일
void Jar::MoveCalculation(float _DeltaTime)
{
	///////////////////////////////////////////////////  중력  ///////////////////////////////////////////////////
	
	MoveDir += float4::Down * 1500.0f * _DeltaTime;

	/////////////////////////////////////////////////// 맵타일 ///////////////////////////////////////////////////

	NextPos = GetPos() + GroundPos + MoveDir * _DeltaTime;

	if (nullptr == ColMap)
	{
		MsgAssert("충돌용 맵 이미지가 없습니다.");
	}

	if (RGB(0, 248, 0) == ColMap->GetPixelColor(NextPos, RGB(0, 0, 0)))
	{
		MoveDir = float4::Zero;
	}

	if (RGB(74, 65, 42) == ColMap->GetPixelColor(NextPos, RGB(0, 0, 0)))
	{
		MoveDir = float4::Zero;
	}

	SetMove(MoveDir * _DeltaTime);
}

void Jar::CollisionCheck(float _DeltaTime)
{
	if (nullptr != BodyCollision)
	{
		if (true == BodyCollision->Collision({ .TargetGroup = static_cast<int>(CollisionOrder::PlayerAttack), .TargetColType = CT_Rect, .ThisColType = CT_Rect }))
		{
			BodyCollision->Off();

			if (1 == SoundCount)
			{
				SoundCount = 0;
				BGMPlayer = GameEngineResources::GetInst().SoundPlayToControl("Clash_smalljar.wav");
				BGMPlayer.Volume(0.2f);
				BGMPlayer.LoopCount(1);
			}

			Break();
		}
	}
}

void Jar::Break()
{
	Jar_Piece1* Piece1 = nullptr;

	Piece1 = GetLevel()->CreateActor<Jar_Piece1>();
	Piece1->SetPos(GetPos());
	Piece1->SetOwnerPos(GetPos());

	Jar_Piece2* Piece2 = nullptr;

	Piece2 = GetLevel()->CreateActor<Jar_Piece2>();
	Piece2->SetPos(GetPos());
	Piece2->SetOwnerPos(GetPos());

	Jar_Piece3* Piece3 = nullptr;

	Piece3 = GetLevel()->CreateActor<Jar_Piece3>();
	Piece3->SetPos(GetPos());
	Piece3->SetOwnerPos(GetPos());

	Kill();
}

void Jar::Kill()
{
	GameEngineActor* ColActor = AnimationRender->GetActor();
	ColActor->Off();
	ColActor->Death();
}